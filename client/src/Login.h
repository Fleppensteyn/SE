/*
  SE 2014
  Group 8
*/

#ifndef LOGIN_H_
#define LOGIN_H_

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
  #include "wx/wx.h"
#endif

enum{
  ID_USERNAME,
  ID_PASSWORD,
  ID_SUBMIT
};

//Contains all gui elements and functionality of the login screen
class Login : public wxPanel
{
public:
  //Sets up the login screen
  // frame - The parent frame
  // x - The x position of the top left corner of the panel
  // y - The y position of the top left corner of the panel
  // w - The width of the panel
  // h - The height of the panel
  Login(wxFrame *frame, int x, int y, int w, int h);
  virtual ~Login();

  //Sends the login event through to the parent frame
  // event - The event triggered by clicking the 'Login' button
  void OnSubmit(wxCommandEvent& event);

  //Handles the events of enter being pressed, either focus on next element or submit
  // event - The event associated with pressing enter
  void OnTextEnter(wxCommandEvent& event);

  //Get the username from the username input box
  //Returns a string of the text in the username input box
  wxString getUsername();

  //Get the password from the password input box
  //Returns a string of the text in the password input box 
  wxString getPassword();

  wxTextCtrl *username; //The username input box
  wxTextCtrl *password; //The password input box

private:
  wxDECLARE_EVENT_TABLE();
};

#endif /* LOGIN_H_ */

