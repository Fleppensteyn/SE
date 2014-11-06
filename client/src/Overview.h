/*
  SE 2014
  Group 8
*/

#ifndef OVERVIEW_H_
#define OVERVIEW_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Curriculum.h"
#include "Catalogue.h"
#include <vector>

enum{
  ID_CURRICULA
};

//Contains all gui elements and functionality of the Curriculum and Catalogue overview
class Overview : public wxPanel
{
public:
  //Sets up the Overview screen
  // frame - The parent frame
  // x - The x position of the top left corner of the panel
  // y - The y position of the top left corner of the panel
  // w - The width of the panel
  // h - The height of the panel
  Overview(wxFrame *frame, int x, int y, int w, int h);

  //Delete all Curricula
  virtual ~Overview();

  //Close the tab that is currently opened
  void OnCloseTab();

  wxBookCtrl *curricula; //Controls the the tab structure of the curricula
private:
  std::vector<Curriculum*> tabs; //A vector containing pointer to all open curricula
  Catalogue *catalogue; //The course catalogue

  //wxDECLARE_EVENT_TABLE();
};

#endif /* OVERVIEW_H_ */