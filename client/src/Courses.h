/*
  SE 2014
  Group 8
*/

#ifndef COURSES_H_
#define COURSES_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Database.h"
#include <vector>

struct ColourAttribute{
  unsigned int ID;
  wxColour colour;
};

struct Course{
  unsigned int ID;
  wxString name;
  wxString line;
  wxString number;
  unsigned int ects;
  wxColour affiliation;
  wxColour type;
};

//Contains all gui elements and functionality of a single curriculum
class Courses
{
public:
  Courses(Database *database);

  ~Courses();

  void addCourse(unsigned int ID, wxString name, wxString line, wxString number, unsigned int ects,
                unsigned int affiliation, unsigned int type);

  int addNewCourse(std::vector<wxString> data);

  void addAffiliation(unsigned int ID, wxColour colour);

  void addCourseType(unsigned int ID, wxColour colour);

  Course getCourse(unsigned int ID);

  int search(unsigned int ID);

private:
  std::vector<ColourAttribute> affiliations;
  std::vector<ColourAttribute> course_types;
  std::vector<Course> all_courses;

  Database *database;
};

#endif /* COURSES_H_ */