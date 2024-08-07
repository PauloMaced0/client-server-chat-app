#include "left_panel.h"
#include "contacts.h"
#include "search.h"
#include <wx/statbmp.h>
#include <wx/stattext.h>
#include <wx/srchctrl.h>

#include "user.xpm"
#include "wx/sizer.h"

LeftPanel::LeftPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
{
    this->SetBackgroundColour(wxColor(36, 36, 38));

    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
    // wxStaticBitmap* create_new_message = new wxStaticBitmap(leftPanel, wxID_ANY, wxBitmap(edit), wxDefaultPosition, wxSize(20, 20));

    searchBox* srchBox = new searchBox(this);

    searchSizer->Add(srchBox, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
    // searchSizer->Add(create_new_message, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 8);

    leftSizer->Add(searchSizer, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);

    contactsStack* contactsList = new contactsStack(this);

    // Example
    //
    wxBitmap profileImg(user);
    wxString name = "John Doe";
    wxDateTime lastMsgDate = wxDateTime::Now();
    wxString lastMessage = "Hey yo WTF ? abcdefghijklmnopksvuxwyz";

    contactsList->AddContactCard(profileImg, name, lastMsgDate, lastMessage);

    // !Example

    leftSizer->Add(contactsList, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);

    this->SetSizerAndFit(leftSizer);
}
