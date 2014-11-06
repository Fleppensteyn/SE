/*
  SE 2014
  Group 8
*/

#ifndef CURRICULUM_H_
#define CURRICULUM_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "wx/bookctrl.h"

//Contains all gui elements and functionality of a single curriculum
class Curriculum : public wxPanel
{
public:
  //Sets up the view of a single curriculum
  // curricula - The parent tab control
  Curriculum(wxBookCtrl *curricula);
  virtual ~Curriculum();

private:

  //wxDECLARE_EVENT_TABLE();
};

#endif /* CURRICULUM_H_ */