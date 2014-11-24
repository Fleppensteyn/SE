/*
  SE 2014
  Group 8
*/

#include "CourseEditor.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(CourseEditor, wxDialog)
  EVT_BUTTON            (ID_EDIT_SUBMIT_COURSE, CourseEditor::OnSubmitCourse)
  EVT_BUTTON						(ID_DELETE_COURSE, CourseEditor::OnDeleteCourse)
  EVT_TEXT_ENTER        (wxID_ANY, CourseEditor::OnTextEnter)
  EVT_COMBOBOX_CLOSEUP  (wxID_ANY, CourseEditor::updatePreview)
  EVT_TEXT              (wxID_ANY, CourseEditor::updatePreview)
  EVT_PAINT             (CourseEditor::drawPreview)
  wxEND_EVENT_TABLE()

//TODO: Iets met copyvariabelen doen, preview werkend krijgen

CourseEditor::CourseEditor(Course *course)
      :wxDialog(NULL, wxID_ANY, wxT("Course Editing"), wxPoint(100,100), wxSize(500, 450),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
 //Static boxes and static text elements
  box1 = new wxStaticBox(this, wxID_ANY, "Course specifics", wxPoint(20, 10),
                         wxSize(460, 120));
  box2 = new wxStaticBox(this, wxID_ANY, "Course affiliations", wxPoint(20, 140),
                         wxSize(460, 150));
	
	//Copy values of course
	wxString copyName = course->name;
  int copyEcts = course->ects;
  //TODO: Zet affiliaton en course_type op de juiste waarden
  //wxString copyAffiliation = ....
  //wxString copyCourse_type = ....;
  wxString copyCourse_number = course->number;
	
	wxString stringEcts = wxString::Format(wxT("%i"),copyEcts);
	//ItoA(copyEcts);
	
  wxFont font = box1->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  wxStaticText *name_text = new wxStaticText(box1, -1, "Course Name:");
  name_text->SetFont(font);
  wxStaticText *ects_text = new wxStaticText(box1, -1, "ECTS:");
  ects_text->SetFont(font);
	wxStaticText *affiliation_text = new wxStaticText(box2, -1, "Affiliation:");
	affiliation_text->SetFont(font);
  wxStaticText *course_type_text = new wxStaticText(box2, -1, "Course Type:");
  course_type_text->SetFont(font);
  wxStaticText *number_text = new wxStaticText(box2, -1, "Course number:");
  number_text->SetFont(font);

  //Course name input box
  course_name = new wxTextCtrl(box1, ID_EDIT_COURSE_NAME, copyName, wxPoint(120, 27), wxSize(300, 25),
                              wxTE_PROCESS_ENTER);
  course_name->SetHint("course name");
  course_name->SetFocus();
  course_name->SetMaxLength(50);

  //ECTS input box
  ects = new wxTextCtrl(box1, ID_EDIT_ECTS, stringEcts, wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT, wxTextValidator(wxFILTER_DIGITS));
  ects->SetMaxLength(2);

  //Affiliation selection
  const wxString temp1[] = {wxT("Affiliated to CS"), //REPLACE THIS WITH LIST FROM DATABASE
                      wxT("Affiliated to Biology"),
                      wxT("Affiliated to Economics"),
                      wxT("Programming Line"),
                      wxT("Algorithmics Line"),
                      wxT("Foundations Line"),
                      wxT("Computer Systems Line"),
                      wxT("Software Engineering Line"),
                      wxT("Computer Graphics Line"),
                      wxT("Other")};

  wxArrayString *affiliations = new wxArrayString(10,temp1);
  affiliation = new wxComboBox(box2, ID_EDIT_AFFILIATION, wxT("Affiliated to CS"), wxPoint(120,27),
                               wxSize(300,25), *affiliations, wxCB_READONLY | wxTE_PROCESS_ENTER);
  
  //Course type selection
  const wxString temp2[] = {wxT("Academic Skills"), //REPLACE THIS WITH LIST FROM DATABASE
                      wxT("Mathematics"),
                      wxT("CS Essentials"),
                      wxT("CS Mandatory"),
                      wxT("CS Elective"),
                      wxT("Economics Essentials"),
                      wxT("Biology Essentials")};
  wxArrayString *course_types = new wxArrayString(7,temp2);
  course_type = new wxComboBox(box2, ID_EDIT_COURSE_TYPE, wxT("Academic Skills"), wxPoint(120,67),
                               wxSize(300,25), *course_types, wxCB_READONLY | wxTE_PROCESS_ENTER);

  //Course number input box
  course_number = new wxTextCtrl(box2, ID_EDIT_COURSE_NUMBER, copyCourse_number, wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT);
  course_number->SetMaxLength(2);

  //Create accept button
  wxButton *create = new wxButton(this, ID_EDIT_SUBMIT_COURSE, wxT("Create"));// this course"));
  
  //Create delete button
	wxButton *deleteCourse = new wxButton(this, ID_DELETE_COURSE, wxT("Delete course"));

  //Positioning of elements in box1
  wxFlexGridSizer *box1_flex = new wxFlexGridSizer(2, 2, 15, 10);
  box1_flex->Add(name_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(course_name, 0, wxALIGN_LEFT);
  box1_flex->Add(ects_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(ects, 0, wxALIGN_LEFT);

  wxBoxSizer *box1_row = new wxBoxSizer(wxHORIZONTAL);
  box1_row->AddStretchSpacer(1);
  box1_row->Add(box1_flex, 0, wxALIGN_CENTER);
  box1_row->AddStretchSpacer(1);

  wxBoxSizer *box1_column = new wxBoxSizer(wxVERTICAL);
  box1_column->AddStretchSpacer(1);
  box1_column->Add(box1_row, 0, wxALIGN_CENTER);
  box1_column->AddStretchSpacer(1);

  box1->SetSizer(box1_column);

  //Positioning of elements in box2
  wxFlexGridSizer *box2_flex = new wxFlexGridSizer(3, 2, 15, 10);
  box2_flex->Add(affiliation_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box2_flex->Add(affiliation, 0, wxALIGN_LEFT);
  box2_flex->Add(course_type_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box2_flex->Add(course_type, 0, wxALIGN_LEFT);
  box2_flex->Add(number_text, 0, wxALIGN_RIGHT| wxTOP, 3);
  box2_flex->Add(course_number, 0, wxALIGN_LEFT);

  wxBoxSizer *box2_row = new wxBoxSizer(wxHORIZONTAL);
  box2_row->AddStretchSpacer(1);
  box2_row->Add(box2_flex, 0, wxALIGN_CENTER);
  box2_row->AddStretchSpacer(1);

  wxBoxSizer *box2_column = new wxBoxSizer(wxVERTICAL);
  box2_column->AddStretchSpacer(1);
  box2_column->Add(box2_row, 0, wxALIGN_CENTER);
  box2_column->AddStretchSpacer(1);

  box2->SetSizer(box2_column);

  //Positioning of elements in dialog
  wxBoxSizer *button_row = new wxBoxSizer(wxHORIZONTAL);
  button_row->Add(CreateButtonSizer(wxCANCEL), 0, wxALIGN_LEFT);
  button_row->AddStretchSpacer(1);
  button_row->Add(deleteCourse, 0, wxALIGN_CENTER);
  button_row->AddStretchSpacer(1);
  button_row->Add(create, 0, wxALIGN_RIGHT);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->Add(box1, 0, wxALL | wxEXPAND, 10);
  column->Add(box2, 0, wxRIGHT | wxBOTTOM | wxLEFT | wxEXPAND, 10);
  column->AddSpacer(80);
  column->Add(button_row, 0, wxRIGHT | wxLEFT | wxEXPAND, 10);

  SetSizer(column);
}//CourseEditor

CourseEditor::~CourseEditor(){
  ClearErrors();
}//~CourseEditor

void CourseEditor::OnDeleteCourse(wxCommandEvent& event){
	
}

void CourseEditor::OnTextEnter(wxCommandEvent& event){
  int id = event.GetId();
  if(id == ID_EDIT_COURSE_NAME) //Enter was pressed in the course name box
    ects->SetFocus();
  else if(id == ID_EDIT_ECTS) //Enter was pressed in the ects box
    affiliation->SetFocus();
  else if(id == ID_EDIT_AFFILIATION) //Enter was pressed in the ects box
    course_type->SetFocus();
  else if(id == ID_EDIT_COURSE_TYPE) //Enter was pressed in the ects box
    course_number->SetFocus();
  else{ //Enter was pressed in any other box that doesn't inherently handle these events
    wxCommandEvent event(wxEVT_BUTTON, ID_EDIT_SUBMIT_COURSE);
    wxPostEvent(this, event);
  }
}//OnTextEnter

void CourseEditor::OnSubmitCourse(wxCommandEvent& event){
  ClearErrors(); //Clear the errors of the previous creation attempt
  if(course_name->GetValue() == "")
    DisplayError(ERROR_EDIT_NO_NAME); //No course name was specified
  if(ects->GetValue() == "")
    DisplayError(ERROR_EDIT_NO_ECTS); //No ects amount specified
  if(course_number->GetValue() == "")
    DisplayError(ERROR_EDIT_NO_NUMBER);

  if(errors.size() == 0)
    EndModal(wxID_OK);

  for(int i = 0; i < errors.size(); i++)
    errors[i]->SetForegroundColour(wxColour(wxT("RED")));
}//OnSubmitCourse

void CourseEditor::DisplayError(int error){
  switch(error){
    case ERROR_EDIT_NO_NAME:
      errors.push_back(new wxStaticText(box1, wxID_ANY, "Course name can't be empty!",
                                        wxPoint(150,10), wxSize(300,17)));
      break;
    case ERROR_EDIT_NO_ECTS:
      errors.push_back(new wxStaticText(box1, wxID_ANY, "Must specify ECTS amount!",
                                        wxPoint(200,70), wxSize(200, 17)));
      break;
    case ERROR_EDIT_NO_NUMBER:
      errors.push_back(new wxStaticText(box2, wxID_ANY, "Must specify a course number!",
                                        wxPoint(150,85), wxSize(300, 17)));
      break;
    case ERROR_EDIT_COURSE_ALREADY_EXISTS:
      errors.push_back(new wxStaticText(this, wxID_ANY, "The specified course already exists!",
                                        wxPoint(120, 380), wxSize(250, 17)));
      errors[0]->SetForegroundColour(wxColour(wxT("RED")));
      break;
  }
}//DisplayError

void CourseEditor::ClearErrors(){
  for(int i = 0; i < errors.size(); i++)
    errors[i]->Destroy();
  errors.clear();
}//ClearErrors

std::vector<wxString> CourseEditor::getData(){
  std::vector<wxString> data;
  data.push_back(course_name->GetValue());
  data.push_back(ects->GetValue());
  data.push_back(affiliation->GetValue());
  data.push_back(course_type->GetValue());
  data.push_back(course_number->GetValue());
  return data;
}//getData

void CourseEditor::updatePreview(wxCommandEvent& event){
  Refresh();
}

void CourseEditor::drawPreview(wxPaintEvent& event){
  /*Course course = Course();
  course.name = course_name->GetValue();
  course.line = determineLine();
  course.number = course_number->GetValue();
  course.ects = wxAtoi(ects->GetValue());
  course.affiliation = courses->getAffiliationColour(affiliation->GetValue());
  course.type = courses->getTypeColour(course_type->GetValue());
  preview = DrawingHelper::drawCourse(course);
  wxPaintDC dc(this);
  dc.DrawBitmap(preview, 130, 310);*/
}//updatePreview

wxString CourseEditor::determineLine(){
  wxString line = "", 
           type = course_type->GetValue(),
           aff = affiliation->GetValue();
  if(type == wxT("Economics Essentials"))
    line = wxT("E");
  else if(type == wxT("Biology Essentials"))
    line = wxT("B");
  else if(aff == wxT("Affiliated to CS") ||
     aff == wxT("Affiliated to Biology") ||
     aff == wxT("Affiliated to Economics") ||
     aff == wxT("Other"))
  {
    if(type == wxT("Academic Skills"))
      line = wxT("AS");
    else if(type == wxT("Mathematics"))
      line = wxT("M");
    else if(type == wxT("CS Essentials"))
      line = wxT("CE");
    else if(type == wxT("CS Mandatory"))
      line = wxT("C");
    else if(type == wxT("CS Elective"))
      line = wxT("CL");
  } 
  else if(aff == wxT("Programming Line"))
    line = wxT("PR");
  else if(aff == wxT("Algorithmics Line"))
    line = wxT("AL");
  else if(aff == wxT("Foundations Line"))
    line = wxT("FI");
  else if(aff == wxT("Computer Systems Line"))
    line = wxT("CS");
  else if(aff == wxT("Software Engineering Line"))
    line = wxT("SE");
  else if(aff == wxT("Computer Graphics Line"))
    line = wxT("CI");

  return line;
}//determineLine

