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
#include "DrawingHelper.h"

const int curriculum_width = 500; 

//Contains all gui elements and functionality of a single curriculum
class Curriculum : public wxScrolledCanvas
{
public:
  //Sets up the view of a single curriculum
  // curricula - The parent tab control
  Curriculum(wxPanel *overview);
  virtual ~Curriculum();
  
  //Prints this curriculum in the overview box
  void DrawCurriculum();
  
  //Updates the contents of a course in this curriculum. Used after editting a course in the course catalogue
  void UpdateCourse(Course toUpdate);

private:
  wxString curName;   //Name of the curriculum
  std::vector<Semester*> semesters; //Vector of all courses
  std::vector<wxBitmap> bmaps;
  DrawingHelper dh;

  //wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */
