/*
  SE 2014
  Group 8
*/

#include "Semester.h"

Semester::Semester(Course *croot){
  root = new Node(croot);
  total_width = 240;
  total_height = y_start + 60;
  drageffect = false;
  dragging = false;
}

Semester::Semester(){
  total_height = y_start;
  root = NULL;
  total_width = 240;
  drageffect = false;
  dragging = false;
}

Semester::~Semester(){

}

void Semester::SetRoot(Course *course){
  Node *temp;
  if(course != NULL){
    temp = new Node(course);
  }
  else{
    temp = new Node(NODE_SPLIT);
  }
  if(root == NULL){
    if(temp->GetNodeType() == NODE_NORMAL)
      total_height += 60;
    else if(temp->GetNodeType() == NODE_SPLIT)
      total_width += 250;
  }
  else
    temp->SetChild(root);
  root = temp;
}//SetRoot

Node* Semester::AddChild(Node *parent, Course *child, unsigned int index){
  Node *retnode = new Node(child);
  parent->SetChild(retnode, index);
  return retnode;
}//AddChild

Node* Semester::AddChild(Node *parent, Course *child){
  Node *retnode = new Node(child);
  parent->SetChild(retnode);
  return retnode;
}//AddChild

Node* Semester::CreateSplit(Node *parent){
  Node *retnode = new Node(NODE_SPLIT);
  parent->SetChild(retnode);
  total_width += 250;
  return retnode;
}//createSplit

Node* Semester::CreateChoice(Node *parent, std::vector<Course*> options){
  Node *retnode = new Node(NODE_CHOICE);
  std::vector<Node*> choices;
  for(int i = 0; i < options.size(); i++)
    choices.push_back(new Node(options[i]));
  retnode->SetChoices(choices);
  return retnode;
}//CreateChoice

void Semester::setPositions(unsigned int x_start){
  unsigned int x = x_start;
  if(total_width != 240)
    x = determineStartX(root, x_start);

  setLine(x, y_start, root, x_start);
}//setPositions

void Semester::show(wxDC& dc, wxPoint dragpos){
  this->dragpos = dragpos;
  dragging = true;
  showLine(dc, root);
  dragging = false;
}//show

void Semester::show(wxDC& dc){
  showLine(dc, root);
}//show

void Semester::checkDragEffect(Node *node){
  int x = node->GetX(),
      y = node->GetY(),
      x_drag = dragpos.x,
      y_drag = dragpos.y;
  if(x - 50 < x_drag && x_drag < x + 120){
    if(y - 20 < y_drag && y_drag < y + 30)
      drageffect = true;
  }
}

void Semester::setLine(unsigned int sx, unsigned int sy, Node *snode, unsigned int x_start){
  Node *temp = snode;
  unsigned int x = sx,
               y = sy;
  while(temp != NULL){
    temp->SetPosition(x, y);
    switch(temp->GetNodeType()){
      case NODE_NORMAL:
        y += 70;
        temp = temp->GetChild();
        break;
      case NODE_SPLIT:
        setLine(determineStartX(temp->GetChild(1), x + 125), y, temp->GetChild(1), x + 125);
        temp = temp->GetChild();
        x = determineStartX(temp, x_start);
        break;
      case NODE_CHOICE:
      default:
        temp = temp->GetChild();
        break;
    }
  }
}//setLine

void Semester::showLine(wxDC& dc, Node *snode){
  Node *temp = snode;
  bool dragtemp;
  int x, y;
  while(temp != NULL){
    if(dragging && !drageffect)
      checkDragEffect(temp);
    switch(temp->GetNodeType()){
      case NODE_NORMAL:
        y = (drageffect)?temp->GetY()+70:temp->GetY();
        dc.DrawBitmap(temp->GetCourse()->bitmap, temp->GetX(), y);
        temp = temp->GetChild();
        break;
      case NODE_SPLIT:
        dragtemp = drageffect;
        showLine(dc, temp->GetChild(1));
        drageffect = dragtemp;
        temp = temp->GetChild();
        break;
      case NODE_CHOICE:
      default: break;
    }
  }
  drageffect = false;
}//showLine

unsigned int Semester::determineStartX(Node *snode, unsigned int s){
  unsigned int x_start = s;
  Node *temp = snode;
  bool split = false;
  while(temp != NULL){
    if(temp->GetNodeType() == NODE_SPLIT){
      if(split)
        x_start += 250;
      else{
        split = true;
        x_start += 125;
      }
    }
    temp = temp->GetChild();
  }
  return x_start;
}

void Semester::determineHeight(){
  total_height = y_start;
  Node *temp = root;
  while(temp != NULL){
    total_height += 70;
    temp = temp->GetChild();
  }
}