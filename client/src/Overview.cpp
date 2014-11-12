/*
  SE 2014
  Group 8
*/

#include "Overview.h"

Overview::Overview(wxFrame *frame, int x, int y, int w, int h)
      :wxPanel(frame, wxID_ANY, wxPoint(x,y), wxSize(w, h))
{
  this->database = new Database("client.db");
  this->courses = new Courses(this->database);
  this->mousemanager = new MouseManager(this);
  this->database->fillCourses(this->courses);

  curricula = new wxBookCtrl(this, ID_CURRICULA);

  //Set an empty curriculum to initially fill the screen
  Curriculum *temporary_curriculum = new Curriculum(curricula);
  temporary_curriculum->SetBackgroundColour(wxColour(120,120,120));
  curricula->AddPage(temporary_curriculum, wxT("Empty"), true);
  tabs.push_back(temporary_curriculum);

  //Setup the catalogue
  catalogue = new Catalogue(this, this->courses);
  catalogue->SetBackgroundColour(wxColour("#FFFFFF"));

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
  delete mousemanager;
  delete courses;
  delete database;
}

void Overview::OnCloseTab(){
  int page = curricula->GetSelection();
  curricula->RemovePage(page);
  tabs.erase(tabs.begin() + page);
}//OnCloseTab
