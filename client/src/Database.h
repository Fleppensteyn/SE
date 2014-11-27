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

struct InsertData
{
  int yid;
  int cid;
  int columncount;
  int splitcount;
  int columnoffset;
  int splitsoffset;
  std::vector<std::vector<int> > lines;
  std::vector<std::vector<int> > columns;
  std::vector<std::vector<int> > splits;
  std::vector<int> ids;
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
  int addCurriculum(wxString name, int semesters, int years);
  int addYear(wxString curname, int year);
  int addYear(int cid, int year);
  int deleteCourse(unsigned int ID);
  int editCourse(unsigned int ID, wxString name, wxString line, wxString number, int ects,
                 unsigned int affiliation, unsigned int type);
  bool deleteYear(wxString curname, wxString yearname);
  void saveYear(wxString curname, wxString yearname, std::vector<Semester*>& tree);

private:
  bool connect();
  void error(const char* msg);
  void fillColours(Courses* courses, int filltype);

  void getPopulation(int fid);
  void orderPopulation(std::vector<std::vector<std::vector<int> > > pop);
  void populateLine(int ind, Node *parent, Semester *sem);
  void populateSplit(int fid, Node *splitnode, Semester *sem);

  bool deleteYear(int yid);
  int simpleQuery(wxString query, const char * errormsg);
  int selectSingleInt(wxString query, int& rc, const char * errormsg);
  std::vector<std::vector<int> > selectIntVector(wxString query, int& rc, const char * errormsg);
  void processLine(Node * root, InsertData& idat, int column);
  int getSemesters(wxString name);

  std::vector<std::vector<std::vector<int> > > pop;
  Courses *courses;
  sqlite3 *db;
  const char* filename;
};

#endif /* DATABASE_H_ */