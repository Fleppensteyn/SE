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
  start_x = 0;
}

Semester::Semester(){
  total_height = y_start;
  root = NULL;
  total_width = 240;
  drageffect = false;
  dragging = false;
  start_x = 0;
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

void Semester::SetRootNode(Node *node){
  root = node;
}

Node* Semester::AddChild(Node *parent, Course *child, unsigned int index){
  Node *retnode = new Node(child);
  parent->SetChild(retnode, index);
  retnode->SetParent(parent);
  return retnode;
}//AddChild

Node* Semester::AddChild(Node *parent, Course *child){
  Node *retnode = new Node(child);
  parent->SetChild(retnode);
  retnode->SetParent(parent);
  return retnode;
}//AddChild

Node* Semester::CreateSplit(Node *parent){
  Node *retnode = new Node(NODE_SPLIT);
  parent->SetChild(retnode);
  retnode->SetParent(parent);
  total_width += 250;
  return retnode;
}//createSplit

Node* Semester::CreateChoice(Node *parent, std::vector<Course*> options){
  Node *retnode = new Node(NODE_CHOICE);
  std::vector<Node*> choices;
  for(int i = 0; i < options.size(); i++)
    choices.push_back(new Node(options[i]));
  retnode->SetChoices(choices);
  retnode->SetParent(parent);
  return retnode;
}//CreateChoice

void Semester::setPositions(unsigned int x_start){
  start_x = x_start;
  unsigned int x = x_start;
  if(total_width != 240)
    x = determineStartX(root, x_start);

  setLine(x, y_start, root, x_start);
}//setPositions

void Semester::show(wxDC& dc, wxPoint dragpos){
  this->dragpos = dragpos;
  dragging = true;
  showLine(dc, root, NULL);
  dragging = false;
}//show

void Semester::show(wxDC& dc){
  showLine(dc, root, NULL);
}//show

std::vector<int> Semester::checkDragEffect(Node *node){
  std::vector<int> pos;
  int x = node->GetX(),
      y = node->GetY(),
      x_drag = dragpos.x,
      y_drag = dragpos.y;
  if(x - 50 < x_drag && x_drag < x + 120){
    if(y - 20 < y_drag && y_drag < y + 30){
      drageffect = true;
      pos.push_back(x);
      pos.push_back(y);
    }
  }
  return pos;
}

std::vector<int> Semester::checkUnder(Node *node){
  int x, y;
  if(node == NULL){
    x = start_x;
    y = y_start - 70;
  }
  else{
    x = node->GetX();
    y = node->GetY();
  }
  return checkUnder(x, y);
}

std::vector<int> Semester::checkUnder(int x, int y){
  std::vector<int> pos;
  int x_drag = dragpos.x,
      y_drag = dragpos.y;
  if(x - 50 < x_drag && x_drag < x + 120){
    if(y + 60 < y_drag){
      pos.push_back(x);
      pos.push_back(y);
    }
  }
  return pos;
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

void Semester::showLine(wxDC& dc, Node *snode, Node *par){
  Node *temp = snode,
       *temp2 = par;
  std::vector<int> pos;
  bool dragtemp;
  int x, y;
  while(temp != NULL){
    temp2 = temp;
    if(dragging && !drageffect){
      pos = checkDragEffect(temp);
      if(pos.size() != 0){
        dc.SetBrush(wxBrush(wxColour("#008888"), wxBRUSHSTYLE_TRANSPARENT));
        dc.SetPen(wxPen(wxColour("#000000"), 2));
        dc.DrawRectangle(pos[0], pos[1], 240, 60);
      }
    }
    switch(temp->GetNodeType()){
      case NODE_NORMAL:
        y = (drageffect)?temp->GetY()+70:temp->GetY();
        dc.DrawBitmap(temp->GetCourse()->bitmap, temp->GetX(), y);
        temp = temp->GetChild();
        break;
      case NODE_SPLIT:
        dragtemp = drageffect;
        showLine(dc, temp->GetChild(1), temp);
        drageffect = dragtemp;
        temp = temp->GetChild();
        break;
      case NODE_CHOICE:
      default: break;
    }
  }
  if(dragging && !drageffect){
    if(temp2 != NULL && temp2 == par){
      pos = checkUnder(temp2->GetX()+125, temp2->GetY() - 70);
    }
    else if(temp2 != NULL && temp2->GetNodeType() == NODE_SPLIT){
      pos = checkUnder(temp2->GetX()-125, temp2->GetY() - 70);
    }
    else
      pos = checkUnder(temp2);
    if(pos.size() != 0){
      dc.SetBrush(wxBrush(wxColour("#008888"), wxBRUSHSTYLE_TRANSPARENT));
      dc.SetPen(wxPen(wxColour("#000000"), 2));
      dc.DrawRectangle(pos[0], pos[1] + 70, 240, 60);
    }
  }
  else
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

void Semester::getNodes(std::vector<Node*> &nodes, Node *node){
  Node *temp = node;
  while(temp != NULL){
    nodes.push_back(temp);
    switch(temp->GetNodeType()){
      case NODE_NORMAL:
        temp = temp->GetChild();
        break;
      case NODE_SPLIT:
        getNodes(nodes, temp->GetChild(1));
        temp = temp->GetChild(0);
        break;
      case NODE_CHOICE:
      default: break;
    }
  }
}

bool Semester::drop(wxPoint dragpos, Course *course){
  this->dragpos = dragpos;
  return dropLine(root, NULL, course);
}

bool Semester::dropLine(Node *snode, Node *par, Course *course){
  Node *temp = snode,
       *temp2 = par;
  std::vector<int> pos;
  bool dragtemp;
  int x, y;
  while(temp != NULL){
    if(!drageffect){
      pos = checkDragEffect(temp);
      if(pos.size() != 0){
        dropUpdate(temp2, temp, course);
        drageffect = false;
        return true;
      }
    }
    temp2 = temp;
    switch(temp->GetNodeType()){
      case NODE_NORMAL:
        temp = temp->GetChild();
        break;
      case NODE_SPLIT:
        dragtemp = drageffect;
        if(dropLine(temp->GetChild(1), temp, course))
          return true;
        drageffect = dragtemp;
        temp = temp->GetChild();
        break;
      case NODE_CHOICE:
      default: break;
    }
  }
  if(!drageffect){
    if(temp2 != NULL && temp2 == par){
      pos = checkUnder(temp2->GetX()+125, temp2->GetY() - 70);
    }
    else if(temp2 != NULL && temp2->GetNodeType() == NODE_SPLIT){
      pos = checkUnder(temp2->GetX()-125, temp2->GetY() - 70);
    }
    else
      pos = checkUnder(temp2);
    if(pos.size() != 0){
      dropUpdate(temp2, temp, course);
      return true;
    }
  }
  else
    drageffect = false;
  return false;
}

void Semester::dropUpdate(Node *parent, Node *child, Course *course){
  Node *new_node = new Node(course);
  int i = 0;
  if(parent == NULL){
    root = new_node;
    if(child != NULL){
      new_node->SetChild(child);
      child->SetParent(new_node);
    }
  }
  else{
    if(parent->GetNodeType() == NODE_SPLIT){
      for(; i < 2; i++){
        if(parent->GetChild(i) == child)
          break;
      }
    }
    parent->SetChild(NULL, i);
    parent->SetChild(new_node, i);
    new_node->SetParent(parent);
    if(child != NULL){
      new_node->SetChild(child);
      child->SetParent(new_node);
    }
  }
}

void Semester::determineWidth(Node *node){
  if(node == root)
    total_width = 240;
  Node *temp = node;
  while(temp != NULL){
    switch(temp->GetNodeType()){
      case NODE_SPLIT:
        determineWidth(temp->GetChild(1));
        total_width += 250;
      default:
        temp = temp->GetChild();
        break;
    }
  }
}