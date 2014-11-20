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
#include "Curriculum.h"

enum{
  ID_CURRICULUM_NAME,
  ID_CURYEARS,
  ID_CURSEMESTERS,
	ID_CURAFFILIATION,
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

  //If enter is pressed in a textctrl switches focus to next element
  void OnTextEnter(wxCommandEvent& event);

  //Checks if the choises made lead to a valid new course, of not sets error messages
  void OnSubmitCurriculum(wxCommandEvent& event);

  //Creates an error message corresponding to the passed error
  void DisplayError(int error);

  //Delete all error messages
  void ClearErrors();
  
	std::vector<wxString> getData();
	
	private:
	wxTextCtrl *curriculum_name;  //Input box for the name of the new curriculum
	wxTextCtrl *years;  //Input box for the number of years in the curriculum
	wxTextCtrl *semesters;  //Input box for the number of semesters per years
	wxComboBox *affiliation;  //Drop-down list box for all possible affiliations
	std::vector<wxStaticText*> errors; //Error messages that apply at any given time
  wxStaticBox *box1;
  
  Curriculum *curriculum;
  
  wxDECLARE_EVENT_TABLE();
};
#endif /* CURRICULUMCREATOR_H_ */
