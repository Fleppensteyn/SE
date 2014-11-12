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

enum{
  ID_COURSE_NAME,
  ID_ECTS,
  ID_AFFILIATION,
  ID_COURSE_TYPE,
  ID_LINE_CHOICE,
  ID_LINE_OPTION,
  ID_LINE_CREATE,
  ID_COURSE_NUMBER,
  ID_SUBMIT_COURSE
};

enum{
  ERROR_NO_NAME,
  ERROR_NO_ECTS,
  ERROR_NO_LINE,
  ERROR_NO_NUMBER,
  ERROR_COURSE_ALREADY_EXISTS
};

//Contains all gui elements and functionality of the dialog used to create new courses
class CourseCreator : public wxDialog
{
public:
  //Sets up the course creation dialog
  // frame - The parent frame
  CourseCreator(wxFrame *frame);

  //Delete all error messages
  virtual ~CourseCreator();

  //If enter is pressed in a textctrl switches focus to next element
  void OnTextEnter(wxCommandEvent& event);

  //Checks if the choises made lead to a valid new course, of not sets error messages
  void OnSubmitCourse(wxCommandEvent& event);

  //Changes the enabled status of the line choice list box and the line create text ctrl
  void OnLineOption(wxCommandEvent& event);

  //Creates an error message corresponding to the passed error
  void DisplayError(int error);

  //Delete all error messages
  void ClearErrors();

  std::vector<wxString> getData();

private:
  wxTextCtrl *course_name;  //Input box for the name of the new course
  wxTextCtrl *ects;         //Input box for the amount of ECTS awarded for the new course
  wxComboBox *affiliation;  //Drop-down list box for all possible affiliations
  wxComboBox *course_type;  //Drop-down list box for all possible course types
  wxComboBox *line_choice;  //Drop-down list box for all existing lines
  wxCheckBox *line_option;  //Checkbox to indicate the use of an existing line or a new line
  wxTextCtrl *line_create;  //Input box used in case of a new line
  wxTextCtrl *course_number;//Input box for the course number (as in the sequence of the line)
  std::vector<wxStaticText*> errors; //Error messages that apply at any given time

  wxStaticBox *box1;
  wxStaticBox *box2;

  wxDECLARE_EVENT_TABLE();
};

#endif /* COURSECREATOR_H_ */