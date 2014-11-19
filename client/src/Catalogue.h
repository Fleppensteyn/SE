/*
  SE 2014
  Group 8
*/

#ifndef CATALOGUE_H_
#define CATALOGUE_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Courses.h"

const int catalogue_width = 265; //Width of the catalogue panel

//Contains all gui elements and functionality of the course catalogue
class Catalogue : public wxScrolledCanvas
{
public:
  //Set up the catalogue panel
  Catalogue(wxPanel *panel, Courses *courses);
  virtual ~Catalogue();

private:
  // void paintEvent(wxPaintEvent& event);
  void OnDraw(wxDC& dc);
  // void scrollEvent(wxScrollEvent& event);
  void filter(SearchPars pars);
  void updateSizes();

  int yscroll;
  wxPanel *overview;
  Courses *courses;
  std::vector<Course *> bmaps;

  // wxDECLARE_EVENT_TABLE();
};

#endif /* CATALOGUE_H_ */