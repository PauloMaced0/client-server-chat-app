#include "contacts.h"
#include "wx/statbmp.h"
#include "wx/stattext.h"
#include "wx/scrolwin.h"

#include "wx/sizer.h"

contactsStack::contactsStack(wxWindow* parent)
    : wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL)
{
    this->SetMinSize(wxSize(250, 60));
    // contactsList->SetBackgroundColour(*wxRED);
    this->SetScrollRate(5, 5);

    this->mainSizer = new wxBoxSizer(wxVERTICAL);

    this->SetSizer(this->mainSizer);
}

void contactsStack::AddContactCard(wxBitmap profileImg, wxString name, wxDateTime lastMsgDate, wxString message) 
{
    wxPanel* contactPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
    // contactPanel->SetBackgroundColour(wxColor(*wxGREEN));

    wxBoxSizer* contactSizer = new wxBoxSizer(wxHORIZONTAL);

    // Profile Image
    // wxBitmap profileBitmap(wxImage("../resources/something.png").Rescale(50, 50));
    wxStaticBitmap* profileImage = new wxStaticBitmap(contactPanel, wxID_ANY, profileImg, wxDefaultPosition, wxSize(40, 40));
    contactSizer->Add(profileImage, 0, wxTOP | wxLEFT | wxBOTTOM, 12);

    // Contact Info (Name, Last Message, Date)
    wxBoxSizer* infoSizer = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer* nameDateSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* nameText = new wxStaticText(contactPanel, wxID_ANY, name);
    // nameText->SetBackgroundColour(*wxBLACK);
    wxFont nameFont = nameText->GetFont();
    nameFont.SetWeight(wxFONTWEIGHT_BOLD);
    nameText->SetFont(nameFont);
    nameDateSizer->Add(nameText, 0, wxLEFT | wxRIGHT, 1);
    
    // Get the current date and time
    wxString dateStr = lastMsgDate.Format("%d/%m/%Y"); // e.g., "2024-08-05"
    
    wxStaticText* dateText = new wxStaticText(contactPanel, wxID_ANY, dateStr);
    // dateText->SetBackgroundColour(*wxBLACK);
    wxFont dateFont = dateText->GetFont();
    dateFont.SetPointSize(12);  // Make the date text smaller
    dateText->SetFont(dateFont);

    nameDateSizer->AddStretchSpacer(1);
    nameDateSizer->Add(dateText, 0, wxLEFT, 2);

    infoSizer->Add(nameDateSizer, 1, wxEXPAND | wxTOP, 2);

    wxStaticText* messageText = new wxStaticText(contactPanel, wxID_ANY, message);
    // messageText->SetBackgroundColour(*wxBLACK);
    messageText->Wrap(200);
    wxFont lastMessageFont = messageText->GetFont();
    lastMessageFont.SetWeight(wxFONTWEIGHT_MEDIUM);
    lastMessageFont.SetPointSize(11);
    messageText->SetFont(lastMessageFont);
    messageText->SetForegroundColour(wxColor(124, 124, 128));
    infoSizer->Add(messageText, 0, wxEXPAND | wxBOTTOM, 2);
    
    contactSizer->Add(infoSizer, 1, wxALL, 5);

    contactPanel->SetSizer(contactSizer);

    this->mainSizer->Add(contactPanel, 0, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
}
