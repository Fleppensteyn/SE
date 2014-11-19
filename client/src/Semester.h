/*
  SE 2014
  Group 8
*/

#ifndef SEMESTER_H_
#define SEMESTER_H_

#include "Courses.h"
#include "Node.h"
#include <vector>

class Semester{
public:
  //Sets the root for this 'new' semester
  Semester(Course *croot);
  ~Semester();

  //Returns the root
  Node* GetRoot(){return root;}
  //Set root to different node
  void  SetRoot(Course *course);
  //Add course 'child' as the 'index' child of the 'parent' course
  Node* AddChild(Node *parent, Course *child, unsigned int index);
  //Add course 'child' as the child of the 'parent' course
  Node* AddChild(Node *parent, Course *child);
  //Creates a split node as child of 'parent' course
  Node* CreateSplit(Node *parent);
  //Creates a choice node as child of 'parent' course
  Node* CreateChoice(Node *parent, std::vector<Course*> options);

private:
  Node *root;
};

#endif /* SEMESTER_H_ */