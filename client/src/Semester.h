/*
  SE 2014
  Group 8
*/

#ifndef SEMESTER_H_
#define SEMESTER_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Courses.h"
#include "Node.h"
#include <vector>

const unsigned int y_start = 80;

class Semester{
public:
  //Sets the root for this 'new' semester
  Semester(Course *croot);
  Semester();
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

  void setPositions(unsigned int x_start);
  void show(wxDC& dc);

  unsigned int getWidth(){return total_width;}
  unsigned int getHeight(){determineHeight(); return total_height;}

private:
  Node *root;
  unsigned int total_width;
  unsigned int total_height;

  void setLine(unsigned int sx, unsigned int sy, Node *snode, unsigned int x_start);
  void showLine(wxDC& dc, Node *snode);
  unsigned int determineStartX(Node *snode, unsigned int s);
  void determineHeight();
};

#endif /* SEMESTER_H_ */