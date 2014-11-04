/*
  SE 2014
  Group 8
*/

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Login.h"
#include "Overview.h"

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
  void SwitchPanels();

private:
  Login *panel_login;
  Overview *panel_overview;
  wxStaticText *failed_login_txt;
  bool s;
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
  GetStatusBar()->SetForegroundColour(wxColour(wxT("RED")));
  failed_login_txt = new wxStaticText(GetStatusBar(), wxID_ANY,wxT("Login failed: incorrect username and/or password"), wxPoint(3, 5), wxDefaultSize, 0 );
  failed_login_txt->Show(false);
  s = false;
  
  panel_login = new Login(this, 300, 400, 200, 300);
  panel_overview = new Overview(this, 50, 50, 1000, 800);
  panel_overview->Hide();

  wxBoxSizer *panels = new wxBoxSizer(wxVERTICAL);
  panels->Add(panel_login, 1, wxEXPAND);
  panels->Add(panel_overview, 1, wxEXPAND);
  SetSizer(panels);
}

void Frame::OnExit(wxCommandEvent& event){
  Close(true);
}

void Frame::OnSubmit(wxCommandEvent& event){
  if(failed_login_txt->IsShown())
    failed_login_txt->Show(false);
  wxString msg = "Checking login info...";
  //msg << " Username: " << panel_login->getUsername() << " Password: " << panel_login->getPassword();
  SetStatusText(msg);
  //do login check here!! (replace 's' with return boolean of login check)
  if(s){
    SetStatusText("Login successful");
    SwitchPanels();
  }
  else{
    SetStatusText("");
    failed_login_txt->Show(true);
    s = true;
  }
}

void Frame::SwitchPanels(){
  if(panel_login->IsShown()){
    panel_login->Hide();
    panel_overview->Show();
  } else {
    panel_overview->Hide();
    panel_overview->Show();
  }
  Layout();
}