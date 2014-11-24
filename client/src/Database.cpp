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
  pop.clear();
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
  Semester *sem;
  int i;

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
    getPopulation(sqlite3_column_int(stmt, 0));
    for(i = 0; i < pop.size(); i++){
      if(pop[i][0][0] != -1){
        sem = new Semester();
        populateLine(i, NULL, sem);
        ret.push_back(sem);
      }
    }
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

  return ret;
}

void Database::getPopulation(int fid){
  pop.clear();
  int curind = -1, indind,
      curline = -1, lineind;
  int i1 = -1,i2 = -1;

  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT columns.ind, lines.id, lines.ind,lines.type,lines.fid") <<
                   wxString(" FROM columns LEFT JOIN lines ON columns.lid=lines.id WHERE") <<
                   wxString(" columns.yid = ") << fid << wxString(";");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    indind = sqlite3_column_int(stmt, 2);
    lineind = sqlite3_column_int(stmt, 1);
    if (curline != lineind){
      std::vector<std::vector<int> > temp;
      pop.push_back(temp);
      curline = lineind;
      i1++;
      i2 = -1;
    }
    if (curind != indind){
      std::vector<int> temp;
      pop[i1].push_back(temp);
      curind = indind;
      i2++;
    }
    for(int i = 0; i < 5; i++)
      pop[i1][i2].push_back(sqlite3_column_int(stmt, i));
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);
  orderPopulation(pop);
}//getPopulation

void Database::orderPopulation(std::vector<std::vector<std::vector<int> > > pop){
  std::vector<std::vector<int> > tempcur;
  std::vector<int> templine;
  //Order on semester
  int i, j, k, l;
  for(i = 0; i < pop.size(); i++){
    k = i;
    for(j = i+1; j < pop.size(); j++){
      if(pop[j][0][0] < pop[k][0][0])
        k = j;
    }
    if(i == k){
      tempcur = pop[i];
      pop[i] = pop[k];
      pop[k] = tempcur;
    }
  }
  for(l = 0; l < pop.size(); l++){
    for(i = 0; i < pop[l].size(); i++){
      k = i;
      for(j = i+1; j < pop[l].size(); j++){
        if(pop[l][j][2] < pop[l][k][2])
          k = j;
      }
      if(i == k){
        templine = pop[l][i];
        pop[l][i] = pop[l][k];
        pop[l][k] = templine;
      }
    }
  }
}//orderPopulation

void Database::populateLine(int ind, Node *parent, Semester *sem){
  Course *course;
  Node *par = parent;
  int i = 0;
  if (par == NULL){
    //create new semester
    switch(pop[ind][0][3]){
      case 1: //normal root
        course = courses->getCourse(pop[ind][0][4]);
        sem->SetRoot(course);
        par = sem->GetRoot();
        break;
      case 2: //split node as root
        sem->SetRoot(NULL);
        par = sem->GetRoot();
        populateSplit(pop[ind][0][4], par, sem);
        break;
      default: break;
    }
    i++;
  }
  for(; i < pop[ind].size(); i++){
    switch(pop[ind][i][3]){
      case 1: //normal node
        course = courses->getCourse(pop[ind][i][4]);
        par = sem->AddChild(par, course);
        break;
      case 2: //split node
        par = sem->CreateSplit(par);
        populateSplit(pop[ind][i][4], par, sem);
        break;
      default: break;
    }
  }
}//populateLine

void Database::populateSplit(int fid, Node *splitnode, Semester *sem){
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT splits.left, splits.right FROM splits WHERE splits.id=") <<
                   fid << wxString(";");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("preparing statement");
    sqlite3_finalize(stmt);
    return;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    int i, j, k,
        left = sqlite3_column_int(stmt, 0),
        right = sqlite3_column_int(stmt, 1);
    bool b = false;
    for(i = 0; i < pop.size(); i++){
      if (left == pop[i][0][1]){
        j = i;
        if(b)
          break;
        else
          b = true;
      }
      else if (right == pop[i][0][1]){
        k = i;
        if(b)
          break;
        else
          b = true;
      }
    }
    populateLine(k, splitnode, sem);
    populateLine(j, splitnode, sem);
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);

}//getPopulation

int Database::addCurriculum(wxString name, int semesters, int years){
  int ret;
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("INSERT INTO curriculum(name) VALUES ('") << name << wxString("');");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("Preparing statement");
    sqlite3_finalize(stmt);
    return -1;
  }
  rc = sqlite3_step(stmt);
  if(rc == SQLITE_ERROR)
    ret = -1;
  else
    ret = sqlite3_last_insert_rowid(this->db);
  sqlite3_finalize(stmt);
  for(int i = 1; i <= years; i++){
    if(addYear(ret, i) < 0)
      ret = -1;
  }
  return ret;
}

int Database::addYear(wxString curname, int year){
  int ret;
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT id FROM curriculum WHERE name='") << curname << wxString("';");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("Preparing statement");
    sqlite3_finalize(stmt);
    return -1;
  }
  rc = sqlite3_step(stmt);
  while (rc == SQLITE_ROW){
    ret = addYear(sqlite3_column_int(stmt, 0), year);
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);
  return ret;
}

int Database::addYear(int cid, int year){
  int ret;
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("INSERT INTO years(cid, ind, name) VALUES ('") << cid <<
                   wxString("' ,'") << year << wxString("' ,'Year ") << year << wxString("');");
  int rc = sqlite3_prepare_v2(this->db, query, -1, &stmt, &pzt);
  if (rc){
    error("Preparing statement");
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