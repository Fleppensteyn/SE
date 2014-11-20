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
  ID_YEARS,
  ID_SEMESTERS,
	ID_AFFILIATION,
	ID_SUBMIT_CURRICULUM
};

class CurriculumCreator : public wxDialog
{
public:
	CurriculumCreator(wxFrame *frame);
	std::vector<wxString> getData();
private:
	wxTextCtrl *curriculum_name;  //Input box for the name of the new curriculum
	wxTextCtrl *years;  //Input box for the number of years in the curriculum
	wxTextCtrl *semesters;  //Input box for the number of semesters per years
	wxComboBox *affiliation;  //Drop-down list box for all possible affiliations
	
  
  wxStaticBox *box1;
  
  Curriculum *curriculum;
};
#endif /* CURRICULUMCREATOR_H_ */
