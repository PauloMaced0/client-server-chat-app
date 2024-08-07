#include "right_panel.h"
#include "user_header.h"
#include "text_display.h"
#include "send_message.h"

#include "edit.xpm"

RightPanel::RightPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
    this->SetBackgroundColour(wxColor(38, 38, 40));

    this->SetMinSize(wxSize(350, 200));

    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    userHeader* user_header = new userHeader(this);

    wxPanel* in_out_message = new wxPanel(this);
    in_out_message->SetBackgroundColour(wxColor(38, 38, 40));

    rightSizer->Add(user_header, 0, wxEXPAND | wxBOTTOM, 1);

    rightSizer->Add(in_out_message, 1, wxEXPAND, 0);

    wxBoxSizer* message_sizer = new wxBoxSizer(wxVERTICAL);
    
    in_out_message->SetSizer(message_sizer);

    textDisplay* m_txtDisplay = new textDisplay(in_out_message);

    sendMessage* send_msg = new sendMessage(in_out_message); 

    message_sizer->Add(m_txtDisplay, 1, wxEXPAND | wxALL, 5);

    message_sizer->Add(send_msg, 0, wxEXPAND);

    in_out_message->SetSizer(message_sizer);

    this->SetSizer(rightSizer);
}
