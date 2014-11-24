/*
  SE 2014
  Group 8
*/

#ifndef YEARCREATOR_H_
#define YEARCREATOR_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>
#include "Database.h"

enum{
  ID_STUDY_PROGRAM,
  ID_YEAR_NAME,
  ID_SUBMIT_YEAR
};

enum{
  ERROR_NO_YEAR,
  ERROR_YEAR_ALREADY_EXISTS
};

//Contains all gui elements and functionality of the dialog used to create new courses
class YearCreator : public wxDialog
{
public:
  //Sets up the course creation dialog
  // frame - The parent frame
  YearCreator(wxFrame *frame, Database *database);

  //Delete all error messages
  virtual ~YearCreator();

  //If enter is pressed in a textctrl switches focus to next element
  void OnTextEnter(wxCommandEvent& event);

  //Checks if the choises made lead to a valid new course, of not sets error messages
  void OnSubmitYear(wxCommandEvent& event);

  //Creates an error message corresponding to the passed error
  void DisplayError(int error);

  //Delete all error messages
  void ClearErrors();

  std::vector<wxString> getData();

private:
  wxComboBox *study_program;  //Drop-down list box for all possible course types
  wxTextCtrl *year_name;//Input box for the course number (as in the sequence of the line)
  std::vector<wxStaticText*> errors; //Error messages that apply at any given time

  wxStaticBox *box1;

  wxDECLARE_EVENT_TABLE();
};

#endif /* YEARCREATOR_H_ */