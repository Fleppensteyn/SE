/*
  SE 2014
  Group 8
*/

#include "Catalogue.h"

wxBEGIN_EVENT_TABLE(Catalogue, wxPanel)
  EVT_PAINT (Catalogue::paintEvent)
wxEND_EVENT_TABLE();

Catalogue::Catalogue(wxPanel *panel, Courses *courses)
      :wxPanel(panel, wxID_ANY, wxPoint(100,100), wxSize(catalogue_width, 100))
{
  this->overview =  panel;
  this->courses = courses;
}

void Catalogue::paintEvent(wxPaintEvent& event){
  wxPaintDC dc(this);
  this->render(dc);
}

void Catalogue::render(wxDC& dc){
  int empty = 0;
  for (int i = 0; i < 16; i++ ){
    Course test = courses->getCourse(i);
    if (test.ID <= 0) empty++;
    else {
      wxBitmap bmp = DrawingHelper::drawCourse(test);
      dc.DrawBitmap(bmp, 5, 5 + 65 * (i-empty));
    }
  }
}

Catalogue::~Catalogue(){

}
