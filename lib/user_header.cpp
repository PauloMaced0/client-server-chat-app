#include "user_header.h"
#include "wx/statbmp.h"
#include "wx/textctrl.h"
#include <wx/sizer.h>

#include "info.xpm"
#include "video.xpm"

userHeader::userHeader(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(-1, 50)) 
{
    this->SetBackgroundColour(wxColor(54, 54, 56));

    wxBoxSizer* nameIconSizer = new wxBoxSizer(wxHORIZONTAL);

    wxTextCtrl* receiverName = new wxTextCtrl(this, wxID_ANY, wxT("To: John Doe"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxBORDER_NONE);
    receiverName->SetBackgroundColour(wxColor(40, 40, 42));
    receiverName->SetForegroundColour(wxColor(255, 255, 255));
    receiverName->SetFont(wxFont(wxFontInfo(14).Light()));
    nameIconSizer->Add(receiverName, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);

    nameIconSizer->AddStretchSpacer(1);

    this->SetSizer(nameIconSizer);

    wxStaticBitmap* videoCallIconCtrl = new wxStaticBitmap(this, wxID_ANY, wxBitmap(video), wxDefaultPosition, wxSize(20, 20));
    wxStaticBitmap* infoIconCtrl = new wxStaticBitmap(this, wxID_ANY, wxBitmap(info), wxDefaultPosition, wxSize(17, 17));

    nameIconSizer->Add(videoCallIconCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 20);
    nameIconSizer->Add(infoIconCtrl, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 15);
}
