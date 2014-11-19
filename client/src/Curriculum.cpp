/*
  SE 2014
  Group 8
*/

#include "Curriculum.h"

Curriculum::Curriculum(wxPanel *overview)
      :wxScrolledCanvas(overview, wxID_ANY, wxPoint(100,100), wxSize(curriculum_width, 100))
{

}

Curriculum::~Curriculum(){

}

void Curriculum::DrawCurriculum(){
  /* 	TODO:
      print een course in een vak met nader te bepalen lengte (bijvoorbeeld 150 met spacer van 25, totaal moet 500 zijn)
      zet een spacer om een klein stukje wit toe te voegen na ieder vak. Doe dit ook tussen regels
  */
}

void Curriculum::UpdateCourse(Course toUpdate){
  /*  TODO:
      Zoek het vak in het curriculum
      Gevonden: Vervang de oude entry met toUpdate
      Niet gevonden: print foutmelding
  */
}
