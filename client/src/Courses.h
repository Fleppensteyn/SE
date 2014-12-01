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
#include "DrawingHelper.h"
#include <vector>

struct ColourAttribute{
  unsigned int ID;
  wxString name;
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
  wxBitmap bitmap;
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

  void addAffiliation(unsigned int ID, wxString name, wxColour colour);

  void addCourseType(unsigned int ID, wxString name, wxColour colour);

  Course * getCourse(unsigned int ID);

  wxColour getAffiliationColour(wxString name);

  wxColour getTypeColour(wxString name);

  wxString getAffiliationName(wxColour colour);

  wxString getTypeName(wxColour colour);

  std::vector<Course *> filter(SearchPars pars);

  int deleteCourse(unsigned int ID);

  int editCourse(unsigned int ID, std::vector<wxString> data);


private:
  std::vector<ColourAttribute> affiliations;
  std::vector<ColourAttribute> course_types;
  std::vector<Course*> all_courses;

  Database *database;

  int search(unsigned int ID);
};

#endif /* COURSES_H_ */
