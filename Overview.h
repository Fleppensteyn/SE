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

class Overview : public wxPanel
{
public:
  Overview(wxFrame *frame, int x, int y, int w, int h);
  //~virtual Overview 

};

#endif /* OVERVIEW_H_ */