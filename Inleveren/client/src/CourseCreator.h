/*
  SE 2014
  Group 8
*/

#ifndef COURSECREATOR_H_
#define COURSECREATOR_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>
#include "Courses.h"
#include "DrawingHelper.h"

enum{
  ID_COURSE_NAME,
  ID_ECTS,
  ID_AFFILIATION,
  ID_COURSE_TYPE,
  ID_COURSE_NUMBER,
  ID_SUBMIT_COURSE
};

enum{
  ERROR_NO_NAME,
  ERROR_NO_ECTS,
  ERROR_NO_NUMBER,
  ERROR_COURSE_ALREADY_EXISTS
};

//Contains all gui elements and functionality of the dialog used to create new courses
class CourseCreator : public wxDialog
{
public:
  //Sets up the course creation dialog
  // frame - The parent frame
  CourseCreator(wxFrame *frame, Courses *courses);

  //Delete all error messages
  virtual ~CourseCreator();

  std::vector<wxString> getData();

  //Creates an error message corresponding to the passed error
  void DisplayError(int error);

private:
  wxTextCtrl *course_name;  //Input box for the name of the new course
  wxTextCtrl *ects;         //Input box for the amount of ECTS awarded for the new course
  wxComboBox *affiliation;  //Drop-down list box for all possible affiliations
  wxComboBox *course_type;  //Drop-down list box for all possible course types
  wxTextCtrl *course_number;//Input box for the course number (as in the sequence of the line)
  std::vector<wxStaticText*> errors; //Error messages that apply at any given time
  wxBitmap preview; //Stores the preview of the created course

  wxStaticBox *box1;
  wxStaticBox *box2;
  Courses *courses;

  //If enter is pressed in a textctrl switches focus to next element
  void OnTextEnter(wxCommandEvent& event);

  //Checks if the choises made lead to a valid new course, of not sets error messages
  void OnSubmitCourse(wxCommandEvent&);

  //Delete all error messages
  void ClearErrors();

  //Triggers the update of the preview
  void updatePreview(wxCommandEvent&);

  //Updates the preview of the course
  void drawPreview(wxPaintEvent&);

  //Determine through hardcoded association what the line for this course would be
  wxString determineLine();

  wxDECLARE_EVENT_TABLE();
};

#endif /* COURSECREATOR_H_ */