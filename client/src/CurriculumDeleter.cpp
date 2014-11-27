/*
  SE 2014
  Group 8
*/

#include "CurriculumDeleter.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(CurriculumDeleter, wxDialog)
  EVT_BUTTON            (ID_DELETE_STUDY_PROGRAM, CurriculumDeleter::OnDeleteCurriculum)
wxEND_EVENT_TABLE()

CurriculumDeleter::CurriculumDeleter(wxFrame *frame, Database *database)
      :wxDialog(frame, wxID_ANY, wxT("Curriculum deleter"), wxPoint(100,100), wxSize(500, 130),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP)
{
  wxStaticText *study_program_text = new wxStaticText(this, -1, "Study Program:");
  wxFont font = study_program_text->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  study_program_text->SetFont(font);

  wxArrayString *sp = database->getFaculties();
  study_program = new wxComboBox(this, wxID_ANY, wxT(""), wxPoint(120,27),
                                 wxSize(300,25), *sp, wxCB_READONLY);
  study_program->SetSelection(0);

  //Create button
  wxButton *create = new wxButton(this, ID_DELETE_STUDY_PROGRAM, wxT("Delete"));
  if(study_program->GetCount() == 0)
    create->Enable(false);

  //Positioning of elements in dialog
  wxFlexGridSizer *flex = new wxFlexGridSizer(1, 2, 25, 10);
  flex->Add(study_program_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  flex->Add(study_program, 0, wxALIGN_LEFT);

  wxBoxSizer *button_row = new wxBoxSizer(wxHORIZONTAL);
  button_row->Add(CreateButtonSizer(wxCANCEL), 0, wxALIGN_LEFT);
  button_row->AddStretchSpacer(1);
  button_row->Add(create, 0, wxALIGN_RIGHT);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->Add(flex, 0, wxALL | wxEXPAND, 10);
  column->Add(button_row, 0, wxRIGHT | wxLEFT | wxEXPAND, 10);

  SetSizer(column);
}//CourseCreator

CurriculumDeleter::~CurriculumDeleter(){

}//~CourseCreator

void CurriculumDeleter::OnDeleteCurriculum(wxCommandEvent& event){
  EndModal(wxID_OK);
}//OnSubmitCourse

std::vector<wxString> CurriculumDeleter::getData(){
  std::vector<wxString> data;
  data.push_back(study_program->GetValue());
  return data;
}//getData