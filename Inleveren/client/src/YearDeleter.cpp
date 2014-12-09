/*
  SE 2014
  Group 8
*/

#include "YearDeleter.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(YearDeleter, wxDialog)
  EVT_TEXT              (ID_DELETER_STUDY_PROGRAM, YearDeleter::OnUpdateCurriculum)
  EVT_BUTTON            (ID_DELETER_DELETE_YEAR, YearDeleter::OnDeleteYear)
wxEND_EVENT_TABLE()

YearDeleter::YearDeleter(wxFrame *frame, Database *database)
      :wxDialog(frame, wxID_ANY, wxT("Year deleter"), wxPoint(100,100), wxSize(500, 180),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
  this->database = database;

  wxStaticText *study_program_text = new wxStaticText(this, -1, "Study program:");
  wxFont font = study_program_text->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  study_program_text->SetFont(font);
  wxStaticText *year_text = new wxStaticText(this, -1, "Year:");
  year_text->SetFont(font);

  wxArrayString *sp = database->getFaculties();
  study_program = new wxComboBox(this, ID_DELETER_STUDY_PROGRAM, wxT(""), wxPoint(120,27),
                                 wxSize(300,25), *sp, wxCB_READONLY);
  study_program->SetSelection(0);

  wxArrayString *sy = database->getYears(study_program->GetValue());
  year = new wxComboBox(this, wxID_ANY, wxT(""), wxPoint(120,67), wxSize(300,25), *sy, wxCB_READONLY);
  year->SetSelection(0);

  //Create button
  create = new wxButton(this, ID_DELETER_DELETE_YEAR, wxT("Delete"));
  if(year->GetCount() == 0)
    create->Enable(false);

  //Positioning of elements in dialog
  wxFlexGridSizer *flex = new wxFlexGridSizer(2, 2, 25, 10);
  flex->Add(study_program_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  flex->Add(study_program, 0, wxALIGN_LEFT);
  flex->Add(year_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  flex->Add(year, 0, wxALIGN_LEFT);

  wxBoxSizer *button_row = new wxBoxSizer(wxHORIZONTAL);
  button_row->Add(CreateButtonSizer(wxCANCEL), 0, wxALIGN_LEFT);
  button_row->AddStretchSpacer(1);
  button_row->Add(create, 0, wxALIGN_RIGHT);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->Add(flex, 0, wxALL | wxEXPAND, 10);
  column->Add(button_row, 0, wxRIGHT | wxLEFT | wxEXPAND, 10);

  SetSizer(column);
}//CourseCreator

YearDeleter::~YearDeleter(){

}//~CourseCreator

std::vector<wxString> YearDeleter::getData(){
  std::vector<wxString> data;
  data.push_back(study_program->GetValue());
  data.push_back(year->GetValue());
  return data;
}//getData

void YearDeleter::OnDeleteYear(wxCommandEvent&){
  EndModal(wxID_OK);
}//OnSubmitCourse

void YearDeleter::OnUpdateCurriculum(wxCommandEvent&){
  wxArrayString *sy = database->getYears(study_program->GetValue());
  year->Clear();
  year->Append(*sy);
  year->SetSelection(0);
  if(year->GetCount() == 0){
    create->Enable(false);
  }
  else{
    create->Enable(true);
  }
}