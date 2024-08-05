#ifndef _MAIN_FRAME_H_
#define _MAIN_FRAME_H_

#include "wx/string.h"
#include <wx/wx.h>

 
class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString &title);

private:
    // something
    //
    void AddChatMessage(const wxString& message, bool isSender);
};

#endif // !_MAIN_FRAME_H_
