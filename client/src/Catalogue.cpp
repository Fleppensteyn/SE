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

  std::vector<Course> carr = courses->getCourseVec();
  for (unsigned int i = 0; i < carr.size(); i++)
    if (carr[i].ID > 0)
      bmaps.push_back(DrawingHelper::drawCourse(carr[i]));
  SetVirtualSize(catalogue_width, bmaps.size() * 65 + 5);
  SetScrollbars(0, 65, 1, bmaps.size(), false);
  SetScrollRate(0, 30);
}

// void Catalogue::scrollEvent(wxScrollEvent& event){
//   // this->Refresh();
//   printf("Scrollan: %d\n", event.GetPosition());
// }

// void Catalogue::paintEvent(wxPaintEvent& event){
//   wxPaintDC dc(this);
//   OnDraw(dc);
// }

void Catalogue::OnDraw(wxDC& dc){
  // int wincap = (GetClientSize().GetHeight()/65) + 2,
  //          i = (GetViewStart().y/65),
  //       offs = GetViewStart().y+5;

  // printf("%d %d %d\n", i, wincap, offs);
  // for (int j = 0; j < wincap; j++ )
  //     if(i < bmaps.size())
  //       dc.DrawBitmap(bmaps[i++], 5, offs + 65 * j);
  for (int i = 0; i < bmaps.size(); i++ )
    dc.DrawBitmap(bmaps[i], 5, 5 + 65 * i);
}

Catalogue::~Catalogue(){
  bmaps.clear();
}
