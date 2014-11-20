/*
  SE 2014
  Group 8
*/

#include "Curriculum.h"

Curriculum::Curriculum(wxPanel *overview)
      :wxScrolledCanvas(overview, wxID_ANY, wxPoint(100,100), wxSize(curriculum_width, 100))
{
  wxFont font = GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  font.SetPointSize(30);
  SetFont(font);
}

Curriculum::~Curriculum(){
  semesters.clear();
}

void Curriculum::setCurriculum(Courses *courses){
  //database to tree things first

  //but for now let's fake it!!!!!!!!!!
  curName = wxString("Test Year 1");
  for(int i = 0; i < 2; i++){
    Course *course = courses->getCourse(1);
    Semester *sem = new Semester(course);
    Node *par = sem->GetRoot();
    for(int j = 0; j < 3; j++)
      par = sem->AddChild(par,course);
    if(i  == 0){
      Node *split = sem->CreateSplit(par);
      par = sem->AddChild(split, course,0);
      par = sem->AddChild(par, course);
      Node *par2 = sem->AddChild(split, course, 1);
      par2 = sem->AddChild(par2, course);
      par2 = sem->AddChild(par2, course);
      split = sem->CreateSplit(par);
      par = sem->AddChild(split, course, 0);
      par2 = sem->AddChild(split, course, 1);
    }
    else{
      for(int j = 0; j < 3; j++)
        par = sem->AddChild(par,course);
    }
    semesters.push_back(sem);
  }
  //till here it was faked

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
  for(int i = 0; i < semesters.size(); i++)
    semesters[i]->show(dc);
}//showCurriculum

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