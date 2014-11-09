/*
  SE 2014
  Group 8
*/

#include "Curriculum.h"
Curriculum::Curriculum(wxBookCtrl *curricula)
      :wxPanel(curricula, wxID_ANY, wxPoint(50,100), wxSize(500, 500))
{
  numberOfCourses = 0;
  /*Hier kunnen we het courses array doorlopen en iedere entry een leeg vak maken voor de netheid*/
}

Curriculum::~Curriculum(){
  
}

void Curriculum::AddCourse(/*Course newCourse*/){
	numberOfCourses++;
	/*courses[numberOfCourses] = newCourse; */
}

void Curriculum::DeleteCourse(/*Course toDelete*/){
	/*Verwijder het vak, afhankelijk van Course-datastructuur*/
	numberOfCourses--;
}

void Curriculum::ShowCurriculum(){
	/* 	TODO:
			loop courses array door
			print een course in een vak met nader te bepalen lengte (bijvoorbeeld 150 met spacer van 25, totaal moet 500 zijn)
			zet een spacer om een klein stukje wit toe te voegen na ieder vak. Doe dit ook tussen regels
			scroll?
	*/
}

void Curriculum::UpdateCourse(/*Course toUpdate*/){
	/*	TODO:
			Zoek het vak in het curriculum
			Gevonden: Vervang de oude entry met toUpdate
			Niet gevonden: print foutmelding
	*/
}
