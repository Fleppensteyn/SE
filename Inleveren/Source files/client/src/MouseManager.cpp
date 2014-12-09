/*
  SE 2014
  Group 8
*/

#include "MouseManager.h"

MouseManager::MouseManager(wxWindow *window, DragDropHelp * dragdrop)
      :wxMouseEventsManagerMod(window)
{
  this->dragdrop = dragdrop;
}

MouseManager::~MouseManager(){

}


int MouseManager::MouseHitTest(const wxPoint&){
  //printf("Hit: %4d,%4d \n",pos.x, pos.y);
  return 1;
}

bool MouseManager::MouseClicked(int){
  //printf("Clicked: %2d\n",item);
  return true;
}

bool MouseManager::MouseDragBegin(int, const wxPoint&){
  //printf("Start: %2d, %4d, %4d\n", item, pos.x, pos.y);
  return true;
}

void MouseManager::MouseDragging(int, const wxPoint&){
  //printf("Dragging: %2d, %4d, %4d\n", item, pos.x, pos.y);
}
void MouseManager::MouseDragEnd(int, const wxPoint&){
  //printf("End: %2d, %4d, %4d\n", item, pos.x, pos.y);
  dragdrop->stopDrag(DRAGDROP_OVERVIEW);
}
void MouseManager::MouseDragCancelled(int){
  //printf("DragCancel: %2d\n",item);
}

void MouseManager::MouseClickCancelled(int){
  //printf("ClickCancel: %2d\n",item);
}

CatalogueMouseManager::CatalogueMouseManager(Catalogue * catalogue, DragDropHelp * dragdrop)
      :MouseManager(catalogue, dragdrop)
{
  this->catalogue = catalogue;
  previouslyClickedItem = -1;
}

int CatalogueMouseManager::MouseHitTest(const wxPoint& pos){
  return catalogue->hitTest(pos);
}

bool CatalogueMouseManager::MouseClicked(int item){
  if(item==previouslyClickedItem){
    previouslyClickedItem = -1;
    catalogue->setDoubleClick();
  }
  else{
    previouslyClickedItem = item;
    //printf("Clicked: %2d\n",item);
    catalogue->select(item);
  }
  return true;
}

void CatalogueMouseManager::MouseDragging(int, const wxPoint& pos){
  dragdrop->updateDragging(pos, DRAGDROP_CATALOG);
  catalogue->Refresh();
  //printf("Dragging: %2d, %4d, %4d\n", item, pos.x, pos.y);
}

bool CatalogueMouseManager::MouseDragBegin(int item, const wxPoint& pos){
  if (MouseHitTest(pos) != item) return false;
  catalogue->startDrag(item, pos);
  return true;
}

void CatalogueMouseManager::MouseDragEnd(int, const wxPoint&){
  //printf("End: %2d, %4d, %4d\n", item, pos.x, pos.y);
  //catalogue->endDrag();
  dragdrop->stopDrag(DRAGDROP_CATALOG);
}

CatalogueMouseManager::~CatalogueMouseManager(){

}

CurriculumMouseManager::CurriculumMouseManager(Curriculum * curriculum,
                                               DragDropHelp * dragdrop)
      :MouseManager(curriculum, dragdrop)
{
  this->curriculum = curriculum;
}

int CurriculumMouseManager::MouseHitTest(const wxPoint& pos){
  return curriculum->hitTest(pos);
}

bool CurriculumMouseManager::MouseClicked(int item){
  //printf("Clicked: %2d\n",item);
  curriculum->select(item);
  return true;
}
void CurriculumMouseManager::MouseDragging(int, const wxPoint& pos){
  dragdrop->updateDragging(pos, DRAGDROP_CURRICULUM);
  curriculum->Refresh();
  //printf("Dragging: %2d, %4d, %4d\n", item, pos.x, pos.y);
}

bool CurriculumMouseManager::MouseDragBegin(int item, const wxPoint& pos){
  if (MouseHitTest(pos) != item) return false;
  curriculum->startDrag(item, pos);
  return true;
}

void CurriculumMouseManager::MouseDragEnd(int item, const wxPoint&){
  //printf("End: %2d, %4d, %4d\n", item, pos.x, pos.y);
  curriculum->endDrag(item);
  dragdrop->stopDrag(DRAGDROP_CURRICULUM);
}

CurriculumMouseManager::~CurriculumMouseManager(){

}
