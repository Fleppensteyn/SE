/*
  SE 2014
  Group 8
*/

#include "Node.h"

Node::Node(NodeType nt){
  SetNodeType(nt);
}

Node::~Node(){
  children.clear();
}

void Node::SetCourse(Course *course){
  if(nodetype == NODE_NORMAL){
    this->course = course;
  }
}//SetCourse

void Node::SetNodeType(NodeType nodetype){
  this->nodetype = nodetype;
  switch(nodetype){
    case NODE_NORMAL:
    case NODE_CHOICE:
      expected_children = 1; break;
    case NODE_SPLIT:
      expected_children = 2; break;
    default:
      expected_children = 0; break;
  }
}//SetNodeType

void Node::SetChild(Node *node){
  SetChild(node, 0);
}//SetChild

void Node::SetChild(Node *node, unsigned int index){
  switch(nodetype){
    case NODE_NORMAL:
    case NODE_CHOICE:
      if(children.size() > 0){
        node->SetChild(children[1]);
        children.clear();
      }
      children.push_back(node);
      break;
    case NODE_SPLIT:
      if(children.size() == expected_children){
        //nothing at this time, but in future move to larger split
      }
      else if(index < children.size()){
        children.insert(children.begin()+index, node);
      }
      else{
        children.push_back(node);
      }
      break;
    default: break;
  }
}//SetChild

void Node::SetChoices(std::vector<Node*> nodes){
  if(nodetype == NODE_CHOICE)
    choices = nodes;
}//SetChoices

void Node::SetPosition(unsigned int x, unsigned int y){
  this->x = x;
  this->y = y;
}