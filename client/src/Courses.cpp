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
  unsigned int i;
  Course * course = new Course();
  course->ID = ID;
  course->name = name;
  course->line = line;
  course->number = number;
  course->ects = ects;
  course->affiliation = wxColour(wxT("RED"));
  course->type = wxColour(wxT("RED"));
  for(i = 0; i < affiliations.size(); i++){
    if(affiliations[i].ID == affiliation)
      course->affiliation = affiliations[i].colour;
  }
  for(i = 0; i < course_types.size(); i++){
    if(course_types[i].ID == type)
      course->type = course_types[i].colour;
  }
  course->bitmap = DrawingHelper::drawCourse(course);
  all_courses.push_back(course);
}//addCourse

int Courses::addNewCourse(std::vector<wxString> data){
  //check if course already exists!
  //if not add it to database!
  int ects = wxAtoi(data[1]);
  unsigned int i;
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

Course * Courses::getCourse(unsigned int ID){
  Course * course = NULL;
  int index = search(ID);
  if(index != -1)
    course = all_courses[index];
  return course;
}//getCourse

wxColour Courses::getAffiliationColour(wxString name){
  for(unsigned int i = 0; i < affiliations.size(); i++){
    if(affiliations[i].name == name)
      return affiliations[i].colour;
  }
  return wxColour(wxT("RED"));
}

wxColour Courses::getTypeColour(wxString name){
  for(unsigned int i = 0; i < course_types.size(); i++){
    if(course_types[i].name == name)
      return course_types[i].colour;
  }
  return wxColour(wxT("RED"));
}

wxString Courses::getAffiliationName(wxColour colour){
  for(unsigned int i = 0; i < affiliations.size(); i++){
    if(affiliations[i].colour == colour)
      return affiliations[i].name;
  }
  return wxT("");
}

wxString Courses::getTypeName(wxColour colour){
  for(unsigned int i = 0; i < course_types.size(); i++){
    if(course_types[i].colour == colour)
      return course_types[i].name;
  }
  return wxT("");
}

std::vector<Course *> Courses::filter(SearchPars pars){
  std::vector<int> ids = database->filter(pars);
  std::vector<Course *> ret;

  int index;
  for (unsigned i = 0; i < ids.size(); i++){
    index = search(ids[i]);
    if (index > -1)
      ret.push_back(all_courses[index]);
  }
  return ret;
}

int Courses::deleteCourse(unsigned int ID){
  for(unsigned int i = 0; i < all_courses.size(); i++){
    if(all_courses[i]->ID == ID){
      all_courses.erase(all_courses.begin() + i);
    }
  }
  return database->deleteCourse(ID);
}

int Courses::editCourse(unsigned int ID, std::vector<wxString> data){
  int ects = wxAtoi(data[1]);
  unsigned int i, j;
  unsigned int affiliation = 1, course_type = 1;
  for(i = 0; i < affiliations.size(); i++){
    if(affiliations[i].name == data[2]){
      affiliation = affiliations[i].ID;
      break;
    }
  }
  for(j = 0; j < course_types.size(); j++){
    if(course_types[j].name == data[3]){
      course_type = course_types[j].ID;
      break;
    }
  }

  int ret = database->editCourse(ID, data[0], data[4], data[5], ects, affiliation, course_type);
  if(ret >= 0){
    for(unsigned int k = 0; k < all_courses.size(); k++){
      if(all_courses[k]->ID == ID){
        all_courses[k]->name = data[0];
        all_courses[k]->line = data[4];
        all_courses[k]->number = data[5];
        all_courses[k]->ects = ects;
        all_courses[k]->affiliation = affiliations[i].colour;
        all_courses[k]->type = course_types[j].colour;
        all_courses[k]->bitmap = DrawingHelper::drawCourse(all_courses[k]);
      }
    }
  }
  return ret;
}

int Courses::search(unsigned int ID){
  int min = 0,
      max = all_courses.size()-1,
      mid;
  while(max >= min){
    mid = min + ((max - min) / 2);
    if(all_courses[mid]->ID == ID)
      return mid;
    else if(all_courses[mid]->ID < ID)
      min = mid + 1;
    else
      max = mid - 1;
  }
  return -1; //ID doesn't exist
}//search