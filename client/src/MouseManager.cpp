/*
  SE 2014
  Group 8
*/

#include "MouseManager.h"

MouseManager::MouseManager(wxPanel *panel)
      :wxMouseEventsManager(panel)
{

}

MouseManager::~MouseManager(){

}


int MouseManager::MouseHitTest(const wxPoint& pos){
  printf("Hit: %4d,%4d \n",pos.x, pos.y);
  return 1;
}

bool MouseManager::MouseClicked(int item){
  return true;
}

bool MouseManager::MouseDragBegin(int item, const wxPoint& pos){
  return true;
}

void MouseManager::MouseDragging(int item, const wxPoint& pos){

}
void MouseManager::MouseDragEnd(int item, const wxPoint& pos){

}
void MouseManager::MouseDragCancelled(int item){

}

void MouseManager::MouseClickCancelled(int item){

}

