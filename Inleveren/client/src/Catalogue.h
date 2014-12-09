/*
  SE 2014
  Group 8
*/

#ifndef CATALOGUE_H_
#define CATALOGUE_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Courses.h"
#include "MouseManager.h"
#include "DragDropHelp.h"
#include "CourseEditor.h"

wxDECLARE_EVENT(EVT_DELETED_COURSE, wxCommandEvent);

const int catalogue_width = 265; //Width of the catalogue panel

//Contains all gui elements and functionality of the course catalogue
class Catalogue : public wxScrolledCanvas
{
public:
  //Set up the catalogue panel
  Catalogue(wxPanel *panel, Courses *courses, DragDropHelp * dragdrop);
  virtual ~Catalogue();
  int hitTest(const wxPoint& pos);
  void select(int index);
  void setDoubleClick();
  void startDrag(int item, const wxPoint& pos);
  void refreshList();

private:
  int selected;
  bool doubleclick;
  int yscroll;
  wxPanel *overview;
  Courses *courses;
  DragDropHelp * dragdrop;
  CatalogueMouseManager * mousemanager;
  std::vector<Course *> bmaps;

  void OnDraw(wxDC& dc);
  void filter();
  void updateSizes();
  void editCourse(wxCommandEvent&);



  wxDECLARE_EVENT_TABLE();
};

#endif /* CATALOGUE_H_ */
