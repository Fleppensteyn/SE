/*
  SE 2014
  Group 8
*/

#include "CurriculumCreator.h"

CurriculumCreator::CurriculumCreator(wxFrame *frame)
      :wxDialog(frame, wxID_ANY, wxT("Curriculum creation"), wxPoint(100,100), wxSize(500, 300),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP){
	
	box1 = new wxStaticBox(this, wxID_ANY, "Course specifics", wxPoint(20, 10),
                         wxSize(460, 200));
	
	wxFont font = box1->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  wxStaticText *name_text = new wxStaticText(box1, -1, "Curriculum Name:");
  name_text->SetFont(font);
  wxStaticText *years_text = new wxStaticText(box1, -1, "Affiliation:");
  years_text->SetFont(font);
  wxStaticText *semesters_text = new wxStaticText(box1, -1, "Semesters per year:");
  semesters_text->SetFont(font);
  wxStaticText *affiliation_text = new wxStaticText(box1, -1, "Affiliation:");
  affiliation_text->SetFont(font);
	
	//Curriculum name input box
  curriculum_name = new wxTextCtrl(box1, ID_CURRICULUM_NAME, wxT(""), wxPoint(120, 27), wxSize(300, 25),
                              wxTE_PROCESS_ENTER);
  curriculum_name->SetHint("curriculum name");
  curriculum_name->SetFocus();
  curriculum_name->SetMaxLength(50);

	//Years input box
	years = new wxTextCtrl(box1, ID_SEMESTERS, wxT("3"), wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT, wxTextValidator(wxFILTER_DIGITS));
  years->SetMaxLength(2);
	
	//Semesters per year input box
  semesters = new wxTextCtrl(box1, ID_SEMESTERS, wxT("2"), wxPoint(120, 67), wxSize(40, 25),
                        wxTE_PROCESS_ENTER | wxTE_RIGHT, wxTextValidator(wxFILTER_DIGITS));
  semesters->SetMaxLength(2);
  
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
  affiliation = new wxComboBox(box1, ID_AFFILIATION, wxT("Affiliated to CS"), wxPoint(120,27),
                               wxSize(300,25), *affiliations, wxCB_READONLY | wxTE_PROCESS_ENTER);
  
  //Create button
  wxButton *create = new wxButton(this, ID_SUBMIT_CURRICULUM, wxT("Create"));

  //Positioning of elements
  wxFlexGridSizer *box1_flex = new wxFlexGridSizer(5, 2, 15, 10);
  box1_flex->Add(name_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(curriculum_name, 0, wxALIGN_LEFT);
  box1_flex->Add(semesters_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(semesters, 0, wxALIGN_LEFT);
  box1_flex->Add(affiliation_text, 0, wxALIGN_RIGHT | wxTOP, 3);
  box1_flex->Add(affiliation, 0, wxALIGN_LEFT);
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

  this->curriculum = curriculum;
}

std::vector<wxString> CurriculumCreator::getData(){
	
}
