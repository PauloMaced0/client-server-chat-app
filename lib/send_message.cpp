#include "send_message.h"
#include "wx/button.h"
#include "wx/textctrl.h"

sendMessage::sendMessage(wxWindow* parent)
    : wxBoxSizer(wxHORIZONTAL) 
{
    wxTextCtrl* m_txtInput = new wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxPoint(10, 220), wxSize(250, 30));
    wxButton* m_btnSend = new wxButton(parent, wxID_ANY, wxT("Send"), wxDefaultPosition, wxSize(50, 30));

    this->Add(m_txtInput, 1, wxEXPAND | wxALL, 5);
    this->Add(m_btnSend, 0, wxALL, 5);
}
