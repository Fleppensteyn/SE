/*
  SE 2014
  Group 8
*/

#ifndef CURRICULUMDELETER_H_
#define CURRICULUMDELETER_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>
#include "Database.h"

enum{
  ID_DELETE_STUDY_PROGRAM
};

//Contains all gui elements and functionality of the dialog used to create new courses
class CurriculumDeleter : public wxDialog
{
public:
  //Sets up the course creation dialog
  // frame - The parent frame
  CurriculumDeleter(wxFrame *frame, Database *database);

  //Delete all error messages
  virtual ~CurriculumDeleter();

  std::vector<wxString> getData();

private:
  wxComboBox *study_program;  //Drop-down list box for all possible course types

  void OnDeleteCurriculum(wxCommandEvent&);

  wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUMDELETER_H_ */