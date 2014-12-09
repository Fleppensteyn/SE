/*
  SE 2014
  Group 8
*/

#ifndef OVERVIEW_H_
#define OVERVIEW_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Curriculum.h"
#include "Catalogue.h"
#include "Courses.h"
#include "MouseManager.h"
#include "DragDropHelp.h"
#include <vector>
#include "Database.h"
#include "YearCreator.h"
#include "CurriculumDeleter.h"
#include "YearDeleter.h"

enum{
  ID_CURRICULA,
  ID_FACULTY,
  ID_YEARS,
  ID_SHOW,
  ID_SPLIT
};

//Contains all gui elements and functionality of the Curriculum and Catalogue overview
class Overview : public wxPanel
{
public:
  //Sets up the Overview screen
  // frame - The parent frame
  // x - The x position of the top left corner of the panel
  // y - The y position of the top left corner of the panel
  // w - The width of the panel
  // h - The height of the panel
  Overview(wxFrame *frame, int x, int y, int w, int h);

  //Delete all Curricula
  virtual ~Overview();

  int addNewCourse(std::vector<wxString> data);

  int addNewCurriculum(std::vector<wxString> data);

  int addNewYear(wxFrame *frame);

  Courses* getCourses();

  void OnDeleteYear(wxFrame *frame);

  void OnDeleteCurriculum(wxFrame *frame);

  void OnDeleteAll();

  const char* getDatabaseFile();

private:
  Curriculum *curriculum; //The open curriculum
  Catalogue *catalogue; //The course catalogue
  Courses *courses;
  MouseManager *mousemanager;
  Database *database;
  DragDropHelp * dragdrop;

  wxComboBox *faculties;
  wxComboBox *years;
  wxButton *split;

  wxString curfac, curyr;

  void OnUpdateFaculty(wxCommandEvent&);

  void OnUpdateYear(wxCommandEvent&);

  void OnDeletedCourse(wxCommandEvent&);

  void OnSplit(wxCommandEvent&);

  void OnSelected(wxCommandEvent&);

  void OnNoSelect(wxCommandEvent&);

  void OnSaveDB(wxCommandEvent&);

  void drawStuff(wxPaintEvent&);

  void OnResize(wxSizeEvent&);

  void clearFaculties();

  void clearYears();

  wxDECLARE_EVENT_TABLE();
};

#endif /* OVERVIEW_H_ */
