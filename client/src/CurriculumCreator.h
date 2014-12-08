/*
  SE 2014
  Group 8
*/

#ifndef CURRICULUMCREATOR_H_
#define CURRICULUMCREATOR_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>

enum{
  ID_CURRICULUM_NAME,
  ID_CURYEARS,
  ID_CURSEMESTERS,
  ID_SUBMIT_CURRICULUM
};

enum{
  ERROR_NO_CURNAME,
  ERROR_NO_CURYEARS,
  ERROR_NO_CURSEMESTERS,
  ERROR_CURRICULUM_ALREADY_EXISTS
};

class CurriculumCreator : public wxDialog
{
public:
  CurriculumCreator(wxFrame *frame);

  //Delete all error messages
  virtual ~CurriculumCreator();

  //Creates an error message corresponding to the passed error
  void DisplayError(int error);

  std::vector<wxString> getData();

private:
  wxTextCtrl *curriculum_name;  //Input box for the name of the new curriculum
  wxTextCtrl *years;  //Input box for the number of years in the curriculum
  wxTextCtrl *semesters;  //Input box for the number of semesters per years
  std::vector<wxStaticText*> errors; //Error messages that apply at any given time
  wxStaticBox *box1;

  //If enter is pressed in a textctrl switches focus to next element
  void OnTextEnter(wxCommandEvent& event);

  //Checks if the choices made lead to a valid new course, or sets error messages
  void OnSubmitCurriculum(wxCommandEvent&);

  //Delete all error messages
  void ClearErrors();

  wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUMCREATOR_H_ */
