/*
  SE 2014
  Group 8
*/

#ifndef COURSEEDITOR_H_
#define COURSEEDITOR_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>
#include "Courses.h"
#include "DrawingHelper.h"

//ID's
enum{
	ID_EDIT_COURSE_NAME,
  ID_EDIT_ECTS,
  ID_EDIT_AFFILIATION,
  ID_EDIT_COURSE_TYPE,
  ID_EDIT_COURSE_NUMBER,
  ID_EDIT_SUBMIT_COURSE,
  ID_DELETE_COURSE,
};

//Errors
enum{
	ERROR_EDIT_NO_NAME,
  ERROR_EDIT_NO_ECTS,
  ERROR_EDIT_NO_NUMBER,
  ERROR_EDIT_COURSE_ALREADY_EXISTS
};

//Contains all gui elements and functionality of the dialog used to create new courses
class CourseEditor : public wxDialog
{
public:
  //Sets up the course creation dialog
  // frame - The parent frame
  CourseEditor(Course *course, Courses *courses);

  //Delete all error messages
  virtual ~CourseEditor();

  //If delete button is pressed, this function will ask for confirmation and then delete the course
  void OnDeleteCourse(wxCommandEvent& event);

  bool isDelete();

  //If enter is pressed in a textctrl switches focus to next element
  void OnTextEnter(wxCommandEvent& event);

  //Checks if the choises made lead to a valid new course, of not sets error messages
  void OnSubmitCourse(wxCommandEvent& event);

  //Creates an error message corresponding to the passed error
  void DisplayError(int error);

  //Delete all error messages
  void ClearErrors();
  
  std::vector<wxString> getData();

	//Triggers the update of the preview
  void updatePreview(wxCommandEvent& event);

  //Updates the preview of the course
  void drawPreview(wxPaintEvent& event);

  //Determine through hardcoded association what the line for this course would be
  wxString determineLine();

  void setAffiliation(wxColour colour);

  void setType(wxColour colour);

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
  bool delete_course;

  Courses *courses;  

  wxDECLARE_EVENT_TABLE();
};

#endif /* COURSEEDITOR_H_ */
