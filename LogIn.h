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

class Login : wxPanel
{
public:
  Login(wxFrame *frame, int x, int y, int w, int h);
  //virtual ~Login(){}

  void OnSubmit(wxCommandEvent& event);
  void OnTextEnter(wxCommandEvent& event);
  wxString getUsername();
  wxString getPassword();

  wxTextCtrl *username;
  wxTextCtrl *password;
  wxButton   *submit;

private:
  wxDECLARE_EVENT_TABLE();
};

#endif /* LOGIN_H_ */

