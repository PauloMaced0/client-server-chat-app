#include "left_panel.h"
#include "right_panel.h"
#include "main_frame.h"
#include "wx/colour.h"
#include "wx/splitter.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title)
{
    this->SetMinSize(wxSize(660, 320));

    wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_BORDER | wxSP_LIVE_UPDATE);

    LeftPanel* leftPanel = new LeftPanel(splitter);
    RightPanel* rightPanel = new RightPanel(splitter);

    splitter->SetMinimumPaneSize(250);
    splitter->SetSashGravity(0);
    splitter->SetBackgroundColour(wxColor(0, 0, 0));
    splitter->SplitVertically(leftPanel, rightPanel, 300);
}
