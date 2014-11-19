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

class CurriculumCreator : public wxDialog
{
public:
	CurriculumCreator(wxFrame *frame);
	std::vector<wxString> getData();
private:
};
#endif /* CURRICULUMCREATOR_H_ */
