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

#include "wx/bookctrl.h"

#include <vector>

//Contains all gui elements and functionality of a single curriculum
class Curriculum : public wxPanel
{
public:
  //Sets up the view of a single curriculum
  // curricula - The parent tab control
  Curriculum(wxBookCtrl *curricula);
  virtual ~Curriculum();
  
  //Adds a course to this curriculum
  void AddCourse(/*Course newCourse,*/ int semester, int position);
  
  //Deletes a course from this curriculum
	void DeleteCourse(int semester, int position);
  
  //Prints this curriculum in the overview box
  void ShowCurriculum();
  
  //Updates the contents of a course in this curriculum. Used after editting a course in the course catalogue
	void UpdateCourse(/*Course toUpdate*/);
	
private:
	wxString curName; 														//Name of the curriculum
	/*std::vector< std::vector<Course> > courses;*/ //Array with all the courses in this curriculum

  //wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */
