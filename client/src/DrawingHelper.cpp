/*
  SE 2014
  Group 8
*/

#include "DrawingHelper.h"

DrawingHelper::DrawingHelper(){

}

wxBitmap DrawingHelper::drawCourse(Course course){
  int width = coursewidth, height = courseheight;
  wxBitmap ret(width,height);
  wxMemoryDC dc(ret);
  dc.SetTextForeground(wxColour("#366092"));

  dc.SetPen(wxPen(course.type.ChangeLightness(50), 1, wxPENSTYLE_SOLID));
  dc.SetBrush(wxBrush(course.type));
  dc.DrawRectangle(0,0,width,height);

  dc.SetPen(wxPen(wxColour("#366092"), 1.5, wxPENSTYLE_SOLID));
  dc.SetBrush(wxBrush(course.affiliation));
  dc.DrawRoundedRectangle(10, 30, 40, 25, 6);

  dc.SetPen(wxPen(wxColour("#000000"), 0, wxPENSTYLE_TRANSPARENT));
  dc.SetBrush(wxBrush(wxColour("#366092")));
  dc.DrawRectangle(60, 5, 2,height-10);


  wxFont font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
  font.SetPointSize(11);
  dc.SetFont(font);

  drawTextAligned(dc, "-", 30, 5, ALIGN_CENTER);
  drawTextAligned(dc, course.line, 25, 5, ALIGN_RIGHT);
  drawTextAligned(dc, course.number, 35, 5, ALIGN_LEFT);

  wxString tmp;
  tmp << course.ects;
  drawTextAligned(dc, tmp, 30, 33, ALIGN_CENTER);
  tmp.Clear();

  wxArrayInt widths;
  wxArrayInt spaces;
  int i = course.name.find(' ');
  while (i != -1){
    spaces.Add(i);
    i = course.name.find(' ', i + 1);
  }
  if(spaces.GetCount() > 0) spaces.Add(course.name.Len()-1);

  int maxwidth = width - 60 - 10;

  wxString drawname(course.name);
  dc.GetPartialTextExtents(drawname, widths);

  for(size_t i = 0; i < spaces.GetCount(); i++){
    if (widths[spaces[i]] > maxwidth && drawname[spaces[i]]!='\n'){
      if (i > 0){
        i--;
        drawname[spaces[i]] = '\n';
        maxwidth += widths[spaces[i]];
      }
    }
  }
  dc.DrawLabel(drawname, wxRect(65, 2, width - 60 - 10, height - 4), wxALIGN_CENTER);
  return ret;
}

void DrawingHelper::drawTextAligned(wxDC& dc, wxString txt, int x, int y, int align){
  int w = dc.GetTextExtent(txt).GetWidth();
  switch (align){
    case ALIGN_LEFT:  dc.DrawText(txt, x, y);      break;
    case ALIGN_RIGHT: dc.DrawText(txt, x-w, y);    break;
    case ALIGN_CENTER:dc.DrawText(txt, x-(w/2), y);break;
  }
}