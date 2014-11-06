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

const int catalogue_width = 300; //Width of the catalogue panel

//Contains all gui elements and functionality of the course catalogue
class Catalogue : public wxPanel
{
public:
  //Set up the catalogue panel
  Catalogue(wxPanel *panel);
  virtual ~Catalogue();

private:

  //wxDECLARE_EVENT_TABLE();
};

#endif /* CATALOGUE_H_ */