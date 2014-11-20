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

const int curriculum_width = 500; 
const unsigned int spacing = 50;

//Contains all gui elements and functionality of a single curriculum
class Curriculum : public wxScrolledCanvas
{
public:
  //Sets up the view of a single curriculum
  // curricula - The parent tab control
  Curriculum(wxPanel *overview);
  virtual ~Curriculum();

  void setCurriculum(Courses *courses);

  //Updates the curriculum after a drag and drop action
  void updateCurriculum();

private:
  wxString curName;   //Name of the curriculum
  std::vector<Semester*> semesters; //Vector of all courses
  std::vector<wxBitmap> bmaps;
  DrawingHelper dh;

  //Prints this curriculum in the overview box
  void drawCurriculum();

  void OnDraw(wxDC& dc);

  unsigned int determineWidth();
  unsigned int determineHeight();

  //wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */
