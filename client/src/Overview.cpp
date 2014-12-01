/*
  SE 2014
  Group 8
*/

#include "Overview.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(Overview, wxPanel)
  EVT_COMBOBOX          (ID_FACULTY, Overview::OnUpdateFaculty)
  //EVT_COMBOBOX_CLOSEUP  (ID_FACULTY, Overview::OnUpdateFaculty)
  // EVT_TEXT              (ID_FACULTY, Overview::OnUpdateFaculty)
  EVT_COMBOBOX          (ID_YEARS, Overview::OnUpdateYear)
  //EVT_COMBOBOX_CLOSEUP  (ID_YEARS, Overview::OnUpdateYear)
  // EVT_TEXT              (ID_YEARS, Overview::OnUpdateYear)
  EVT_BUTTON            (ID_SPLIT, Overview::OnSplit)
  EVT_PAINT             (Overview::drawStuff)
  EVT_SIZE              (Overview::OnResize)
  EVT_COMMAND           (wxID_ANY, EVT_DELETED_COURSE, Overview::OnDeletedCourse)
  EVT_COMMAND           (wxID_ANY, EVT_SELECTED, Overview::OnSelected)
  EVT_COMMAND           (wxID_ANY, EVT_NO_SELECT, Overview::OnNoSelect)
  EVT_COMMAND           (wxID_ANY, EVT_SAVE_DB, Overview::OnSaveDB)
wxEND_EVENT_TABLE()

Overview::Overview(wxFrame *frame, int x, int y, int w, int h)
      :wxPanel(frame, wxID_ANY, wxPoint(x,y), wxSize(w, h))
{
#ifndef __APPLE__
  SetDoubleBuffered(true);
#endif
  this->database = new Database("client.db");
  this->courses = new Courses(this->database);
  this->dragdrop = new DragDropHelp();
  this->mousemanager = new MouseManager(this, this->dragdrop);
  this->database->fillCourses(this->courses);

  //Set an empty curriculum to initially fill the screen
  curriculum = new Curriculum(this, dragdrop);
  curriculum->SetBackgroundColour(wxColour(200,200,200));

  wxArrayString *facs = database->getFaculties();
  faculties = new wxComboBox(this, ID_FACULTY, wxT(""), wxPoint(0,0), wxSize(200,25),
                             *facs, wxCB_READONLY);
  years = new wxComboBox(this, ID_YEARS, wxT(""), wxPoint(0,0), wxSize(120, 25), 0, NULL,
                         wxCB_READONLY);

  split = new wxButton(this, ID_SPLIT, wxT("Insert split"));
  split->Enable(false);

  //Setup the catalogue
  catalogue = new Catalogue(this, this->courses, this->dragdrop);
  catalogue->SetBackgroundColour(wxColour("#FFFFFF"));

  //Position the curricula and catalogue and drop-down list buttons
  wxBoxSizer *cbrow = new wxBoxSizer(wxHORIZONTAL);
  cbrow->Add(faculties, 0, wxALIGN_LEFT | wxALL, 10);
  cbrow->Add(years, 0, wxALIGN_LEFT | wxALL, 10);
  cbrow->Add(split, 0, wxALIGN_LEFT | wxALL, 10);

  wxBoxSizer *curcolumn = new wxBoxSizer(wxVERTICAL);
  curcolumn->Add(cbrow);
  curcolumn->Add(curriculum, 1, wxEXPAND);

  wxBoxSizer *row = new wxBoxSizer(wxHORIZONTAL);
  row->AddSpacer(5);
  row->Add(curcolumn, 1, wxEXPAND);
  row->AddSpacer(10);
  row->Add(catalogue, 0, wxEXPAND);
  row->AddSpacer(5);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->AddSpacer(5);
  column->Add(row, 1, wxEXPAND);
  column->AddSpacer(5);

  SetSizer(column);
#ifdef __APPLE__
  if (faculties->GetCount() > 0){
    wxCommandEvent event(wxEVT_COMBOBOX, ID_FACULTY);
    wxPostEvent(this, event);
  }
#endif
}

Overview::~Overview(){
  delete mousemanager;
  delete courses;
  delete database;
  delete dragdrop;
}

int Overview::addNewCourse(std::vector<wxString> data){
  int ret = courses->addNewCourse(data);
  catalogue->refreshList();
  return ret;
}

int Overview::addNewCurriculum(std::vector<wxString> data){
  unsigned int semesters = wxAtoi(data[1]);
  unsigned int years = wxAtoi(data[2]);
  int ret = database->addCurriculum(data[0], semesters, years);
  if(ret >= 0){
    wxString sel = faculties->GetValue();
    faculties->Clear();
    wxArrayString *facs = database->getFaculties();
    faculties->Append(*facs);
    for(unsigned int i = 0; i < faculties->GetCount(); i++){
      if(faculties->GetString(i) == sel){
        faculties->SetSelection(i);
        break;
      }
    }
  }
  return ret;
}//addCourse

int Overview::addNewYear(wxFrame *frame){
  YearCreator yc(frame, database);
  while(yc.ShowModal() == wxID_OK){
    std::vector<wxString> data = yc.getData();
    int ret = database->addYear(data[0], wxAtoi(data[1]));
    if(ret >= 0){
      if(data[0] == faculties->GetValue()){
        wxCommandEvent event(wxEVT_COMBOBOX, ID_FACULTY);
        wxPostEvent(this, event);
      }
      return 1;
    }
    else if(ret == -1)
      yc.DisplayError(ERROR_YEAR_ALREADY_EXISTS);
  }
  return -1;
}

Courses* Overview::getCourses(){
  return courses;
}

void Overview::OnDeleteYear(wxFrame *frame){
  YearDeleter yd(frame, database);
  if(yd.ShowModal() == wxID_OK){
    std::vector<wxString> data = yd.getData();
    database->deleteYear(data[0], data[1]);
    if(data[0] == faculties->GetValue() && data[1] == years->GetValue()){
      clearYears();
      wxArrayString *temp = database->getYears(data[0]);
      years->Append(*temp);

      curriculum->clear();
    }
    else if(data[0] == faculties->GetValue()){
      wxString text = years->GetValue();
      years->Clear();
      wxArrayString *temp = database->getYears(data[0]);
      years->Append(*temp);
      for(unsigned int i = 0; i < years->GetCount(); i++){
        if(years->GetString(i) == text)
          years->SetSelection(i);
      }
    }
  }
}

void Overview::OnDeleteCurriculum(wxFrame *frame){
  CurriculumDeleter cd(frame, database);
  if(cd.ShowModal() == wxID_OK){
    std::vector<wxString> data = cd.getData();
    database->deleteCurriculum(data[0], true);
    if(data[0] == faculties->GetValue()){
      clearFaculties();
      clearYears();
      wxArrayString *temp = database->getFaculties();
      faculties->Append(*temp);

      curriculum->clear();
    }
    else{
      wxString text = faculties->GetValue();
      faculties->Clear();
      wxArrayString *temp = database->getFaculties();
      faculties->Append(*temp);
      for(unsigned int i = 0; i < faculties->GetCount(); i++){
        if(faculties->GetString(i) == text)
          faculties->SetSelection(i);
      }
    }
  }
}

void Overview::OnDeleteAll(){
  wxString msg = wxString("Do you want to permanently delete all curricula?\n") <<
                 wxString("Beware this can not be undone!");
  wxMessageDialog md(this, msg, wxT("Confirmation of deletion"), wxYES_NO);
  if(md.ShowModal() == wxID_YES){
    database->deleteAll();
    clearFaculties();
    clearYears();
    curriculum->clear();
  }
}

const char* Overview::getDatabaseFile(){
  return database->getDatabaseFile();
}

void Overview::OnUpdateFaculty(wxCommandEvent&){
  years->Clear();
  wxArrayString *temp = database->getYears(faculties->GetValue());
  years->Append(*temp);
  years->SetSelection(0);
  wxCommandEvent pevent(wxEVT_COMBOBOX, ID_YEARS);
  wxPostEvent(this, pevent);
}//OnUpdateFaculty

void Overview::OnUpdateYear(wxCommandEvent&){
  wxString fac = faculties->GetValue();
  wxString ys = years->GetValue();
  wxString name = faculties->GetValue() << wxString(" ") << ys;
  curriculum->setCurriculum(database->populateTree(fac, ys), name);
  curfac = fac;
  curyr = ys;
}//OnUpdateYear

void Overview::OnDeletedCourse(wxCommandEvent&){
  if(years->GetValue() != ""){
    wxCommandEvent event(wxEVT_COMBOBOX, ID_YEARS);
    wxPostEvent(this, event);
  }
}

void Overview::OnSplit(wxCommandEvent&){
  if(split->IsEnabled()){
    curriculum->insertSplit();
  }
}

void Overview::OnSelected(wxCommandEvent&){
  split->Enable(true);
}

void Overview::OnNoSelect(wxCommandEvent&){
  split->Enable(false);
}

void Overview::OnSaveDB(wxCommandEvent&){
  std::vector<Semester *> tree = this->curriculum->getCurriculum();
  this->database->saveYear(curfac, curyr, tree);
}

void Overview::drawStuff(wxPaintEvent&){
  wxPaintDC dc(this);
  wxPoint pos;
  if (dragdrop->needsDrawing(pos, DRAGDROP_OVERVIEW))
    dc.DrawBitmap(dragdrop->getCourse()->bitmap, pos);
  curriculum->dragDraw();
}

void Overview::OnResize(wxSizeEvent&){
  Layout();
  curriculum->drawCurriculum();
  curriculum->Layout();
  wxPoint catalogpos = GetSizer()->GetItem(catalogue, true)->GetPosition(),
       curriculumpos = GetSizer()->GetItem(curriculum, true)->GetPosition();
  wxSize catalogsize = catalogue->GetClientSize(),
      curriculumsize = curriculum->GetClientSize();
  dragdrop->updateVariables(catalogpos, curriculumpos, catalogsize, curriculumsize);
}

void Overview::clearFaculties(){
  wxArrayString *temp = new wxArrayString();
  temp->Add(wxT(""));

  faculties->Clear();
  faculties->Append(*temp);
  faculties->SetSelection(0);
  faculties->Clear();
}

void Overview::clearYears(){
  wxArrayString *temp = new wxArrayString();
  temp->Add(wxT(""));

  years->Clear();
  years->Append(*temp);
  years->SetSelection(0);
  years->Clear();
}