/*
  SE 2014
  Group 8
*/

#include "DragDropHelp.h"

DragDropHelp::DragDropHelp(){
  course = NULL;
}

DragDropHelp::~DragDropHelp(){
}

void DragDropHelp::updateVariables(wxPoint catalogpos, wxPoint curriculumpos,
                                   wxSize catalogsize, wxSize curriculumsize){
  printf("var update\n");
  currpos = curriculumpos;
  catpos = catalogpos;
  currsize = curriculumsize;
  catsize = catalogsize;
}

void DragDropHelp::updateDragging(const wxPoint pos, int source){
  printf("drag update %4d %4d %d %4d %4d\n", pos.x, pos.y, source, catpos.x, catpos.y);
  if (course == NULL) return;
  switch (source){
    case DRAGDROP_CATALOG:    drawpos = pos + catpos - dragpoint; break;
    case DRAGDROP_CURRICULUM: drawpos = pos + currpos - dragpoint; break;
    case DRAGDROP_OVERVIEW: drawpos = pos - dragpoint; break;
    default: break;
  }
}

bool DragDropHelp::needsDrawing(wxPoint& pos, int source){
  // printf("draw check %4d, %4d\n", drawpos.x, drawpos.y);
  if (course == NULL) return false;
  wxPoint tmp;
  bool xd, yd;
  switch (source){
    case DRAGDROP_CATALOG:
      tmp = drawpos - catpos;
      pos.x = tmp.x; pos.y = tmp.y;
      xd = (tmp.x + coursewidth >= 0 && tmp.x <= catsize.GetWidth());
      yd = (tmp.y + courseheight >= 0 && tmp.y <= catsize.GetHeight());
      return (xd && yd);
      break;
    case DRAGDROP_CURRICULUM:
      tmp = drawpos - currpos;
      pos.x = tmp.x; pos.y = tmp.y;
      xd = (tmp.x + coursewidth >= 0 && tmp.x <= currsize.GetWidth());
      yd = (tmp.y + courseheight >= 0 && tmp.y <= currsize.GetHeight());
      return (xd && yd);
      break;
    case DRAGDROP_OVERVIEW:
      xd = (drawpos.x > currpos.x && drawpos.x + coursewidth < currpos.x + currsize.GetWidth());
      if (xd)
        yd = (drawpos.y > currpos.y && drawpos.y + courseheight < currpos.y + currsize.GetHeight());
      else {
        xd = (drawpos.x > catpos.x && drawpos.x + coursewidth < catpos.x + catsize.GetWidth());
        if (xd)
          yd = (drawpos.y > catpos.y && drawpos.y + courseheight < catpos.y + catsize.GetHeight());
        else
          yd = false;
      }
      pos.x = drawpos.x;
      pos.y = drawpos.y;
      return !(xd && yd);
      break;
  }
  return false;
}

void DragDropHelp::startDrag(const wxPoint start, const wxPoint dragpoint, Course * course, int source){
  printf("drag start\n");
  this->dragpoint = dragpoint;
  this->course = course;
  updateDragging(start, source);
}

void DragDropHelp::stopDrag(){
  printf("drag stop\n");
  course = NULL;
  drawpos = wxPoint(-1, -1);
  dragpoint = wxPoint(coursewidth, courseheight);
}

Course * DragDropHelp::getCourse(){
  return course;
}