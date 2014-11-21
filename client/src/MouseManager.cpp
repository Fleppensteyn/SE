/*
  SE 2014
  Group 8
*/

#include "MouseManager.h"

MouseManager::MouseManager(wxWindow *window, DragDropHelp * dragdrop)
      :wxMouseEventsManager(window)
{
  this->dragdrop = dragdrop;
}

MouseManager::~MouseManager(){

}


int MouseManager::MouseHitTest(const wxPoint& pos){
  printf("Hit: %4d,%4d \n",pos.x, pos.y);
  return 1;
}

bool MouseManager::MouseClicked(int item){
  printf("Clicked: %2d\n",item);
  return true;
}

bool MouseManager::MouseDragBegin(int item, const wxPoint& pos){
  printf("Start: %2d, %4d, %4d\n", item, pos.x, pos.y);
  return true;
}

void MouseManager::MouseDragging(int item, const wxPoint& pos){
  printf("Dragging: %2d, %4d, %4d\n", item, pos.x, pos.y);
}
void MouseManager::MouseDragEnd(int item, const wxPoint& pos){
  printf("End: %2d, %4d, %4d\n", item, pos.x, pos.y);
  dragdrop->stopDrag();
}
void MouseManager::MouseDragCancelled(int item){
  printf("DragCancel: %2d\n",item);
}

void MouseManager::MouseClickCancelled(int item){
  printf("ClickCancel: %2d\n",item);
}

CatalogueMouseManager::CatalogueMouseManager(Catalogue * catalogue, DragDropHelp * dragdrop)
      :MouseManager(catalogue, dragdrop)
{
  this->catalogue = catalogue;
}

int CatalogueMouseManager::MouseHitTest(const wxPoint& pos){
  return catalogue->hitTest(pos);
}

bool CatalogueMouseManager::MouseClicked(int item){
  printf("Clicked: %2d\n",item);
  catalogue->select(item);
  return true;
}
void CatalogueMouseManager::MouseDragging(int item, const wxPoint& pos){
  dragdrop->updateDragging(pos, DRAGDROP_CATALOG);
  catalogue->Refresh();
  printf("Dragging: %2d, %4d, %4d\n", item, pos.x, pos.y);
}

bool CatalogueMouseManager::MouseDragBegin(int item, const wxPoint& pos){
  catalogue->startDrag(item, pos);
  return true;
}

CatalogueMouseManager::~CatalogueMouseManager(){

}
