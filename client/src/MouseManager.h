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

class MouseManager : public wxMouseEventsManager
{
public:
  MouseManager(wxPanel *panel);
  virtual ~MouseManager();

protected:
  int MouseHitTest(const wxPoint& pos);
  bool MouseClicked(int item);
  bool MouseDragBegin(int item, const wxPoint& pos);
  void MouseDragging(int item, const wxPoint& pos);
  void MouseDragEnd(int item, const wxPoint& pos);
  void MouseDragCancelled(int item);
  void MouseClickCancelled(int item);

};


#endif /* MOUSEMANAGER_H_ */
