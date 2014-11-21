/*
  SE 2014
  Group 8
*/

#ifndef DATABASE_H_
#define DATABASE_H_

#include "sqlite/sqlite3.h"
#include <vector>

//#include "wx/string.h"

class Courses;
struct Course;
class Node;
class Semester;
class wxString;
class wxArrayString;

enum
{
  FILL_AFFILLIATIONS,
  FILL_COURSETYPES
};

struct SearchPars
{
  int category;
  int affiliation;
  int ects;
  char * pattern;
};

class Database
{
public:
  Database(const char* filename);
  virtual ~Database();
  void fillCourses(Courses* courses);
  int addNewCourse(wxString name, wxString line, wxString number, int ects,
                   unsigned int affiliation, unsigned int type);
  std::vector<int> filter(SearchPars par);
  wxArrayString* getFaculties();
  wxArrayString* getYears(wxString name);
  std::vector<Semester*> populateTree(wxString curname, wxString yearname);

private:
  bool connect();
  void error(const char* msg);
  void fillColours(Courses* courses, int filltype);

  void getPopulation(int fid);
  void orderPopulation(std::vector<std::vector<std::vector<int> > > pop);
  void populateLine(int ind, Node *parent, Semester *sem);
  void populateSplit(int fid, Node *splitnode, Semester *sem);

  std::vector<std::vector<std::vector<int> > > pop;
  Courses *courses;
  sqlite3 *db;
  const char* filename;
};

#endif /* DATABASE_H_ */