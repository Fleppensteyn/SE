/*
  SE 2014
  Group 8
*/

#include "Overview.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(Overview, wxPanel)
  //EVT_COMBOBOX_CLOSEUP  (ID_FACULTY, Overview::OnUpdateFaculty)
  EVT_TEXT              (ID_FACULTY, Overview::OnUpdateFaculty)
  //EVT_COMBOBOX_CLOSEUP  (ID_YEARS, Overview::OnUpdateYear)
  EVT_TEXT              (ID_YEARS, Overview::OnUpdateYear)
  EVT_BUTTON            (ID_SHOW, Overview::OnShow)
  EVT_PAINT             (Overview::drawStuff)
  EVT_SIZE              (Overview::OnResize)
wxEND_EVENT_TABLE()

Overview::Overview(wxFrame *frame, int x, int y, int w, int h)
      :wxPanel(frame, wxID_ANY, wxPoint(x,y), wxSize(w, h))
{
  this->database = new Database("client.db");
  this->courses = new Courses(this->database);
  this->dragdrop = new DragDropHelp();
  this->mousemanager = new MouseManager(this, this->dragdrop);
  this->database->fillCourses(this->courses);

  //Set an empty curriculum to initially fill the screen
  curriculum = new Curriculum(this, dragdrop);
  curriculum->SetBackgroundColour(wxColour(200,200,200));

  const wxString t[] = {wxT("Computer Science"), wxT("Economics")};
  wxArrayString *temp = new wxArrayString(2, t);
  wxArrayString *facs = database->getFaculties();
  faculties = new wxComboBox(this, ID_FACULTY, wxT(""), wxPoint(0,0), wxSize(200,25),
                             *facs, wxCB_READONLY);
  years = new wxComboBox(this, ID_YEARS);

  show = new wxButton(this, ID_SHOW, wxT("Show"));
  show->Enable(false);

  //Setup the catalogue
  catalogue = new Catalogue(this, this->courses, this->dragdrop);
  catalogue->SetBackgroundColour(wxColour("#FFFFFF"));

  //Position the curricula and catalogue and drop-down list buttons
  wxBoxSizer *cbrow = new wxBoxSizer(wxHORIZONTAL);
  cbrow->Add(faculties, 0, wxALIGN_LEFT | wxALL, 10);
  cbrow->Add(years, 0, wxALIGN_LEFT | wxALL, 10);
  cbrow->Add(show, 0, wxALIGN_LEFT | wxALL, 10);

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
}

Overview::~Overview(){
  delete mousemanager;
  delete courses;
  delete database;
  delete dragdrop;
}

void Overview::OnUpdateFaculty(wxCommandEvent& event){
  years->Clear();
  wxArrayString *temp = database->getYears(faculties->GetValue());
  years->Append(*temp);
  show->Enable(false);
}//OnUpdateFaculty

void Overview::OnUpdateYear(wxCommandEvent& event){
  show->Enable(true);
}//OnUpdateYear

void Overview::drawStuff(wxPaintEvent& event){
  wxPaintDC dc(this);
  wxPoint pos;
  if (dragdrop->needsDrawing(pos, DRAGDROP_OVERVIEW))
    dc.DrawBitmap(dragdrop->getCourse()->bitmap, pos);
  curriculum->dragDraw();
}

void Overview::OnShow(wxCommandEvent& event){
  wxString fac = faculties->GetValue();
  wxString ys = years->GetValue();
  wxString name = faculties->GetValue() << wxString(" ") << ys;
  curriculum->setCurriculum(database->populateTree(fac, ys), name);
}

void Overview::OnResize(wxSizeEvent& event){
  Layout();
  wxPoint catalogpos = GetSizer()->GetItem(catalogue, true)->GetPosition(),
       curriculumpos = GetSizer()->GetItem(curriculum, true)->GetPosition();
  wxSize catalogsize = catalogue->GetClientSize(),
      curriculumsize = curriculum->GetClientSize();
  dragdrop->updateVariables(catalogpos, curriculumpos, catalogsize, curriculumsize);
}