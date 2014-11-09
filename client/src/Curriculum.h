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
#include <string>

//There can be no more than 50 courses in a curriculum
const int MAXCOURSES = 50;

//Contains all gui elements and functionality of a single curriculum
class Curriculum : public wxPanel
{
public:
  //Sets up the view of a single curriculum
  // curricula - The parent tab control
  Curriculum(wxBookCtrl *curricula);
  virtual ~Curriculum();
  
  //Adds a course to this curriculum
  void AddCourse(/*Course newCourse*/);
  
  //Deletes a course from this curriculum
	void DeleteCourse(/*Course toDelete*/);
  
  //Prints this curriculum in the overview box
  void ShowCurriculum();
  
  //Updates the contents of a course in this curriculum. Used after editting a course in the course catalogue
	void UpdateCourse(/*Course toUpdate*/);
	
private:
	std::string curName; 						//Name of the curriculum
	/*Course courses[MAXCOURSES];*/ //Array with all the courses in this curriculum
	int numberOfCourses; 						//The number of courses in this curriculum
  //wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */
