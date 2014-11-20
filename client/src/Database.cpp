/*
  SE 2014
  Group 8
*/
#include "Database.h"
#include "Courses.h"
#include "Semester.h"

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
  this->courses = courses;
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

wxArrayString* Database::getFaculties(){
  wxArrayString *retarray = new wxArrayString();

  sqlite3_stmt *stmt;
  const char *pzt;
  const char* query = "SELECT name FROM curriculum;";
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return retarray;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    retarray->Add(sqlite3_column_text(stmt,0), 1);
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

  return retarray;
}//getFaculties

wxArrayString* Database::getYears(wxString name){
  wxArrayString *retarray = new wxArrayString();

  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT name FROM years WHERE cid IN ") <<
                   wxString("(SELECT id FROM curriculum WHERE name='") << name << wxString("');");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return retarray;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    retarray->Add(sqlite3_column_text(stmt,0), 1);
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

  return retarray;
}//getYears

std::vector<Semester*> Database::populateTree(wxString curname, wxString yearname){
  std::vector<Semester*> ret;

  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT years.id FROM years WHERE years.name='") << yearname <<
                   wxString("' AND years.cid IN (SELECT curriculum.id FROM curriculum ") <<
                   wxString("WHERE curriculum.name='") << curname << wxString("');");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement1");
    sqlite3_finalize(stmt);
    return ret;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    ret = populateTree(sqlite3_column_int(stmt, 0));
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

  return ret;
}

std::vector<Semester*> Database::populateTree(int fid){
  std::vector<Semester*> ret;
  Semester *sem;
  int cursem = -1, type;
  std::vector<Course*> course;
  std::vector<int> index;
  Node *parent = NULL;

  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT columns.ind, lines.id, lines.ind,lines.type,lines.fid") <<
                   wxString(" FROM columns LEFT JOIN lines ON columns.lid=lines.id WHERE") <<
                   wxString(" columns.yid = ") << fid << wxString(";");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement1");
    wxPrintf("%s",query);
    sqlite3_finalize(stmt);
    return ret;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    type = sqlite3_column_int(stmt, 3);
    if(sqlite3_column_int(stmt, 1) == cursem){
      if (type == 1){ //Add course
        index.push_back(sqlite3_column_int(stmt, 2));
        course.push_back(courses->getCourse(sqlite3_column_int(stmt, 4)));
      }
      else if (type == 2){ //Add split
        parent = populateLine(NULL, index, course, sem);
        parent = sem->CreateSplit(parent);
        populateSplit(parent, sem, sqlite3_column_int(stmt, 4));
      }
    }
    else{ //Start constructing a new semester
      if(parent == NULL)
        populateLine(NULL, index, course, sem);
      parent = NULL;
      course.clear();
      index.clear();
      cursem = sqlite3_column_int(stmt, 1);
      if (type == 1){ //normal root
        course.push_back(courses->getCourse(sqlite3_column_int(stmt, 4)));
        index.push_back(sqlite3_column_int(stmt, 2));
        sem = new Semester();
        ret.push_back(sem);
      }
      else if (type == 2){ //split as root (do we really want to even allow this???)
        sem = new Semester();
        sem->SetRoot(NULL);
        parent = sem->GetRoot();
        ret.push_back(sem);
        populateSplit(parent, sem, sqlite3_column_int(stmt, 4));
      }
    }
    rc = sqlite3_step(stmt);
  }
  if(rc == SQLITE_DONE && parent == NULL)
    populateLine(NULL, index, course, sem);
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

  return ret;
}

void Database::populateSplit(Node *splitnode, Semester *sem, int fid){
  Node *parent = NULL;
  std::vector<Course*> course;
  std::vector<int> index;
  int type;

  //left
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT splits.id, lines.id, lines.ind, lines.type, ") <<
                   wxString("lines.fid FROM splits LEFT JOIN lines ON") <<
                   wxString(" splits.left=lines.id") <<
                   wxString(" WHERE splits.id=") << fid << wxString(";");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement2");
    sqlite3_finalize(stmt);
    return;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    type = sqlite3_column_int(stmt, 3);
    if (type == 1){ //Add course
      index.push_back(sqlite3_column_int(stmt, 2));
      course.push_back(courses->getCourse(sqlite3_column_int(stmt, 4)));
    }
    else if (type == 2){ //Add split
      parent = populateLine(splitnode, index, course, sem);
      parent = sem->CreateSplit(parent);
      populateSplit(parent, sem, sqlite3_column_int(stmt, 4));
    }
    rc = sqlite3_step(stmt);
  }
  if(rc == SQLITE_DONE && parent == NULL)
    populateLine(splitnode, index, course, sem);
  if (rc != SQLITE_DONE)
    error("evaluating statement3");
  sqlite3_finalize(stmt);

  course.clear();
  index.clear();
  parent = NULL;
  //right
  query = wxString("SELECT splits.id, lines.id, lines.ind, lines.type, ") <<
          wxString("lines.fid FROM splits LEFT JOIN lines ON") <<
          wxString(" splits.right=lines.id") <<
          wxString(" WHERE splits.id=") << fid << wxString(";");
  rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    type = sqlite3_column_int(stmt, 3);
    if (type == 1){ //Add course
      index.push_back(sqlite3_column_int(stmt, 2));
      course.push_back(courses->getCourse(sqlite3_column_int(stmt, 4)));
    }
    else if (type == 2){ //Add split
      parent = populateLine(splitnode, index, course, sem);
      parent = sem->CreateSplit(parent);
      populateSplit(parent, sem, sqlite3_column_int(stmt, 4));
    }
    rc = sqlite3_step(stmt);
  }
  if(rc == SQLITE_DONE && parent == NULL)
    populateLine(splitnode, index, course, sem);
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

  course.clear();
  index.clear();
}//populatesplit

Node* Database::populateLine(Node *root, std::vector<int> index, std::vector<Course*> course,
                             Semester *sem){
  Node *retnode = root;
  int i,j;
  for(i = 1; i < course.size()+1; i++){
    for(j = 0; j < course.size(); j++){
      if(i = index[j]){
        if(i == 1 && retnode == NULL){
          sem->SetRoot(course[j]);
          retnode = sem->GetRoot();
        }
        else
          retnode = sem->AddChild(retnode, course[j]);
      }
    }
  }
  return retnode;
}//populateLine