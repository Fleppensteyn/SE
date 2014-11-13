/*
  SE 2014
  Group 8
*/

#include "CurriculumCreator.h"

CurriculumCreator::CurriculumCreator(wxFrame *frame)
      :wxDialog(frame, wxID_ANY, wxT("Curriculum creation"), wxPoint(100,100), wxSize(500, 400),
       wxDEFAULT_DIALOG_STYLE | wxSTAY_ON_TOP){
	
}

std::vector<wxString> CurriculumCreator::getData(){
	
}
