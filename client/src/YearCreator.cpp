/*
  SE 2014
  Group 8
*/

#include "YearCreator.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(YearCreator, wxDialog)
  EVT_BUTTON            (ID_SUBMIT_YEAR, YearCreator::OnSubmitYear)
  EVT_TEXT_ENTER        (wxID_ANY, YearCreator::OnTextEnter)
wxEND_EVENT_TABLE()

YearCreator::YearCreator(wxFrame *frame, Database *database)
      :wxDialog(frame, wxID_ANY, wxT("Year creation"), wxPoint(100,100), wxSize(500, 200),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
  //Static boxes and static text elements
  box1 = new wxStaticBox(this, wxID_ANY, "Year specifics", wxPoint(20, 10),
                         wxSize(460, 120));

  wxFont font = box1->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  wxStaticText *study_program_text = new wxStaticText(box1, -1, "Study program:");
  study_program_text->SetFont(font);
  wxStaticText *year_name_text = new wxStaticText(box1, -1, "Year:");
  year_name_text->SetFont(font);

  wxArrayString *sp = database->getFaculties();
  study_program = new wxComboBox(box1, ID_STUDY_PROGRAM, wxT(""), wxPoint(120,27),
                               wxSize(300,25), *sp, wxCB_READONLY | wxTE_PROCESS_ENTER);
  study_program->SetSelection(0);
  year_name = new wxTextCtrl(box1, ID_YEAR_NAME, wxT("1"), wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT, wxTextValidator(wxFILTER_DIGITS));
  year_name->SetMaxLength(2);

  //Create button
  wxButton *create = new wxButton(this, ID_SUBMIT_YEAR, wxT("Create"));// this course"));

  //Positioning of elements in box1
  wxFlexGridSizer *box1_flex = new wxFlexGridSizer(2, 2, 15, 10);
  box1_flex->Add(study_program_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(study_program, 0, wxALIGN_LEFT);
  box1_flex->Add(year_name_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(year_name, 0, wxALIGN_LEFT);

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
  column->Add(box1, 0, wxALL | wxEXPAND, 10);
  column->Add(button_row, 0, wxRIGHT | wxLEFT | wxEXPAND, 10);

  SetSizer(column);
}//CourseCreator

YearCreator::~YearCreator(){
  ClearErrors();
}//~CourseCreator

void YearCreator::DisplayError(int error){
  switch(error){
    case ERROR_NO_YEAR:
      errors.push_back(new wxStaticText(box1, wxID_ANY, "Year can't be empty!",
                                        wxPoint(150,50), wxSize(300,17)));
      break;
    case ERROR_YEAR_ALREADY_EXISTS:
      errors.push_back(new wxStaticText(this, wxID_ANY, "Year already exists!",
                                        wxPoint(120, 140), wxSize(200, 17)));
      errors[0]->SetForegroundColour(wxColour(wxT("RED")));
      break;
  }
}//DisplayError

std::vector<wxString> YearCreator::getData(){
  std::vector<wxString> data;
  data.push_back(study_program->GetValue());
  data.push_back(year_name->GetValue());
  return data;
}//getData

void YearCreator::OnTextEnter(wxCommandEvent&){
  wxCommandEvent event(wxEVT_BUTTON, ID_SUBMIT_YEAR);
  wxPostEvent(this, event);
}//OnTextEnter

void YearCreator::OnSubmitYear(wxCommandEvent&){
  ClearErrors(); //Clear the errors of the previous creation attempt
  if(year_name->GetValue() == "")
    DisplayError(ERROR_NO_YEAR); //No course name was specified

  if(errors.size() == 0)
    EndModal(wxID_OK);

  for(unsigned int i = 0; i < errors.size(); i++)
    errors[i]->SetForegroundColour(wxColour(wxT("RED")));
}//OnSubmitCourse

void YearCreator::ClearErrors(){
  for(unsigned int i = 0; i < errors.size(); i++)
    errors[i]->Destroy();
  errors.clear();
}//ClearErrors