/*
  SE 2014
  Group 8
*/

#include "Courses.h"

Courses::Courses(){

}//Courses

Courses::~Courses(){
  affiliations.clear();
  course_types.clear();
  all_courses.clear();
}//~Courses

void Courses::addCourse(unsigned int ID, wxString name, wxString line, wxString number,
                       unsigned int ects, unsigned int affiliation, unsigned int type){
  int i;
  Course course = {ID, name, line, number, ects, wxColour(wxT("RED")), wxColour(wxT("RED"))};
  for(i = 0; i < affiliations.size(); i++){
    if(affiliations[i].ID == affiliation)
      course.affiliation = affiliations[i].colour;
  }
  for(i = 0; i < course_types.size(); i++){
    if(course_types[i].ID == type)
      course.type = course_types[i].colour;
  }
  all_courses.push_back(course);
}//addCourse

int Courses::addCourse(unsigned int ID, wxString name, wxString line, wxString number,
                       unsigned int ects, unsigned int affiliation, unsigned int type, bool add){
  //check if course already exists!
  //if not add it to database!
  addCourse(ID, name, line, number, ects, affiliation, type);
  return 1;
}//addCourse


void Courses::addAffiliation(unsigned int ID, wxColour colour){
  ColourAttribute aff = {ID, colour};
  affiliations.push_back(aff);
}//addAffiliation

void Courses::addCourseType(unsigned int ID, wxColour colour){
  ColourAttribute ct = {ID, colour};
  course_types.push_back(ct);
}//addCourseType

Course Courses::getCourse(unsigned int ID){
  Course course = Course();
  int index = search(ID);
  if(index != -1)
    course = all_courses[index];
  return course;
}//getCourse

int Courses::search(unsigned int ID){
  int min = 0,
      max = all_courses.size()-1,
      mid;
  while(max >= min){
    mid = min + ((max - min) / 2);
    if(all_courses[mid].ID == ID)
      return mid;
    else if(all_courses[mid].ID < ID)
      min = mid + 1;
    else
      max = mid - 1;
  }
  return -1; //ID doesn't exist
}//search
