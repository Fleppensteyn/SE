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
  this->mm = new CurriculumMouseManager(this, dragdrop);
  wxFont font = GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  font.SetPointSize(30);
  SetFont(font);
  selected = -1;
}

Curriculum::~Curriculum(){
  semesters.clear();
  nodes.clear();
  delete mm;
}

void Curriculum::setCurriculum(std::vector<Semester*> vec, wxString name){//Courses *courses){
  //database to tree things first
  semesters.clear();
  semesters = vec;

  curName = name;

  drawCurriculum();
  collectAllNodes();
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
    dragpos = CalcUnscrolledPosition(dragpos);
    dc.DrawBitmap(dragdrop->getCourse()->bitmap, dragpos);
  }
  else{
    for(int i = 0; i < semesters.size(); i++)
      semesters[i]->show(dc);
    if(selected != -1){
      dc.SetBrush(wxBrush(wxColour("#008888"), wxBRUSHSTYLE_TRANSPARENT));
      dc.SetPen(wxPen(wxColour("#000000"), 2));
      Node *node = nodes[selected];
      const wxPoint p(node->GetX(), node->GetY());
      //wxPoint pos = CalcUnscrolledPosition(p);
      dc.DrawRectangle(p.x - 1, p.y - 1, 242, 62);
    }
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

void Curriculum::collectAllNodes(){
  nodes.clear();
  for(int i = 0; i < semesters.size(); i++){
    semesters[i]->getNodes(nodes, semesters[i]->GetRoot());
  }
}

int Curriculum::hitTest(const wxPoint& pos){
  int x, y;
  wxPoint unscpos = CalcUnscrolledPosition(pos);
  for(int i = 0; i < nodes.size(); i++){
    x = nodes[i]->GetX();
    y = nodes[i]->GetY();
    if(x < unscpos.x && unscpos.x < x + 240){
      if(y < unscpos.y && unscpos.y < y + 60 && nodes[i]->GetNodeType() == NODE_NORMAL)
        return i;
    }
  }
  return wxNOT_FOUND;
}

void Curriculum::select(int index){
  selected = index;
  Refresh();
}

void Curriculum::startDrag(int item, const wxPoint& pos){
  wxPoint unscpos = CalcUnscrolledPosition(pos);
  wxPoint dragpoint(unscpos.x - nodes[item]->GetX(), unscpos.y - nodes[item]->GetY());
  this->dragdrop->startDrag(pos, dragpoint, nodes[item]->GetCourse(), DRAGDROP_CURRICULUM);
}