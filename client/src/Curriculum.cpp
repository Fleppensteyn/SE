/*
  SE 2014
  Group 8
*/

#include "Curriculum.h"

Curriculum::Curriculum(wxPanel *overview, DragDropHelp * dragdrop)
      :wxScrolledCanvas(overview, wxID_ANY, wxPoint(100,100), wxSize(curriculum_width, 100))
{
  SetDoubleBuffered(true);
  this->dragdrop = dragdrop;
  wxFont font = GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  font.SetPointSize(30);
  SetFont(font);
}

Curriculum::~Curriculum(){
  semesters.clear();
}

void Curriculum::setCurriculum(std::vector<Semester*> vec, wxString name){//Courses *courses){
  //database to tree things first
  semesters.clear();
  semesters = vec;

  curName = name;

  drawCurriculum();
  Refresh();
}

void Curriculum::updateCurriculum(){
  /*  TODO:
      Handle a drag and drop action
  */
}

void Curriculum::drawCurriculum(){
  unsigned int curwidth = determineWidth(),
               curheight = determineHeight(),
               viswidth = GetSize().GetWidth(),
               visheight = GetSize().GetHeight(),
               startwidth,
               count = semesters.size();
  if(curwidth < viswidth){
    startwidth = (viswidth - curwidth) / 2;
    for(int i = 0; i < count; i++){
      semesters[i]->setPositions(startwidth);
      startwidth += semesters[i]->getWidth() + spacing;
    }
    if(curheight > visheight)
      SetScrollbars(0, 30, 1, curheight/30);
  }
  else{
    startwidth = 5;
    for(int i = 0; i < count; i++){
      semesters[i]->setPositions(startwidth);
      startwidth += semesters[i]->getWidth() + spacing;
    }
    if(curheight > visheight)
      SetScrollbars(30, 30, curwidth/30, curheight/30);
    else
      SetScrollbars(30, 0, curwidth/30, 1);
  }
}//drawCurriculum

void Curriculum::OnDraw(wxDC& dc){
  wxPoint vpoint = GetViewStart();
  wxSize rsize = GetSize();
  int width = dc.GetTextExtent(curName).GetWidth();
  dc.DrawText(curName, vpoint.x + ((rsize.GetWidth() - width) / 2), vpoint.y + 10);

  wxPoint dragpos;
  if (dragdrop->needsDrawing(dragpos, DRAGDROP_CURRICULUM)){
    for(int i = 0; i < semesters.size(); i++)
      semesters[i]->show(dc, dragpos);
    dc.DrawBitmap(dragdrop->getCourse()->bitmap, dragpos);
  }
  else{
    for(int i = 0; i < semesters.size(); i++)
      semesters[i]->show(dc);
  }
}//showCurriculum

void Curriculum::dragDraw(){
  wxPoint dragpos;
  if (dragdrop->needsDrawing(dragpos, DRAGDROP_CURRICULUM))
    Refresh();
}

unsigned int Curriculum::determineWidth(){
  unsigned int total_width = 0;
  for(int i = 0; i < semesters.size(); i++)
    total_width += semesters[i]->getWidth();
  total_width += semesters.size() * spacing;
  return total_width;
}//determineWidth

unsigned int Curriculum::determineHeight(){
  unsigned int total_height = 0;
  for(int i = 0; i < semesters.size(); i++){
    if(total_height < semesters[i]->getHeight())
      total_height = semesters[i]->getHeight();
  }
  return total_height + 100;
}//determineWidth
