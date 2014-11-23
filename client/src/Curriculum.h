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

struct OneCurriculum{
  wxString name;
  wxString affiliation;
  unsigned int semesters;
  unsigned int years;
};

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

  void setCurriculum(std::vector<Semester*> vec, wxString name);//Courses *courses);

	void addCurriculum(wxString name, wxString affiliation, unsigned int semesters, unsigned int years);

	int addNewCurriculum(std::vector<wxString> data);
	
  //Updates the curriculum after a drag and drop action
  void updateCurriculum();

  void dragDraw();

private:
  wxString curName;   //Name of the curriculum
  std::vector<Semester*> semesters; //Vector of all courses
  std::vector<wxBitmap> bmaps;
  std::vector<OneCurriculum> all_curricula; // Vector of all curricula
  DrawingHelper dh;
  DragDropHelp * dragdrop;
  
  //Prints this curriculum in the overview box
  void drawCurriculum();

  void OnDraw(wxDC& dc);

  unsigned int determineWidth();
  unsigned int determineHeight();

  //wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */
