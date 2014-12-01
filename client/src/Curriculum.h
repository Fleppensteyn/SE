/*
  SE 2014
  Group 8
*/

#ifndef CURRICULUM_H_
#define CURRICULUM_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>
#include "Courses.h"
#include "Semester.h"
#include "Node.h"
#include "DrawingHelper.h"
#include "DragDropHelp.h"
#include "MouseManager.h"

wxDECLARE_EVENT(EVT_SELECTED, wxCommandEvent);
wxDECLARE_EVENT(EVT_NO_SELECT, wxCommandEvent);
wxDECLARE_EVENT(EVT_SAVE_DB, wxCommandEvent);

const int curriculum_width = 500;
const unsigned int spacing = 50;

//Contains all gui elements and functionality of a single curriculum
class Curriculum : public wxScrolledCanvas
{
public:
  //Sets up the view of a single curriculum
  // curricula - The parent tab control
  Curriculum(wxPanel *overview, DragDropHelp * dragdrop);

  virtual ~Curriculum();

  void setCurriculum(std::vector<Semester*> vec, wxString name);
  void drawCurriculum();

  void dragDraw();

  int hitTest(const wxPoint& pos);
  void select(int index);
  void startDrag(int item, const wxPoint& pos);
  void endDrag(int item);

  void insertSplit();
  void clear();

  std::vector<Semester*> getCurriculum();

private:
  wxString curName;   //Name of the curriculum
  std::vector<Semester*> semesters; //Vector of all courses
  std::vector<Node*> nodes;
  int selected;
  DrawingHelper dh;
  DragDropHelp * dragdrop;
  CurriculumMouseManager *mm;
  wxPanel * overview;
  bool dragging;

  void drawCurriculum(bool scroll);
  void OnDraw(wxDC& dc);
  void collectAllNodes();
  void resetNode();
  void removeEmptySplits();

  unsigned int determineWidth();
  unsigned int determineHeight();

  virtual bool SendAutoScrollEvents(wxScrollWinEvent&) const;

  // wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */
