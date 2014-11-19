/*
  SE 2014
  Group 8
*/

#include "Semester.h"

Semester::Semester(Course *croot){
  root = new Node(croot);
}

Semester::~Semester(){

}

void Semester::SetRoot(Course *course){
  Node *temp = new Node(course);
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