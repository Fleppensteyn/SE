/*
  SE 2014
  Group 8
*/

#ifndef DRAGDROPHELP_H_
#define DRAGDROPHELP_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Courses.h"

class Curriculum;

enum
{
  DRAGDROP_CATALOG,
  DRAGDROP_CURRICULUM,
  DRAGDROP_OVERVIEW
};

class DragDropHelp
{
public:
  DragDropHelp();
  virtual ~DragDropHelp();

  void updateVariables(wxPoint catalogpos, wxPoint curriculumpos, wxSize catalogsize, wxSize curriculumsize);

  void updateDragging(const wxPoint pos, int source);
  bool needsDrawing(wxPoint& pos, int place);

  void startDrag(const wxPoint start, const wxPoint dragpoint, Course * course, int source);
  void stopDrag(int source);
  Course * getCourse();

  void setCurriculum(Curriculum * cur);


private:
  Course * course;
  wxPoint currpos, catpos, dragpoint, drawpos;
  wxSize  currsize, catsize;
  Curriculum * curriculum;
};

#endif /* DRAGDROPHELP_H_ */