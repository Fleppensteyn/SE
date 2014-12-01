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
  Node(Course *c); //Normal node
  Node(NodeType nt); //only specify nodetype

  ~Node();

  Course* GetCourse();
  NodeType GetNodeType();
  unsigned int GetChildCount();
  unsigned int GetExpectedChildren();
  Node* GetChild();
  Node* GetChild(unsigned int i);
  std::vector<Node*> GetChoices();
  unsigned int GetX();
  unsigned int GetY();
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