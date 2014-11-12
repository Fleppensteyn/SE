/*
  SE 2014
  Group 8
*/

#ifndef DATABASE_H_
#define DATABASE_H_

#include "sqlite/sqlite3.h"

//#include "wx/string.h"

class Courses;
class wxString;

enum
{
  FILL_AFFILLIATIONS,
  FILL_COURSETYPES
};

class Database
{
public:
  Database(const char* filename);
  virtual ~Database();
  void fillCourses(Courses* courses);
  int addNewCourse(wxString name, wxString line, wxString number, unsigned int ects,
                   wxString affiliation, wxString type);

private:
  bool connect();
  void error(const char* msg);
  void fillColours(Courses* courses, int filltype);

  sqlite3 *db;
  const char* filename;
};

#endif /* DATABASE_H_ */