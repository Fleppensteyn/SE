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

#include "wx/mousemanager.h"

#include "DragDropHelp.h"

class Catalogue;

class MouseManager : public wxMouseEventsManager
{
public:
  MouseManager(wxWindow * window, DragDropHelp * dragdrop);
  virtual ~MouseManager();

protected:
  virtual int MouseHitTest(const wxPoint& pos);
  virtual bool MouseClicked(int item);
  virtual bool MouseDragBegin(int item, const wxPoint& pos);
  virtual void MouseDragging(int item, const wxPoint& pos);
  virtual void MouseDragEnd(int item, const wxPoint& pos);
  virtual void MouseDragCancelled(int item);
  virtual void MouseClickCancelled(int item);
  DragDropHelp * dragdrop;
};

class CatalogueMouseManager : public MouseManager
{
public:
  CatalogueMouseManager(Catalogue * catalogue, DragDropHelp * dragdrop);
  virtual ~CatalogueMouseManager();

protected:
  virtual int MouseHitTest(const wxPoint& pos);
  virtual bool MouseClicked(int item);
  virtual bool MouseDragBegin(int item, const wxPoint& pos);
  virtual void MouseDragging(int item, const wxPoint& pos);
  // virtual void MouseDragEnd(int item, const wxPoint& pos);
  // virtual void MouseDragCancelled(int item);
  // virtual void MouseClickCancelled(int item);

private:
  Catalogue * catalogue;

};

#include "Catalogue.h"

#endif /* MOUSEMANAGER_H_ */
