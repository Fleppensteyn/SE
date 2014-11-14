/*
  SE 2014
  Group 8
*/

#include "Courses.h"

Courses::Courses(Database *database){
  this->database = database;
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

int Courses::addNewCourse(std::vector<wxString> data){
  //check if course already exists!
  //if not add it to database!
  int ects = wxAtoi(data[1]);
  int i;
  unsigned int affiliation = 1, course_type = 1;
  for(i = 0; i < affiliations.size(); i++){
    if(affiliations[i].name == data[2])
      affiliation = affiliations[i].ID;
  }
  for(i = 0; i < course_types.size(); i++){
    if(course_types[i].name == data[3])
      course_type = course_types[i].ID;
  }

  int ret = database->addNewCourse(data[0], data[4], data[5], ects, affiliation, course_type);
  if(ret >= 0)
    addCourse(ret, data[0], data[4], data[5], ects, affiliation, course_type);
  return ret;
}//addCourse


void Courses::addAffiliation(unsigned int ID, wxString name, wxColour colour){
  ColourAttribute aff = {ID, name, colour};
  affiliations.push_back(aff);
}//addAffiliation

void Courses::addCourseType(unsigned int ID, wxString name, wxColour colour){
  ColourAttribute ct = {ID, name, colour};
  course_types.push_back(ct);
}//addCourseType

Course Courses::getCourse(unsigned int ID){
  Course course = Course();
  int index = search(ID);
  if(index != -1)
    course = all_courses[index];
  return course;
}//getCourse

wxColour Courses::getAffiliationColour(wxString name){
  for(int i = 0; i < affiliations.size(); i++){
    if(affiliations[i].name == name)
      return affiliations[i].colour;
  }
}

wxColour Courses::getTypeColour(wxString name){
  for(int i = 0; i < course_types.size(); i++){
    if(course_types[i].name == name)
      return course_types[i].colour;
  }
}

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

std::vector<Course> Courses::getCourseVec(){
  return all_courses;
}
