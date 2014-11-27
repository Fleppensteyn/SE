/*
  SE 2014
  Group 8
*/

#ifndef YEARDELETER_H_
#define YEARDELETER_H_

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include <vector>
#include "Database.h"

enum{
  ID_DELETER_STUDY_PROGRAM,
  ID_DELETER_DELETE_YEAR
};

//Contains all gui elements and functionality of the dialog used to create new courses
class YearDeleter : public wxDialog
{
public:
  //Sets up the course creation dialog
  // frame - The parent frame
  YearDeleter(wxFrame *frame, Database *database);

  //Delete all error messages
  virtual ~YearDeleter();

  void OnDeleteYear(wxCommandEvent& event);

  void OnUpdateCurriculum(wxCommandEvent& event);

  std::vector<wxString> getData();

private:
  wxComboBox *study_program;  //Drop-down list box for all possible study programs
  wxComboBox *year;
  wxButton *create;

  Database *database;

  wxDECLARE_EVENT_TABLE();
};

#endif /* YEARDELETER_H_ */