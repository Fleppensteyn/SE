/*
  SE 2014
  Group 8
*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "LogIn.h"

class App : public wxApp
{
public:
  virtual bool OnInit();

};

class Frame : public wxFrame
{
public:
  Frame(const wxString& title, const wxPoint& pos, const wxSize& size);
  void OnExit(wxCommandEvent& event);
  void OnSubmit(wxCommandEvent& event);
private:
  LogIn *panel;

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU    (wxID_EXIT, Frame::OnExit)
  EVT_BUTTON  (ID_SUBMIT, Frame::OnSubmit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);

bool App::OnInit(){
  Frame *frame = new Frame("SE-2014", wxPoint(50,50), wxSize(600, 400));
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
      : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append(wxID_EXIT);

  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(menuFile, "&File");
  SetMenuBar(menuBar);

  CreateStatusBar(1);
  SetStatusText("");

  panel = new LogIn(this, 300, 400, 200, 300);
}

void Frame::OnExit(wxCommandEvent& event){
  Close(true);
}

void Frame::OnSubmit(wxCommandEvent& event){
  wxString msg = "Checking login info...";
  //msg << " Username: " << panel->getUsername() << " Password: " << panel->getPassword();
  SetStatusText(msg);
}
