/*
  SE 2014
  Group 8
*/

#include "Curriculum.h"

wxDEFINE_EVENT(EVT_SELECTED, wxCommandEvent);
wxDEFINE_EVENT(EVT_NO_SELECT, wxCommandEvent);


Curriculum::Curriculum(wxPanel *overview, DragDropHelp * dragdrop)
      :wxScrolledCanvas(overview, wxID_ANY, wxPoint(100,100), wxSize(curriculum_width, 100))
{
  SetDoubleBuffered(true);
  this->dragdrop = dragdrop;
  this->dragdrop->setCurriculum(this);
  this->mm = new CurriculumMouseManager(this, dragdrop);
  this->overview = overview;
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
  if(vec.size() == 0){
    Refresh();
    return;
  }
  semesters.clear();
  semesters = vec;

  selected = -1;
  wxCommandEvent event(EVT_NO_SELECT);
  wxPostEvent(this, event);

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
  if (dragdrop->getCourse() != NULL)
    this->overview->Refresh();
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
}//determineHeight

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
  wxCommandEvent event(EVT_SELECTED);
  wxPostEvent(this, event);
  Refresh();
}

void Curriculum::startDrag(int item, const wxPoint& pos){
  selected = item;
  wxCommandEvent event(EVT_SELECTED);
  wxPostEvent(this, event);
  Node *parent = nodes[selected]->GetParent();
  Node *child = nodes[selected]->GetChild();
  int i;
  if(parent == NULL){
    for(i = 0; i < semesters.size(); i++){
      if(semesters[i]->GetRoot() == nodes[selected])
        semesters[i]->SetRootNode(child);
    }
    if(child != NULL)
      child->SetParent(NULL);
  }
  else{
    switch(parent->GetNodeType()){
      case NODE_NORMAL:
      case NODE_CHOICE:
        parent->SetChild(NULL);
        if(child != NULL){
          parent->SetChild(child);
          child->SetParent(parent);
        }
        break;
      case NODE_SPLIT:
        for(i = 0; i < 2; i++){
          if(parent->GetChild(i) == nodes[selected])
            break;
        }
        parent->SetChild(NULL, i);
        if(child != NULL){
          parent->SetChild(child, i);
          child->SetParent(parent);
        }
      default: break;
    }
  }
  drawCurriculum();
  wxPoint unscpos = CalcUnscrolledPosition(pos);
  wxPoint dragpoint(unscpos.x - nodes[item]->GetX(), unscpos.y - nodes[item]->GetY());
  this->dragdrop->startDrag(pos, dragpoint, nodes[item]->GetCourse(), DRAGDROP_CURRICULUM);
}

void Curriculum::endDrag(int item){
  wxPoint dragpos;
  if (!dragdrop->needsDrawing(dragpos, DRAGDROP_CURRICULUM)){
    if(item != -1){
      nodes.erase(nodes.begin() + selected);
      selected = -1;
      wxCommandEvent event(EVT_NO_SELECT);
      wxPostEvent(this, event);
      //make sure the database updates!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
  }
  else{
    //see if it is to be placed somewhere
    bool changed = false;
    for(int i = 0; i < semesters.size(); i++){
      if(semesters[i]->drop(dragpos, dragdrop->getCourse()))
        changed = true;
    }
    if(changed){
      if(item != -1){
        nodes.erase(nodes.begin() + selected);
        selected = -1;
        wxCommandEvent event(EVT_NO_SELECT);
        wxPostEvent(this, event);
      }
      collectAllNodes();
      //update database!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }
    else if(item != -1) //else reset it to it's previous position
      resetNode();
    
  }
  removeEmptySplits();
  drawCurriculum();
  Refresh();
}//endDrag

void Curriculum::resetNode(){
  Node *parent = nodes[selected]->GetParent();
  Node *child = nodes[selected]->GetChild();
  int i;
  if(parent == NULL){
    for(i = 0; i < semesters.size(); i++){
      if(semesters[i]->GetRoot() == child)
        semesters[i]->SetRootNode(nodes[selected]);
    }
    if(child != NULL)
      child->SetParent(nodes[selected]);
  }
  else{
    switch(parent->GetNodeType()){
      case NODE_NORMAL:
      case NODE_CHOICE:
        parent->SetChild(NULL);
        parent->SetChild(nodes[selected]);
        if(child != NULL)
          child->SetParent(nodes[selected]);
        break;
      case NODE_SPLIT:
        for(i = 0; i < 2; i++){
          if(parent->GetChild(i) == child)
            break;
        }
        if(child != NULL){
          parent->SetChild(NULL, i);
          child->SetParent(nodes[selected]);
        }
        parent->SetChild(nodes[selected], i);
      default: break;
    }
  }
}//resetNode

void Curriculum::removeEmptySplits(){
  int i, j = 0;
  for(i = 0; i < nodes.size(); i++){
    if(nodes[i]->GetNodeType() == NODE_SPLIT && nodes[i]->GetChildCount() == 0){
      Node *par = nodes[i]->GetParent();
      if(par == NULL){
        for(; j < semesters.size(); j++){
          if(semesters[j]->GetRoot() == nodes[i]){
            semesters[j]->SetRootNode(NULL);
          }
        }
      }
      else {
        if(par->GetNodeType() == NODE_SPLIT){
          for(j = 0; j < 2; j++){
            if(par->GetChild(j) == nodes[i])
              break;
          }
        }
        par->SetChild(NULL, j);
      }
      nodes.erase(nodes.begin() + i);
    }
  }
}

void Curriculum::insertSplit(){
  Node * parent = nodes[selected]->GetParent();
  Node * splitnode = new Node(NODE_SPLIT);
  int i = 0;
  if(parent == NULL){
    for(; i < semesters.size(); i++){
      if(semesters[i]->GetRoot() == nodes[selected])
        break;
    }
    semesters[i]->SetRootNode(splitnode);
  }
  else{
    if(parent->GetNodeType() == NODE_SPLIT){
      for(; i < 2; i++){
        if(parent->GetChild(i) == nodes[selected])
          break;
      }
    }
    parent->SetChild(NULL, i);
    parent->SetChild(splitnode, i);
    splitnode->SetParent(parent);
  }
  splitnode->SetChild(NULL);
  splitnode->SetChild(nodes[selected]);
  nodes[selected]->SetParent(splitnode);
  nodes.push_back(splitnode);

  selected = -1;
  wxCommandEvent event(EVT_NO_SELECT);
  wxPostEvent(this, event);

  //update the database!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  //or not, this change can also be propagated to database next time something is moved
  //saving for just an added split seems kind of futile

  drawCurriculum();
  Refresh();
}