#ifndef _APP_H_
#define _APP_H_

#include "wx/event.h"
#include "wx/socket.h"
#include <wx/wx.h>

class App : public wxApp
{
public:
    bool OnInit() override;
    int OnExit() override;

private:
    wxSocketClient* tcp_socket;
    void OpenTCPConnection();
    void OnSocketEvent(wxSocketEvent& event);

    wxDECLARE_EVENT_TABLE();
};

enum {
    SOCKET_ID = 100
};

#endif // !_APP_H_
