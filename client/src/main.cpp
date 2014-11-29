/*
  SE 2014
  Group 8
*/

#ifdef __MINGW32__
#include "wx/setup.h"
#define wxUSE_IPV6 1
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

#include "Login.h"
#include "Overview.h"
#include "CourseCreator.h"
#include "CurriculumCreator.h"
#include "ServerCommunication.h"
#include <vector>

//The main application class
class App : public wxApp
{
public:
  //Initializes the program
  virtual bool OnInit();
};

enum{
  ID_LOGOUT             = 1,
  ID_NEW_COURSE         = 2,
  ID_NEW_CURRICULUM     = 3,
  ID_NEW_YEAR           = 4,
  ID_DELETE_YEAR        = 5,
  ID_DELETE_CURRICULUM  = 6,
  ID_RESET              = 7
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

  //If in overview, opens 'Create new course' dialog
  void OnNewCourse(wxCommandEvent& event);

  //If in overview, opens 'Create new curriculum' dialog
  void OnNewCurriculum(wxCommandEvent& event);

  void OnNewYear(wxCommandEvent& event);

  void OnDeleteYear(wxCommandEvent& event);

  void OnDeleteCurriculum(wxCommandEvent& event);

  void OnDeleteAll(wxCommandEvent& event);

  //Switches between the Login and Overview panel
  void SwitchPanels();

private:
  Login *panel_login; //The login panel for all login functionality and components
  Overview *panel_overview; //The overview panel showing the standard overview once logged in
  wxStaticText *failed_login_txt; //The error message that is displayed after a failed login attempt
  ServerCommunication * server_com;

  wxMenuBar *menubar_login; //menubar used for the login screen
  wxMenuBar *menubar_overview; //menubar used for the overview
  wxDECLARE_EVENT_TABLE();
};

//A summary of all events of the class Frame that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(Frame, wxFrame)
  EVT_MENU    (wxID_EXIT, Frame::OnExit)
  EVT_MENU    (ID_LOGOUT, Frame::OnLogout)
  EVT_MENU    (ID_NEW_COURSE, Frame::OnNewCourse)
  EVT_MENU    (ID_NEW_CURRICULUM, Frame::OnNewCurriculum)
  EVT_MENU    (ID_NEW_YEAR, Frame::OnNewYear)
  EVT_MENU    (ID_DELETE_YEAR, Frame::OnDeleteYear)
  EVT_MENU    (ID_DELETE_CURRICULUM, Frame::OnDeleteCurriculum)
  EVT_MENU    (ID_RESET, Frame::OnDeleteAll)
  EVT_BUTTON  (ID_SUBMIT, Frame::OnSubmit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);

bool App::OnInit(){
  Frame *frame = new Frame("Curriculum Builder by Genius@Work", wxPoint(50,50),
                           wxSize(700, 500));
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
      : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  server_com = new ServerCommunication("http://se.putman.pw/api.php");

  //Create the menu bar for the login screen
  wxMenu *menuFile_login = new wxMenu; //The login File menu
  menuFile_login->Append(wxID_EXIT);

  menubar_login = new wxMenuBar();
  menubar_login->Append(menuFile_login, "&File");
  SetMenuBar(menubar_login);

  //Create the menu bar for the overview screen
  wxMenu *menuFile_overview = new wxMenu; //The overview File menu
  menuFile_overview->Append(ID_LOGOUT, wxT("&Logout"));
  menuFile_overview->Append(wxID_EXIT);

  wxMenu *menuNew = new wxMenu;
  menuNew->Append(ID_NEW_COURSE, wxT("New course"));
  menuNew->Append(ID_NEW_CURRICULUM, wxT("New study program"));
  menuNew->Append(ID_NEW_YEAR, wxT("New year"));

  wxMenu *menuDelete = new wxMenu;
  menuDelete->Append(ID_DELETE_YEAR, wxT("Delete year"));
  menuDelete->Append(ID_DELETE_CURRICULUM, wxT("Delete study program"));
  menuDelete->Append(ID_RESET, wxT("Delete all"));

  menubar_overview = new wxMenuBar();
  menubar_overview->Append(menuFile_overview, "&File");
  menubar_overview->Append(menuNew, "&New");
  menubar_overview->Append(menuDelete, "&Delete");

  CreateStatusBar(1);
  SetStatusText("");

  //Create the error message that is displayed on a failed login attempt
  GetStatusBar()->SetForegroundColour(wxColour(wxT("RED")));
  failed_login_txt = new wxStaticText(GetStatusBar(), wxID_ANY,wxT("Login failed: incorrect username and/or password"), wxPoint(3, 5), wxDefaultSize, 0 );
  failed_login_txt->Show(false);
  GetStatusBar()->SetForegroundColour(wxColour(wxT("BLACK")));

  //Create the program title bar at the top of the screen
  wxPanel *title_panel = new wxPanel(this);
  title_panel->SetBackgroundColour(wxColour(0xFF,0x55,0x33));
  wxStaticText *program_title_text = new wxStaticText(title_panel, wxID_ANY,
                                  "Curriculum Builder", wxPoint(10,10), wxSize(100,60) );
  wxFont font = program_title_text->GetFont();
  font.Scale(4);
  program_title_text->SetFont(font);
  program_title_text->SetForegroundColour(wxColour(wxT("WHITE")));
  wxStaticBoxSizer *program_title = new wxStaticBoxSizer(wxHORIZONTAL,this,"");
  program_title->Add(title_panel, 1, wxEXPAND);

  //Create the bar at the bottom of the screen
  wxPanel *info_panel = new wxPanel(this);
  info_panel->SetBackgroundColour(wxColour(0xB6,0xB6,0xB6));
  wxStaticText *group_info_text = new wxStaticText(info_panel, wxID_ANY, L"\u00a9  2014 Genius@Work\nPowered by Group8", wxPoint(1,1), wxSize(100, 20));
  font = group_info_text->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  group_info_text->SetFont(font);
  group_info_text->SetForegroundColour(wxColour(wxT("WHITE")));
  wxStaticBoxSizer *group_info = new wxStaticBoxSizer(wxHORIZONTAL,this,"");
  group_info->Add(info_panel, 1, wxEXPAND);

  //Initiate the login and overview panels
  panel_login = new Login(this, 300, 400, 200, 300);
  panel_overview = new Overview(this, 50, 50, 1000, 800);
  panel_overview->Hide();

  //Arrangement of panels and bars onscreen.
  wxBoxSizer *panels = new wxBoxSizer(wxVERTICAL);
  panels->Add(program_title, 0, wxEXPAND | wxALIGN_LEFT);
  panels->Add(panel_login, 1, wxEXPAND);
  panels->Add(panel_overview, 1, wxEXPAND);
  panels->Add(group_info, 0, wxEXPAND);
  SetSizer(panels);
}//Frame

void Frame::OnExit(wxCommandEvent& event){
  delete server_com;
  Close(true);
}//OnExit

void Frame::OnSubmit(wxCommandEvent& event){
  if(failed_login_txt->IsShown())   //If there was a previous failed login attempt
    failed_login_txt->Show(false);  //remove the error message
  wxString msg = "Checking login info...";
  SetStatusText(msg);

  std::string resp;
  bool loggedin = server_com->checkLogin(panel_login->getUsername().c_str(),
                                        panel_login->getPassword().c_str(),
                                        resp);

  if (loggedin) {
    SetStatusText(wxString(resp));
    SwitchPanels();
  } else{
    wxString fail_txt = "Login failed: ";
    fail_txt += resp;
    SetStatusText("");
    failed_login_txt->SetLabel(fail_txt);
    failed_login_txt->Show(true);
  }
}//OnSubmit

void Frame::OnLogout(wxCommandEvent& event){
  SwitchPanels();
}//OnLogout

void Frame::OnNewCourse(wxCommandEvent& event){
  CourseCreator cc(this, panel_overview->getCourses());
  while (cc.ShowModal() == wxID_OK){
    std::vector<wxString> data = cc.getData();
    //SetStatusText(wxString("name: |") << data[0] << wxString("| ects: |") << data[1] <<
    //              wxString("| aff: |") << data[2] << wxString("| type: |") << data[3] <<
    //              wxString("| line: |") << data[4] << wxString("| number: |") << data[5]);
    int ret = panel_overview->addNewCourse(data);
    if(ret >= 0){
      SetStatusText(wxString("Succesfully added new course") << ret);
      return;
    }
    else if(ret == -1){
      cc.DisplayError(ERROR_COURSE_ALREADY_EXISTS);
    }
  }
  SetStatusText("");
}//OnNewCourse

void Frame::OnNewCurriculum(wxCommandEvent& event){
  CurriculumCreator cc(this);
  while(cc.ShowModal() == wxID_OK){
    std::vector<wxString> data = cc.getData();
    int ret = panel_overview->addNewCurriculum(data);
    if(ret >= 0){
      SetStatusText("Succesfully added new study program");
      return;
    }
    else if(ret == -1){
      cc.DisplayError(ERROR_CURRICULUM_ALREADY_EXISTS);
    }
  }
  SetStatusText("");
}

void Frame::OnNewYear(wxCommandEvent& event){
  panel_overview->addNewYear(this);
}

void Frame::OnDeleteYear(wxCommandEvent& event){
  panel_overview->OnDeleteYear(this);
}

void Frame::OnDeleteCurriculum(wxCommandEvent& event){
  panel_overview->OnDeleteCurriculum(this);
}

void Frame::OnDeleteAll(wxCommandEvent& event){
  panel_overview->OnDeleteAll();
}

void Frame::SwitchPanels(){
  if(panel_login->IsShown()){ //Switch from login to overview
    SetSize(1400,850);
    panel_login->Hide();
    panel_overview->Show();
    SetMenuBar(menubar_overview);
  } else {  //Switch from overview back to login
    SetSize(700,500);
    panel_overview->Hide();
    panel_login->Show();
    SetMenuBar(menubar_login);
  }
  Layout();
}//SwithPanels
