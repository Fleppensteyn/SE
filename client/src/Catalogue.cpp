/*
  SE 2014
  Group 8
*/

#include "Catalogue.h"

Catalogue::Catalogue(wxPanel *panel, Courses *courses, DragDropHelp *dragdrop)
      :wxScrolledCanvas(panel, wxID_ANY, wxPoint(100,100), wxSize(catalogue_width, 100))
{
  this->mousemanager = new CatalogueMouseManager(this, dragdrop);
  this->overview =  panel;
  this->courses = courses;
  this->dragdrop = dragdrop;
  yscroll = 20;
  selected = -1;

  SearchPars sp;
  filter(sp);
}

void Catalogue::filter(SearchPars pars){
  bmaps = courses->filter(pars);
  updateSizes();
}

void Catalogue::updateSizes(){
  SetVirtualSize(catalogue_width, (bmaps.size() * 65) + 5);
  SetScrollbars(0, 65, 1, bmaps.size(), false);
  SetScrollRate(0, yscroll);
  Refresh();
}

int Catalogue::hitTest(const wxPoint& pos){
  wxPoint upos = CalcUnscrolledPosition(pos);
  printf("%4d %4d\n", upos.x, upos.y);
  if (upos.x < 2 || upos.x > coursewidth + 2 ||
      upos.y % (courseheight + 5) < 5 || upos.y > bmaps.size() * 65){
    select(-1);
    return wxNOT_FOUND;
  } else
    return upos.y/65;
}

void Catalogue::select(int index){
  selected = index;
  Refresh();
}

void Catalogue::editCourse(int index) {
	Course *course = bmaps[index];
	CourseEditor *editor = new CourseEditor(course);
  while (editor->ShowModal() == wxID_OK){
    std::vector<wxString> data = editor->getData();
    int ret = 1;//courses->editCourse(data);
    if(ret >= 0){
      return;
    }
    else if(ret == -1){
      editor->DisplayError(ERROR_EDIT_COURSE_ALREADY_EXISTS);
    }
  } 
}

void Catalogue::OnDraw(wxDC& dc){
  unsigned int wincap = (GetClientSize().GetHeight()/65) + 2,
               curind = ((GetViewStart().y*yscroll)/65);

  for (unsigned i = curind; i < curind+wincap && i < bmaps.size(); i++ )
    dc.DrawBitmap(bmaps[i]->bitmap, 2, 5 + 65 * i);

  dc.SetBrush(wxBrush(wxColour("#008888"), wxBRUSHSTYLE_TRANSPARENT));
  dc.SetPen(wxPen(wxColour("#FF0000"), 3));
  if (selected >= curind && selected < curind + wincap)
    dc.DrawRectangle(1, 4 + 65 * selected, coursewidth + 2, courseheight + 2);
  wxPoint drawpos;
  if (this->dragdrop->needsDrawing(drawpos, DRAGDROP_CATALOG)){
    drawpos = CalcUnscrolledPosition(drawpos);
    dc.DrawBitmap(this->dragdrop->getCourse()->bitmap, drawpos);
  }
  if (dragdrop->getCourse() != NULL)
    this->overview->Refresh();
}

Catalogue::~Catalogue(){
  bmaps.clear();
  delete mousemanager;
}

void Catalogue::startDrag(int item, const wxPoint& pos){
  wxPoint unscpos = CalcUnscrolledPosition(pos);
  wxPoint dragpoint(unscpos.x -2, (unscpos.y % 65) - 5);
  this->dragdrop->startDrag(pos, dragpoint, bmaps[item], DRAGDROP_CATALOG);
  Refresh();
}
