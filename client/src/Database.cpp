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
        if(sem->GetRoot() != NULL)
          ret.push_back(sem);
        else
          delete sem;
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
  // printf("getpop\n");
  pop.clear();
  int curind = -1, indind,
      curline = -1, lineind;
  int i1 = -1,i2 = -1;

  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("SELECT columns.ind, lines.id, lines.ind,lines.type,lines.fid") <<
                   wxString(" FROM columns LEFT JOIN lines ON columns.lid=lines.id WHERE") <<
                   wxString(" columns.yid = ") << fid << wxString(";");
  // printf("%s\n", (const char *) query.ToAscii());
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
    if (curind != indind || i2 == -1){
      std::vector<int> temp;
      pop[i1].push_back(temp);
      curind = indind;
      i2++;
    }
    // printf("ROWS AND STUFF %d %d %d %d %d %d\n", indind, lineind, curind, curline, i1, i2);
    for(int i = 0; i < 5; i++)
      pop[i1][i2].push_back(sqlite3_column_int(stmt, i));
    rc = sqlite3_step(stmt);
  }
  // printf("What the stuff\n");
  if (rc != SQLITE_DONE)
    error("evaluating statement");
  sqlite3_finalize(stmt);
  orderPopulation(pop);
}//getPopulation

void Database::orderPopulation(std::vector<std::vector<std::vector<int> > > pop){
  // printf("Ordering\n");
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
  // printf("Populating line\n");
  Course *course;
  Node *par = parent;
  int i = 0;
  while (par == NULL){
    if(i >= pop[ind].size())
      return;
    //create new semester
    switch(pop[ind][i][3]){
      case 1: //normal root
        course = courses->getCourse(pop[ind][i][4]);
        if(course != NULL){
          sem->SetRoot(course);
          par = sem->GetRoot();
        }
        break;
      case 2: //split node as root
        sem->SetRoot(NULL);
        par = sem->GetRoot();
        populateSplit(pop[ind][i][4], par, sem);
        break;
      default: break;
    }
    i++;
  }
  for(; i < pop[ind].size(); i++){
    switch(pop[ind][i][3]){
      case 1: //normal node
        course = courses->getCourse(pop[ind][i][4]);
        if(course != NULL)
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
    int i, j = -1, k = -1,
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
    if(k != -1)
      populateLine(k, splitnode, sem);
    if(j != -1)
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

int Database::deleteCourse(unsigned int ID){
  int ret;
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("DELETE FROM courses WHERE id=") << ID << wxString(";");
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
    ret = 1;
  sqlite3_finalize(stmt);
  return ret;
}

int Database::editCourse(unsigned int ID, wxString name, wxString line, wxString number,
                         int ects, unsigned int affiliation, unsigned int type){
  int ret;
  sqlite3_stmt *stmt;
  const char *pzt;
  wxString query = wxString("UPDATE courses SET name = '") << name <<
                   wxString("', line = '") << line <<
                   wxString("', number = '") << number <<
                   wxString("', ects = ") << ects <<
                   wxString(", affilid = ") << affiliation <<
                   wxString(", typeid = ") << type <<
                   wxString(" WHERE id = ") << ID << wxString(";");
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
    ret = 1;
  sqlite3_finalize(stmt);
  return ret;
  return  ret;
}

bool Database::deleteYear(wxString curname, wxString yearname){
  int yid, rc;

  wxString query;
  query.Printf("SELECT years.id FROM years, curriculum WHERE years.cid = curriculum.id"
               " AND years.name = '%s' AND curriculum.name = '%s';", yearname, curname);
  yid = selectSingleInt(query, rc, "selecting year to delete");
  if (rc != SQLITE_ROW)
    return false;
  else
    return deleteYear(yid);
}

bool Database::deleteYear(int yid){
  int rc;
  wxString query;

  query.Printf("SELECT ind, lid FROM columns WHERE yid = %d;", yid);
  std::vector<std::vector<int> > colres = selectIntVector(query, rc, "selecting columns to delete");
  if (rc != SQLITE_DONE)
    return false;

  wxString splitcols("("), colstr("(");

  for (int i = 0; i < colres.size(); i++){
    if (colres[i][0] == -1)
      splitcols << colres[i][1] << ",";
    colstr << colres[i][1] << ",";
  }
  splitcols.RemoveLast();
  colstr.RemoveLast();

  if (splitcols.Len() > 0){
    splitcols << ")";
    query.Printf("DELETE FROM splits WHERE left IN %s OR right IN %s;", splitcols, splitcols);
    if (simpleQuery(query, "deleting splits") == SQLITE_ERROR)
      return false;
  }

  if (colstr.Len() > 0){
    colstr << ")";
    query.Printf("DELETE FROM lines WHERE id IN %s;", colstr);
    if (simpleQuery(query, "deleting lines") == SQLITE_ERROR)
      return false;
  }

  query.Printf("DELETE FROM columns WHERE yid = %d;", yid);
  if (simpleQuery(query, "deleting columns") == SQLITE_ERROR)
    return false;

  query.Printf("DELETE FROM years WHERE id = %d;", yid);
  if (simpleQuery(query, "deleting year") == SQLITE_ERROR)
    return false;
  return true;
}

int Database::simpleQuery(wxString query, const char * errormsg){
  sqlite3_stmt *stmt;
  const char *pzt;
  printf("simpleQuery: %s\n", (const char *)query.ToAscii());
  int rc = sqlite3_prepare_v2(this->db, query.utf8_str(), -1, &stmt, &pzt);
  if (rc){
    error(errormsg);
    sqlite3_finalize(stmt);
    return SQLITE_ERROR;
  }
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE){
    error(errormsg);
    sqlite3_finalize(stmt);
    return SQLITE_ERROR;
  }
  sqlite3_finalize(stmt);
  return rc;
}

int Database::selectSingleInt(wxString query, int& rc, const char * errormsg){
  sqlite3_stmt *stmt;
  const char *pzt;
  int ret = -1;

  printf("selectSingleInt: %s\n", (const char *)query.ToAscii());
  rc = sqlite3_prepare_v2(this->db, query.utf8_str(), -1, &stmt, &pzt);
  if (rc){
    error(errormsg);
    sqlite3_finalize(stmt);
    return ret;
  }
  rc = sqlite3_step(stmt);
  if (rc == SQLITE_ROW)
    ret = sqlite3_column_int(stmt, 0);
  else
    error(errormsg);
  sqlite3_finalize(stmt);
  return ret;
}

std::vector<std::vector<int> > Database::selectIntVector(wxString query, int& rc, const char * errormsg){
  sqlite3_stmt *stmt;
  const char *pzt;
  std::vector<std::vector<int> > ret;

  printf("selectIntVector: %s\n", (const char *)query.ToAscii());

  rc = sqlite3_prepare_v2(this->db, query.utf8_str(), -1, &stmt, &pzt);
  if (rc){
    error(errormsg);
    sqlite3_finalize(stmt);
    return ret;
  }
  rc = sqlite3_step(stmt);
  int cols = sqlite3_data_count(stmt);
  while (rc == SQLITE_ROW){
    std::vector<int> temp;
    for (int i = 0; i < cols; i++)
      temp.push_back(sqlite3_column_int(stmt, i));
    ret.push_back(temp);
    rc = sqlite3_step(stmt);
  }
  if (rc != SQLITE_DONE)
    error(errormsg);
  sqlite3_finalize(stmt);
  return ret;
}

void Database::saveYear(wxString curname, wxString yearname, std::vector<Semester*>& tree){
  int yid, rc;

  wxString query;
  query.Printf("SELECT years.cid, years.id FROM years, curriculum WHERE years.cid = curriculum.id"
               " AND years.name = '%s' AND curriculum.name = '%s';", yearname, curname);
  std::vector<std::vector<int> > idsel = selectIntVector(query, rc, "checking if year exists");
  std::vector<int> ids;
  if (rc == SQLITE_DONE && idsel.size() > 0){
    // printf("Year exists cid: %d yid: %d\n", idsel[0][0], idsel[0][1]);
    ids = idsel[0];
    query.Printf("SELECT ind FROM years WHERE id = %d;",ids[1]);
    int oldind = selectSingleInt(query, rc, "figuring out the index of the current year");
    deleteYear(ids[1]);
    query.Printf("INSERT INTO years (id, cid, ind, name) VALUES (%d, %d, %d, '%s');", ids[1], ids[0], oldind, yearname);
    rc = simpleQuery(query, "re-inserting a deleted year into the database");
    if (rc != SQLITE_DONE) return;
  } else {
    // printf("Year not in db yet\n");
    int newind = 1;
    query.Printf("SELECT id FROM curriculum WHERE name = '%s';", curname);
    ids.push_back(selectSingleInt(query, rc, "getting the curriculum id"));
    if (rc != SQLITE_ROW){
      ids[0] = addCurriculum(curname, 0, 0);
      newind = 1;
    } else {
      query.Printf("SELECT max(ind) FROM years WHERE cid = %d;", ids[0]);
      newind = 1 + selectSingleInt(query, rc, "figuring out the highest year index");
      if (rc != SQLITE_ROW)
        newind = 1;
    }
    query.Printf("INSERT INTO years (cid, ind, name) VALUES (%d, %d, '%s');", ids[0], newind, yearname);
    rc = simpleQuery(query, "inserting a new year into the database");
    if (rc != SQLITE_DONE) return;
    ids.push_back(sqlite3_last_insert_rowid(this->db));
    // return;
  }
  InsertData idat;
  idat.yid = ids[1];
  idat.cid = ids[0];
  idat.columncount = tree.size();
  idat.splitcount = 0;
  for (int i = 0; i < idat.columncount; i++){
    int temp[] = {ids[1], i+1, i};
    std::vector<int> tmpvec(temp, temp + 3);
    idat.columns.push_back(tmpvec);
  }
  for (int i = 0; i < idat.columncount; i++)
    processLine(tree[i]->GetRoot(), idat, i);

  query.Printf("SELECT max(id) FROM lines;");
  idat.columnoffset = 1 + selectSingleInt(query, rc, "figuring out the highest line id");
  if (rc != SQLITE_ROW)
    idat.columnoffset = 1;

  if (idat.splitcount > 0){
    for (int i = 0; i < idat.splitcount; i++){
      query.Printf("INSERT INTO splits(left, right) VALUES (%d, %d);",
                    idat.splits[i][1] + idat.columnoffset, idat.splits[i][2] + idat.columnoffset);
      rc = simpleQuery(query, "inserting splits");
      if (rc != SQLITE_DONE) break;
      else if (i == 0) idat.splitsoffset = sqlite3_last_insert_rowid(this->db);
    }
  }
  for (int i = 0; i < idat.columns.size(); i++){
    query.Printf("INSERT INTO columns(yid, ind, lid) VALUES (%d, %d, %d);",
                  idat.yid, idat.columns[i][1], idat.columns[i][2] + idat.columnoffset);
    rc = simpleQuery(query, "inserting columns");
    if (rc != SQLITE_DONE) continue;
  }
  for (int i = 0; i < idat.lines.size(); i++){
    if (idat.lines[i][2] == 2) idat.lines[i][3] += idat.splitsoffset;
    query.Printf("INSERT INTO lines(id, ind, type, fid) VALUES (%d, %d, %d, %d);",
                  idat.lines[i][0] + idat.columnoffset, idat.lines[i][1], idat.lines[i][2], idat.lines[i][3]);
    rc = simpleQuery(query, "inserting lines");
    if (rc != SQLITE_DONE) continue;
  }
}

void Database::processLine(Node * root, InsertData& idat, int column){
  if (root == NULL) return;
  Node * cur = root;
  int type, id, ind = 1;
  std::vector<int> tmpvec;
  while (cur != NULL){
    // printf("col: %d, vec: %d\n", column, ind);
    switch (cur->GetNodeType()){
      case NODE_NORMAL: type = 1; id = cur->GetCourse()->ID; break;
      case NODE_SPLIT:  type = 2; id = idat.splitcount; break;
      case NODE_CHOICE: type = 3; id = -1; break;
    }
    int temp[] = {column, ind++, type, id};
    tmpvec = std::vector<int>(temp, temp+4);
    idat.lines.push_back(tmpvec);
    if (type == 2){
      // printf("Let's process splits\n");
      int lcolid = idat.columncount + idat.splitcount * 2;
      idat.splitcount++;
      for (int i = 0; i < 2; i++){
        int temp[] = {idat.yid, -1, lcolid + i};
        // printf("Splits pls\n");
        tmpvec = std::vector<int>(temp, temp + 3);
        idat.columns.push_back(tmpvec);
        processLine(cur->GetChild(i), idat, lcolid + i);
      }
      int temp[] = {id, lcolid, lcolid + 1};
      tmpvec = std::vector<int>(temp, temp + 3);
      idat.splits.push_back(tmpvec);
      cur = NULL;
    } else cur = cur->GetChild();
  }
}