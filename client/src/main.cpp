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

//The main application class
class App : public wxApp
{
public:
  //Initializes the program
  virtual bool OnInit();
};

enum{
  ID_LOGOUT,
  ID_CLOSE_TAB
};

//The frame within which the entire program is run.
class Frame : public wxFrame
{
public:
  //Constructor, initiates the login screen and sets the title and footnote
  // title - The title of the program
  // pos - The start position (top left corner) of the program
  // size - The size at the start of the program
  Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

  //Exits the program when an wxID_EXIT event occurs
  // event - The wxID_EXIT event
  void OnExit(wxCommandEvent& event);

  //Attempts to log in and on succes switches the program to the Overview panel
  // event - The event thrown by the 'Login' button
  void OnSubmit(wxCommandEvent& event);

  //If logged in, logs the user out and returns to login screen
  void OnLogout(wxCommandEvent& event);

  //If in overview, closes the tab that is currently open
  void OnCloseTab(wxCommandEvent& event);

  //Switches between the Login and Overview panel
  void SwitchPanels();

private:
  Login *panel_login; //The login panel for all login functionality and components
  Overview *panel_overview; //The overview panel showing the standard overview once logged in
  wxStaticText *failed_login_txt; //The error message that is displayed after a failed login attempt
  wxMenuItem *logout; //Logout menu item
  wxMenuItem *close_tab; //Menu item to close open tab

  bool s; 
  wxDECLARE_EVENT_TABLE();
};

//A summary of all events of the class Frame that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU    (wxID_EXIT, Frame::OnExit)
  EVT_MENU    (ID_LOGOUT, Frame::OnLogout)
  EVT_MENU    (ID_CLOSE_TAB, Frame::OnCloseTab)
  EVT_BUTTON  (ID_SUBMIT, Frame::OnSubmit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);

bool App::OnInit(){
  Frame *frame = new Frame("SE-2014", wxPoint(50,50), wxSize(700, 500));
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
      : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  wxMenu *menuFile = new wxMenu; //The File menu
  close_tab = menuFile->Append(ID_CLOSE_TAB, wxT("& Close tab"));
  close_tab->Enable(false);
  menuFile->AppendSeparator();
  logout = menuFile->Append(ID_LOGOUT, wxT("&Logout"));
  logout->Enable(false);
  menuFile->Append(wxID_EXIT);

  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(menuFile, "&File");
  SetMenuBar(menuBar);

  CreateStatusBar(1);
  SetStatusText("");

  //Create the error message that is displayed on a failed login attempt
  GetStatusBar()->SetForegroundColour(wxColour(wxT("RED")));
  failed_login_txt = new wxStaticText(GetStatusBar(), wxID_ANY,wxT("Login failed: incorrect username and/or password"), wxPoint(3, 5), wxDefaultSize, 0 );
  failed_login_txt->Show(false);

  s = false; //Temporarely used for login simulation
  
  //Create the program title bar at the top of the screen
  wxStaticText *program_title = new wxStaticText(this, wxID_ANY, "Curriculum Viewer", wxPoint(50,50), wxSize(100,70) );
  wxFont font = program_title->GetFont();
  font.Scale(4);
  program_title->SetFont(font);
  program_title->SetForegroundColour(wxColour(wxT("WHITE")));
  program_title->SetBackgroundColour(wxColour(0xFF,0x55,0x33));

  //Create the bar at the bottom of the screen
  wxStaticText *group_info = new wxStaticText(this, wxID_ANY, L"\u00a9  2014 Genius@Work\nPowered by Group8", wxPoint(50,50), wxSize(100, 30));
  font = group_info->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  group_info->SetFont(font);
  group_info->SetForegroundColour(wxColour(wxT("WHITE")));
  group_info->SetBackgroundColour(wxColour(0xB6,0xB6,0xB6));

  //Initiate the login and overview panels
  panel_login = new Login(this, 300, 400, 200, 300);
  panel_overview = new Overview(this, 50, 50, 1000, 800);
  panel_overview->Hide();

  //Arrangement of panels and bars onscreen.
  wxBoxSizer *panels = new wxBoxSizer(wxVERTICAL);
  panels->Add(program_title, 0, wxEXPAND | wxALIGN_CENTER);
  panels->Add(panel_login, 1, wxEXPAND);
  panels->Add(panel_overview, 1, wxEXPAND);
  panels->Add(group_info, 0, wxEXPAND);
  SetSizer(panels);
}//Frame

void Frame::OnExit(wxCommandEvent& event){
  Close(true);
}//OnExit

void Frame::OnSubmit(wxCommandEvent& event){
  if(failed_login_txt->IsShown())   //If there was a previous failed login attempt
    failed_login_txt->Show(false);  //remove the error message
  wxString msg = "Checking login info...";
  SetStatusText(msg);
  //do login check here!! (replace 's' with return boolean of login check)
  if(s){  //login successful 
    SetStatusText("Login successful");
    SwitchPanels();
  }
  else{ //login failed
    SetStatusText("");
    failed_login_txt->Show(true);
    s = true; //temporarely used to simulate login functionality
  }
}//OnSubmit

void Frame::OnLogout(wxCommandEvent& event){
  SwitchPanels();
}//OnLogout

void Frame::OnCloseTab(wxCommandEvent& event){
  panel_overview->OnCloseTab();
}

void Frame::SwitchPanels(){
  if(panel_login->IsShown()){ //Switch from login to overview
    SetSize(1500,800);
    panel_login->Hide();
    panel_overview->Show();
    logout->Enable(true);
    close_tab->Enable(true);
  } else {  //Switch from overview back to login
    SetSize(700,500);
    panel_overview->Hide();
    panel_login->Show();
    logout->Enable(false);
    close_tab->Enable(false);
  }
  Layout();
}//SwithPanels