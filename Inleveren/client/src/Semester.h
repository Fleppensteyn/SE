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
  Node* GetRoot();
  //Set root to different node
  void  SetRoot(Course *course);
  void  SetRootNode(Node *node);
  //Add course 'child' as the 'index' child of the 'parent' course
  Node* AddChild(Node *parent, Course *child, unsigned int index);
  //Add course 'child' as the child of the 'parent' course
  Node* AddChild(Node *parent, Course *child);
  //Creates a split node as child of 'parent' course
  Node* CreateSplit(Node *parent);
  //Creates a choice node as child of 'parent' course
  Node* CreateChoice(Node *parent, std::vector<Course*> options);

  void setPositions(unsigned int x_start);
  void show(wxDC& dc, wxPoint dragpos);
  void show(wxDC& dc);

  unsigned int getWidth();
  unsigned int getHeight();
  void getNodes(std::vector<Node*> &nodes, Node *node);

  bool drop(wxPoint dragpos, Course *course);

private:
  Node *root;
  unsigned int total_width;
  unsigned int total_height;
  unsigned int start_x;
  wxPoint dragpos;
  bool drageffect, dragging;

  std::vector<int> checkDragEffect(Node *node);
  std::vector<int> checkUnder(Node *node);
  std::vector<int> checkUnder(int x, int y);
  void setLine(unsigned int sx, unsigned int sy, Node *snode, unsigned int x_start);
  void showLine(wxDC& dc, Node *snode, Node *par);
  bool dropLine(Node *snode, Node *par, Course *course);
  void dropUpdate(Node *node, Node *child, Course *course);
  unsigned int determineStartX(Node *snode, unsigned int s);
  void determineHeight();
  void determineWidth(Node *node);
};

#endif /* SEMESTER_H_ */