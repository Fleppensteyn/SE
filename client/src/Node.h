/*
  SE 2014
  Group 8
*/

#ifndef NODE_H_
#define NODE_H_

#include "Courses.h"
#include <vector>

typedef enum __nodetype {
  NODE_NORMAL,
  NODE_SPLIT,
  NODE_CHOICE
} NodeType;

class Node{
public:
  Node(Course *c) : course(c), nodetype(NODE_NORMAL), parent(NULL), expected_children(1) {} //Normal node
  Node(NodeType nt); //only specify nodetype

  ~Node();

  Course* GetCourse(){return course;}
  NodeType GetNodeType(){return nodetype;}
  unsigned int GetChildCount(){return children.size();}
  unsigned int GetExpectedChildren(){return expected_children;}
  Node* GetChild(){return (children.size() > 0)?children[0]:NULL;}
  Node* GetChild(unsigned int i){return (children.size() > i)?children[i]:NULL;}
  std::vector<Node*> GetChoices(){return choices;}
  unsigned int GetX(){return x;}
  unsigned int GetY(){return y;}
  Node* GetParent();

  void SetCourse(Course *course);
  void SetNodeType(NodeType nodetype);
  void SetParent(Node * node);
  void SetChild(Node *node);
  void SetChild(Node *node, unsigned int index);
  void SetChoices(std::vector<Node*> nodes);
  void SetPosition(unsigned int x, unsigned int y);

private:
  Course *course;
  NodeType nodetype;
  Node *parent;
  std::vector<Node*> children;
  std::vector<Node*> choices;
  unsigned int expected_children;
  unsigned int x;
  unsigned int y;
};

#endif /* NODE_H_ */