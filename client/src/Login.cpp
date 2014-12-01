/*
  SE 2014
  Group 8
*/

#include "Login.h"

//A summary of all events of the class Login that need to be captured
//and the function call they should trigger.
wxBEGIN_EVENT_TABLE(Login, wxPanel)
  EVT_TEXT_ENTER  (wxID_ANY, Login::OnTextEnter)
wxEND_EVENT_TABLE()

Login::Login(wxFrame *frame, int x, int y, int w, int h)
      :wxPanel(frame, wxID_ANY, wxPoint(x,y), wxSize(w, h))
{
  //Create the text input boxes
  username = new wxTextCtrl(this, ID_USERNAME, wxT(""), wxPoint(150, 100), wxSize(200,25),
                            wxTE_PROCESS_ENTER);
  username->SetHint("username");
  username->SetFocus();
  password = new wxTextCtrl(this, ID_PASSWORD, wxT(""), wxPoint(150, 200), wxSize(200,25),
                            wxTE_PASSWORD | wxTE_PROCESS_ENTER);
  password->SetHint("password");

  wxStaticText *usertext = new wxStaticText(this, -1, "Username:");
  wxStaticText *passtext = new wxStaticText(this, -1, "Password:");
  wxFont font = usertext->GetFont();
  font.SetWeight(wxFONTWEIGHT_BOLD);
  usertext->SetFont(font);
  passtext->SetFont(font);

  wxButton *submit = new wxButton(this, ID_SUBMIT, wxT("Login"));

  //Positioning the gui elements
  wxBoxSizer *row1 = new wxBoxSizer(wxHORIZONTAL);
  row1->Add(usertext, 0, wxALL, 5);
  row1->Add(username, 0, wxALL, 0);

  wxBoxSizer *row2 = new wxBoxSizer(wxHORIZONTAL);
  row2->Add(passtext, 0, wxALL, 5);
  row2->Add(password, 0, wxALL, 0);

  wxBoxSizer *column = new wxBoxSizer(wxVERTICAL);
  column->AddStretchSpacer(1);
  column->Add(row1, 0, wxALL | wxALIGN_CENTER, 20);
  column->Add(row2, 0, wxALL | wxALIGN_CENTER, 10);
  column->Add(submit, 0, wxALL | wxALIGN_CENTER, 10);
  column->AddStretchSpacer(1);

  SetSizer(column);
}

Login::~Login(){
  
}

wxString Login::getUsername(){
  return username->GetLineText(0);
}

wxString Login::getPassword(){
  return password->GetLineText(0);
}

void Login::OnTextEnter(wxCommandEvent& event){
  if(ID_USERNAME == event.GetId()) //The enter was typed while in username input box
    password->SetFocus();
  else{ //The enter was typed while in password input box
    wxCommandEvent event(wxEVT_BUTTON, ID_SUBMIT);
    wxPostEvent(this, event); //Fire a submit event
  }
}