/*
  SE 2014
  Group 8
*/

#include "Overview.h"

Overview::Overview(wxFrame *frame, int x, int y, int w, int h)
      :wxPanel(frame, wxID_ANY, wxPoint(x,y), wxSize(w, h))
{
  curricula = new wxBookCtrl(this, ID_CURRICULA);

  //Set an empty curriculum to initially fill the screen
  Curriculum *temporary_curriculum = new Curriculum(curricula);
  temporary_curriculum->SetBackgroundColour(wxColour(120,120,120));
  curricula->AddPage(temporary_curriculum, wxT("Empty"), true);
  tabs.push_back(temporary_curriculum);

  //Setup the catalogue
  catalogue = new Catalogue(this);
  catalogue->SetBackgroundColour(wxColour(150,150,150));

  //Position the curricula and catalogue
  wxBoxSizer *row = new wxBoxSizer(wxHORIZONTAL);
  row->AddSpacer(5);
  row->Add(curricula, 1, wxEXPAND);
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
  tabs.clear();
}

void Overview::OnCloseTab(){
  int page = curricula->GetSelection();
  curricula->RemovePage(page);
  tabs.erase(tabs.begin() + page);
}//OnCloseTab