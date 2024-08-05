#include "main_frame.h"
#include "wx/chartype.h"
#include "wx/colour.h"
#include "wx/gdicmn.h"
#include "wx/osx/bitmap.h"
#include "wx/osx/statbmp.h"
#include "wx/richtext/richtextctrl.h"
#include <wx/srchctrl.h>
#include "wx/splitter.h"
#include "wx/osx/button.h"
#include "wx/osx/textctrl.h"
#include "wx/string.h"
#include "wx/stringimpl.h"
#include <wx/wx.h>

#include "info.xpm"
#include "video.xpm"

MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    SetMinSize(wxSize(660, 320));

    wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    wxPanel* panel_left = new wxPanel(splitter, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
    wxPanel* panel_right = new wxPanel(splitter, wxID_ANY, wxDefaultPosition, wxSize(400, 200));

    panel_left->SetBackgroundColour(wxColor(36, 36, 38));
    panel_right->SetMinSize(wxSize(350, 200));

    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* searchSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* m_btn_create_new_contact = new wxButton(panel_left, wxID_ANY, wxT("New contact"), wxDefaultPosition, wxSize(100, 30));

    wxSearchCtrl* search = new wxSearchCtrl(panel_left, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(250, 30));
    search->ShowCancelButton(true);
    search->ShowSearchButton(true);

    searchSizer->Add(search, 1, wxEXPAND | wxALL, 5);
    searchSizer->Add(m_btn_create_new_contact, 0, wxALL, 5);

    leftSizer->Add(searchSizer, 0, wxEXPAND | wxTOP | wxBOTTOM, 5);

    panel_left->SetSizerAndFit(leftSizer);

    splitter->SetMinimumPaneSize(250);
    splitter->SetSashGravity(0);
    splitter->SetBackgroundColour(wxColor(0, 0, 0));
    splitter->SplitVertically(panel_left, panel_right, 300);

    wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);

    wxPanel* panel_right_top = new wxPanel(panel_right, wxID_ANY, wxDefaultPosition, wxSize(-1, 50));
    panel_right_top->SetBackgroundColour(wxColor(54, 54, 56));

    wxBoxSizer* nameIconSizer = new wxBoxSizer(wxHORIZONTAL);

    wxTextCtrl* receiverName = new wxTextCtrl(panel_right_top, wxID_ANY, wxT("To: John Doe"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxBORDER_NONE);
    receiverName->SetBackgroundColour(wxColor(40, 40, 42));
    receiverName->SetForegroundColour(wxColor(255, 255, 255));
    receiverName->SetFont(wxFont(wxFontInfo(15).Light()));
    nameIconSizer->Add(receiverName, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

    nameIconSizer->AddStretchSpacer(1);

    panel_right_top->SetSizer(nameIconSizer);

    wxStaticBitmap* videoCallIconCtrl = new wxStaticBitmap(panel_right_top, wxID_ANY, wxBitmap(video), wxDefaultPosition, wxSize(22, 22));
    wxStaticBitmap* infoIconCtrl = new wxStaticBitmap(panel_right_top, wxID_ANY, wxBitmap(info), wxDefaultPosition, wxSize(19, 19));

    nameIconSizer->Add(videoCallIconCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
    nameIconSizer->Add(infoIconCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 15);

    wxPanel* panel_right_bot = new wxPanel(panel_right, wxID_ANY);
    panel_right_bot->SetBackgroundColour(wxColor(38, 38, 40));

    rightSizer->Add(panel_right_top, 0, wxEXPAND | wxBOTTOM, 1);

    rightSizer->Add(panel_right_bot, 1, wxEXPAND, 0);

    wxBoxSizer* message_sizer = new wxBoxSizer(wxVERTICAL);
    
    panel_right_bot->SetSizer(message_sizer);

    wxRichTextCtrl* m_txtDisplay = new wxRichTextCtrl(panel_right_bot, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(370, 200), wxTE_MULTILINE | wxTE_READONLY | wxBORDER_NONE);
    m_txtDisplay->SetBackgroundColour(wxColor(38, 38, 40));

    wxBoxSizer* message_box_sizer = new wxBoxSizer(wxVERTICAL);
    m_txtDisplay->SetSizer(message_box_sizer);

/* */

    // Simulate user 1 sending a message (left-aligned)
    wxRichTextAttr leftAlign;
    leftAlign.SetAlignment(wxTEXT_ALIGNMENT_LEFT);
    m_txtDisplay->BeginStyle(leftAlign);
    m_txtDisplay->WriteText("Hello, how are you?\n");
    m_txtDisplay->EndStyle();

    // Simulate user 2 responding (right-aligned)
    wxRichTextAttr rightAlign;
    rightAlign.SetAlignment(wxTEXT_ALIGNMENT_RIGHT);
    m_txtDisplay->BeginStyle(rightAlign);
    m_txtDisplay->WriteText("I'm good, thanks! How about you ewfewkfwekj kjwe jkewjkkjew jkewj ew jkjkefwjkef wjk ewjke wjk?\n");
    m_txtDisplay->EndStyle();

/* */

    wxTextCtrl* m_txtInput = new wxTextCtrl(panel_right_bot, wxID_ANY, wxEmptyString, wxPoint(10, 220), wxSize(250, 30));
    wxButton* m_btnSend = new wxButton(panel_right_bot, wxID_ANY, wxT("Send"), wxPoint(270, 220), wxSize(50, 30));

    message_sizer->Add(m_txtDisplay, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);
    inputSizer->Add(m_txtInput, 1, wxEXPAND | wxALL, 5);
    inputSizer->Add(m_btnSend, 0, wxALL, 5);

    message_sizer->Add(inputSizer, 0, wxEXPAND);

    panel_right_bot->SetSizer(message_sizer);

    panel_right->SetSizer(rightSizer);
}
