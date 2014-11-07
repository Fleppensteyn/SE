/*
  SE 2014
  Group 8
*/

#include "CourseCreator.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(CourseCreator, wxDialog)
  EVT_BUTTON      (ID_SUBMIT_COURSE, CourseCreator::OnSubmitCourse)
  EVT_TEXT_ENTER  (wxID_ANY, CourseCreator::OnTextEnter)
wxEND_EVENT_TABLE()

CourseCreator::CourseCreator(wxFrame *frame)
      :wxDialog(frame, wxID_ANY, wxT("Course creation"), wxPoint(100,100), wxSize(500, 400),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
  //Static boxes and static text elements
  wxStaticBox *box1 = new wxStaticBox(this, wxID_ANY, "Course specifics", wxPoint(20, 10),
                                      wxSize(460, 120));
  wxStaticBox *box2 = new wxStaticBox(this, wxID_ANY, "Course affiliations", wxPoint(20, 140),
                                      wxSize(460, 190));
  wxFont font = box1->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  wxStaticText *name_text = new wxStaticText(box1, wxID_ANY, "Course Name:", wxPoint (30, 30), wxSize(80,20));
  name_text->SetFont(font);
  wxStaticText *ects_text = new wxStaticText(box1, wxID_ANY, "ECTS:", wxPoint(77, 70), wxSize(33,20));
  ects_text->SetFont(font);
  wxStaticText *affiliation_text = new wxStaticText(box2, wxID_ANY, "Affiliation:", wxPoint(49,30),
                                                    wxSize(61,20));
  affiliation_text->SetFont(font);
  wxStaticText *course_type_text = new wxStaticText(box2, wxID_ANY, "Course Type:", wxPoint(36,70),
                                                    wxSize(74,20));
  course_type_text->SetFont(font);

  //Course name input box
  course_name = new wxTextCtrl(box1, ID_COURSE_NAME, wxT(""), wxPoint(120, 27), wxSize(300, 25),
                              wxTE_PROCESS_ENTER);
  course_name->SetHint("course name");
  course_name->SetFocus();
  course_name->SetMaxLength(30);

  //ECTS input box
  ects = new wxTextCtrl(box1, ID_ECTS, wxT("6"), wxPoint(120, 67), wxSize(40, 25),
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
                      wxT("Computer Graphics Line")};

  wxArrayString *affiliations = new wxArrayString(9,temp1);
  affiliation = new wxComboBox(box2, ID_AFFILIATION, wxT("Affiliated to CS"), wxPoint(120,27),
                               wxSize(300,500), *affiliations, wxCB_READONLY | wxTE_PROCESS_ENTER,
                               wxDefaultValidator);
  //Course type selection
  const wxString temp2[] = {wxT("Academic Skills"), //REPLACE THIS WITH LIST FROM DATABASE
                      wxT("Mathematics"),
                      wxT("CS Essentials"),
                      wxT("CS Mandaroty"),
                      wxT("CS Elective"),
                      wxT("Economics Essentials"),
                      wxT("Biology Essentials")};
  wxArrayString *course_types = new wxArrayString(7,temp2);
  course_type = new wxComboBox(box2, ID_COURSE_TYPE, wxT("Academic Skills"), wxPoint(120,67),
                               wxSize(300,500), *course_types, wxCB_READONLY | wxTE_PROCESS_ENTER,
                               wxDefaultValidator);

  //Create button
  wxButton *create = new wxButton(this, ID_SUBMIT_COURSE, wxT("Create"));// this course"));
  
  //Positioning of elements
  wxBoxSizer *button_row = new wxBoxSizer(wxHORIZONTAL);
  button_row->Add(CreateButtonSizer(wxCANCEL), 0, wxALIGN_LEFT);
  button_row->AddStretchSpacer(1);
  button_row->Add(create, 0, wxALIGN_RIGHT);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->Add(box1, 0, wxALL | wxEXPAND, 10);
  column->Add(box2, 0, wxBOTTOM | wxRIGHT | wxLEFT | wxEXPAND, 10);
  column->Add(button_row, 0, wxRIGHT | wxLEFT | wxEXPAND, 10);

  SetSizer(column);
}//CourseCreator

CourseCreator::~CourseCreator(){
  ClearErrors();
}//~CourseCreator

void CourseCreator::OnTextEnter(wxCommandEvent& event){
  int id = event.GetId();
  if(id == ID_COURSE_NAME) //Enter was pressed in the course name box
    ects->SetFocus();
  else if(id == ID_ECTS) //Enter was pressed in the ects box
    affiliation->SetFocus();
  else{ //Enter was pressed in any other box that doesn't inherently handle these events
    wxCommandEvent event(wxEVT_BUTTON, ID_SUBMIT_COURSE);
    wxPostEvent(this, event);
  }
}//OnTextEnter

void CourseCreator::OnSubmitCourse(wxCommandEvent& event){
  ClearErrors(); //Clear the errors of the previous creation attempt
  if(course_name->GetLineText(0) == course_name->GetHint())
    DisplayError(ERROR_NO_NAME); //No course name was specified

  for(int i = 0; i < errors.size(); i++)
    errors[i]->SetForegroundColour(wxColour(wxT("RED")));
}//OnSubmitCourse

void CourseCreator::DisplayError(int error){
  switch(error){
    case ERROR_NO_NAME:
       errors.push_back(new wxStaticText(this, wxID_ANY, "Course name can't be empty",
                                              wxPoint(130,20), wxSize(300,15)));
       break;
  }
}//DisplayError

void CourseCreator::ClearErrors(){
  for(int i = 0; i < errors.size(); i++)
    delete errors[i];
  errors.clear();
}//ClearErrors