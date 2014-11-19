/*
  SE 2014
  Group 8
*/
#include "Database.h"
#include "Courses.h"

Database::Database(const char* filename){
  this->filename = filename;
  if(!connect())
    throw 1;
}
Database::~Database(){
  sqlite3_close(this->db);
  // delete filename;
}

bool Database::connect(){
  int rc = sqlite3_open(filename, &this->db);
  if (rc){
    error("opening database");
    sqlite3_close(this->db);
    return false;
  }
  return true;
}

void Database::error(const char* msg){
  fprintf(stderr, "Error: While %s - %s \n", msg, sqlite3_errmsg(this->db));
}

void Database::fillColours(Courses* courses, int filltype){
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query;

  switch (filltype){
    case FILL_AFFILLIATIONS:query += "SELECT * FROM affiliations;"; break;
    case FILL_COURSETYPES: query += "SELECT * FROM course_types;"; break;
    default: fprintf(stderr, "Error: While filling colour table - Unknown table type\n");return; break;
  }

  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing colour filling statement");
    sqlite3_finalize(stmt);
    return;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    wxString tcs("#");
    switch (filltype){
      case FILL_AFFILLIATIONS: courses->addAffiliation(sqlite3_column_int(stmt, 0),
                                          wxString(sqlite3_column_text(stmt,1)),
                                          wxColour(tcs+sqlite3_column_text(stmt, 2))); break;
      case FILL_COURSETYPES: courses->addCourseType(sqlite3_column_int(stmt, 0),
                                          wxString(sqlite3_column_text(stmt,1)),
                                          wxColour(tcs+sqlite3_column_text(stmt, 2))); break;
    }
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating colour filling statement");
  sqlite3_finalize(stmt);
}

void Database::fillCourses(Courses* courses){
  // void (*addAffil) (unsigned int, wxColour) = &courses->addAffiliation;
  fillColours(courses, FILL_AFFILLIATIONS);
  fillColours(courses, FILL_COURSETYPES);

  // void (*addCType) (unsigned int, wxColour) = &courses->addCourseType;
  // fillColours("SELECT id, colour FROM course_types;", addCType);

  sqlite3_stmt *stmt;
  const char *pzt;
  const char* query = "SELECT * FROM courses;";
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    courses->addCourse(sqlite3_column_int(stmt, 0),
                       wxString::FromUTF8((const char *)sqlite3_column_text(stmt,1)),
                       wxString::FromUTF8((const char *)sqlite3_column_text(stmt,2)),
                       wxString::FromUTF8((const char *)sqlite3_column_text(stmt,3)),
                       sqlite3_column_int(stmt, 4),
                       sqlite3_column_int(stmt, 5),
                       sqlite3_column_int(stmt, 6));
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);
}

int Database::addNewCourse(wxString name, wxString line, wxString number, int ects,
                           unsigned int affiliation, unsigned int type){
  int ret;
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("INSERT INTO courses(name, line, number, ects, affilid, typeid)")
                   << wxString(" VALUES ('") << name << wxString("' ,'") << line <<
                   wxString("' ,'") << number << wxString("' ,'") << ects <<
                   wxString("' ,'") << affiliation << wxString("' ,'") << type << wxString("');");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("Preparing statment");
    sqlite3_finalize(stmt);
    return -1;
  }
  rc = sqlite3_step(stmt);
  if(rc == SQLITE_ERROR)
    ret = -1;
  else
    ret = sqlite3_last_insert_rowid(this->db);
  sqlite3_finalize(stmt);
  return ret;
}

std::vector<int> Database::filter(SearchPars par){
  std::vector<int> ret;
  sqlite3_stmt *stmt;
  const char *pzt;

  wxString where = wxString("");
  wxString query = wxString("SELECT id FROM courses ") << where
            << "ORDER BY typeid ASC, affilid ASC, number ASC;";

  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return ret;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    ret.push_back(sqlite3_column_int(stmt, 0));
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);
  return ret;
}