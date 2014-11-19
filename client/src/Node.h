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
  Node(Course *c) : course(c), nodetype(NODE_NORMAL), expected_children(1) {} //Normal node
  Node(NodeType nt); //only specify nodetype

  ~Node();

  Course* GetCourse(){return course;}
  NodeType GetNodeType(){return nodetype;}
  unsigned int GetChildCount(){return children.size();}
  unsigned int GetExpectedChildren(){return expected_children;}
  Node* GetChild(unsigned int i){return children[i];}

  void SetCourse(Course *course);
  void SetNodeType(NodeType nodetype);
  void SetChild(Node *node);
  void SetChild(Node *node, unsigned int index);
  void SetChoices(std::vector<Node*> nodes);

private:
  Course *course;
  NodeType nodetype;
  std::vector<Node*> children;
  std::vector<Node*> choices;
  unsigned int expected_children;
};

#endif /* NODE_H_ */