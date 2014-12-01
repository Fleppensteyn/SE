/*
  SE 2014
  Group 8
*/

#ifndef MOUSEMANAGER_H_
#define MOUSEMANAGER_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "newmouseman/mousemanagermod.h"

#include "DragDropHelp.h"

class Catalogue;
class Curriculum;

class MouseManager : public wxMouseEventsManagerMod
{
public:
  MouseManager(wxWindow * window, DragDropHelp * dragdrop);
  virtual ~MouseManager();

protected:
  virtual int MouseHitTest(const wxPoint&);
  virtual bool MouseClicked(int);
  virtual bool MouseDragBegin(int, const wxPoint&);
  virtual void MouseDragging(int, const wxPoint&);
  virtual void MouseDragEnd(int, const wxPoint&);
  virtual void MouseDragCancelled(int);
  virtual void MouseClickCancelled(int);
  DragDropHelp * dragdrop;
};

class CatalogueMouseManager : public MouseManager
{
public:
  CatalogueMouseManager(Catalogue * catalogue, DragDropHelp * dragdrop);
  virtual ~CatalogueMouseManager();

private:
  virtual int MouseHitTest(const wxPoint& pos);
  virtual bool MouseClicked(int item);
  virtual bool MouseDragBegin(int item, const wxPoint& pos);
  virtual void MouseDragging(int, const wxPoint& pos);
  int previouslyClickedItem;
  virtual void MouseDragEnd(int, const wxPoint&);
  // virtual void MouseDragCancelled(int item);
  // virtual void MouseClickCancelled(int item);

  Catalogue * catalogue;

};

class CurriculumMouseManager : public MouseManager
{
public:
  CurriculumMouseManager(Curriculum * curriculum, DragDropHelp * dragdrop);
  virtual ~CurriculumMouseManager();

private:
  virtual int MouseHitTest(const wxPoint& pos);
  virtual bool MouseClicked(int item);
  virtual bool MouseDragBegin(int item, const wxPoint& pos);
  virtual void MouseDragging(int, const wxPoint& pos);
  virtual void MouseDragEnd(int item, const wxPoint&);
  // virtual void MouseDragCancelled(int item);
  // virtual void MouseClickCancelled(int item);

  Curriculum * curriculum;

};

#include "Catalogue.h"
#include "Curriculum.h"

#endif /* MOUSEMANAGER_H_ */
