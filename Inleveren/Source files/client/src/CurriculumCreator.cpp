/*
  SE 2014
  Group 8
*/

#include "CurriculumCreator.h"

wxBEGIN_EVENT_TABLE(CurriculumCreator, wxDialog)
  EVT_BUTTON            (ID_SUBMIT_CURRICULUM, CurriculumCreator::OnSubmitCurriculum)
  EVT_TEXT_ENTER        (wxID_ANY, CurriculumCreator::OnTextEnter)
wxEND_EVENT_TABLE()

CurriculumCreator::CurriculumCreator(wxFrame *frame)
      :wxDialog(frame, wxID_ANY, wxT("Study program creation"), wxPoint(100,100), wxSize(500, 230),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP){

  box1 = new wxStaticBox(this, wxID_ANY, "Study program specifics", wxPoint(20, 10),
                         wxSize(460, 160));

  wxFont font = box1->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  wxStaticText *name_text = new wxStaticText(box1, -1, "Study program name:");
  name_text->SetFont(font);
  wxStaticText *years_text = new wxStaticText(box1, -1, "Years:");
  years_text->SetFont(font);
  wxStaticText *semesters_text = new wxStaticText(box1, -1, "Semesters per year:");
  semesters_text->SetFont(font);

  //Curriculum name input box
  curriculum_name = new wxTextCtrl(box1, ID_CURRICULUM_NAME, wxT(""), wxPoint(120, 27), wxSize(300, 25),
                              wxTE_PROCESS_ENTER);
  curriculum_name->SetHint("study program name");
  curriculum_name->SetFocus();
  curriculum_name->SetMaxLength(50);


  //Semesters per year input box
  semesters = new wxTextCtrl(box1, ID_CURSEMESTERS, wxT("2"), wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT, wxTextValidator(wxFILTER_DIGITS));
  semesters->SetMaxLength(2);

  //Years input box
  years = new wxTextCtrl(box1, ID_CURYEARS, wxT("3"), wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT, wxTextValidator(wxFILTER_DIGITS));
  years->SetMaxLength(2);

  //Create button
  wxButton *create = new wxButton(this, ID_SUBMIT_CURRICULUM, wxT("Create"));

  //Positioning of elements
  wxFlexGridSizer *box1_flex = new wxFlexGridSizer(3, 2, 15, 10);
  box1_flex->Add(name_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(curriculum_name, 0, wxALIGN_LEFT);
  box1_flex->Add(semesters_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(semesters, 0, wxALIGN_LEFT);
  box1_flex->Add(years_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(years, 0, wxALIGN_LEFT);

  wxBoxSizer *box1_row = new wxBoxSizer(wxHORIZONTAL);
  box1_row->AddStretchSpacer(1);
  box1_row->Add(box1_flex, 0, wxALIGN_CENTER);
  box1_row->AddStretchSpacer(1);

  wxBoxSizer *box1_column = new wxBoxSizer(wxVERTICAL);
  box1_column->AddStretchSpacer(1);
  box1_column->Add(box1_row, 0, wxALIGN_CENTER);
  box1_column->AddStretchSpacer(1);

  box1->SetSizer(box1_column);

  //Positioning of elements in dialog
  wxBoxSizer *button_row = new wxBoxSizer(wxHORIZONTAL);
  button_row->Add(CreateButtonSizer(wxCANCEL), 0, wxALIGN_LEFT);
  button_row->AddStretchSpacer(1);
  button_row->Add(create, 0, wxALIGN_RIGHT);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->Add(box1, 0, wxRIGHT | wxBOTTOM | wxLEFT | wxEXPAND, 10);
  column->Add(button_row, 0, wxRIGHT | wxLEFT | wxEXPAND, 10);

  SetSizer(column);
}

CurriculumCreator::~CurriculumCreator(){
  ClearErrors();
}//~CurriculumCreator


void CurriculumCreator::DisplayError(int error){
  switch(error){
    case ERROR_NO_CURNAME:
      errors.push_back(new wxStaticText(box1, wxID_ANY, "Curriculum name can't be empty!",
                                        wxPoint(160,10), wxSize(300,17)));
      break;
    case ERROR_NO_CURSEMESTERS:
      errors.push_back(new wxStaticText(box1, wxID_ANY, "Must specify a number of semesters!",
                                        wxPoint(160,50), wxSize(300, 17)));
      break;
    case ERROR_NO_CURYEARS:
      errors.push_back(new wxStaticText(box1, wxID_ANY, "Must specify a number of years!",
                                        wxPoint(160,90), wxSize(300, 17)));
      break;
    case ERROR_CURRICULUM_ALREADY_EXISTS:
      errors.push_back(new wxStaticText(this, wxID_ANY, "The specified curriculum already exists!",
                                        wxPoint(120, 170), wxSize(280, 17)));
      errors[0]->SetForegroundColour(wxColour(wxT("RED")));
      break;
  }
}//DisplayError

std::vector<wxString> CurriculumCreator::getData(){
  std::vector<wxString> data;
  data.push_back(curriculum_name->GetValue());
  data.push_back(semesters->GetValue());
  data.push_back(years->GetValue());
  return data;
}

void CurriculumCreator::OnTextEnter(wxCommandEvent& event){
  int id = event.GetId();
  if(id == ID_CURRICULUM_NAME) //Enter was pressed in the course name box
    years->SetFocus();
  else if(id == ID_CURYEARS) //Enter was pressed in the ects box
    semesters->SetFocus();
  else{ //Enter was pressed in any other box that doesn't inherently handle these events
    wxCommandEvent event(wxEVT_BUTTON, ID_SUBMIT_CURRICULUM);
    wxPostEvent(this, event);
  }
}//OnTextEnter

void CurriculumCreator::OnSubmitCurriculum(wxCommandEvent&){
  ClearErrors(); //Clear the errors of the previous creation attempt
  if(curriculum_name->GetValue() == "")
    DisplayError(ERROR_NO_CURNAME); //No curriculum name was specified
  if(years->GetValue() == "")
    DisplayError(ERROR_NO_CURYEARS); //No years amount specified
  if(semesters->GetValue() == "")
    DisplayError(ERROR_NO_CURSEMESTERS);//No semesters amount specified

  if(errors.size() == 0)
    EndModal(wxID_OK);

  for(unsigned int i = 0; i < errors.size(); i++)
    errors[i]->SetForegroundColour(wxColour(wxT("RED")));
}//OnSubmitCourse

void CurriculumCreator::ClearErrors(){
  for(unsigned int i = 0; i < errors.size(); i++)
    errors[i]->Destroy();
  errors.clear();
}//ClearErrors
