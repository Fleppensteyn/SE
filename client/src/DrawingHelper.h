/*
  SE 2014
  Group 8
*/

#ifndef DRAWINGHELPER_H_
#define DRAWINGHELPER_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Courses.h"

struct Course;

enum {
  ALIGN_LEFT,
  ALIGN_RIGHT,
  ALIGN_CENTER
};

class DrawingHelper
{
public:
  DrawingHelper();
  static wxBitmap drawCourse(Course course);
private:
  static void drawTextAligned(wxDC& dc, wxString txt, int x, int y, int align);

};


#endif /* DRAWINGHELPER_H_ */