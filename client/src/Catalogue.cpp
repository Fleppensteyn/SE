/*
  SE 2014
  Group 8
*/

#include "Catalogue.h"

// wx BEGIN_EVENT_TABLE(Catalogue, wxPanel)
//   EVT _PAINT (Catalogue::paintEvent)
//   EVT _SCROLL (Catalogue::scrollEvent)
// wxEND _EVENT_TABLE();

Catalogue::Catalogue(wxPanel *panel, Courses *courses)
      :wxScrolledCanvas(panel, wxID_ANY, wxPoint(100,100), wxSize(catalogue_width, 100))
{
  this->overview =  panel;
  this->courses = courses;
  yscroll = 20;

  SearchPars sp;
  filter(sp);
}

void Catalogue::filter(SearchPars pars){
  bmaps = courses->filter(pars);
  updateSizes();
}

void Catalogue::updateSizes(){
  SetVirtualSize(catalogue_width, (bmaps.size() * 65) + 5);
  SetScrollbars(0, 65, 1, bmaps.size(), false);
  SetScrollRate(0, yscroll);
  Refresh();
}

void Catalogue::OnDraw(wxDC& dc){
  unsigned int wincap = (GetClientSize().GetHeight()/65) + 2,
               curind = ((GetViewStart().y*yscroll)/65);

  for (unsigned i = curind; i < curind+wincap && i < bmaps.size(); i++ )
    dc.DrawBitmap(bmaps[i]->bitmap, 2, 5 + 65 * i);
}

Catalogue::~Catalogue(){
  bmaps.clear();
}
