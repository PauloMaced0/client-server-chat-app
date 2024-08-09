#include "main_frame.h"
#include "protocol.h"
#include "wx/event.h"
#include "app.h"
#include <cstdint>
#include <wx/wx.h>

wxBEGIN_EVENT_TABLE(App, wxApp)
    EVT_SOCKET(SOCKET_ID,   App::OnSocketEvent)
wxEND_EVENT_TABLE();

wxIMPLEMENT_APP(App);

bool App::OnInit() 
{
    if (!wxApp::OnInit())
        return false;

    this->OpenTCPConnection();

    MainFrame* mainFrame = new MainFrame("ChatUP!");
    mainFrame->SetClientSize(900, 600);
    mainFrame->Center();
    mainFrame->Show();

    // Testing !!!!!
    // std::cout << this->tcp_socket->IsConnected() << std::endl;

    RegisterMessage* msg = new RegisterMessage("John Doe");
    Proto::send_msg(this->tcp_socket->GetSocket(), *msg);

    delete msg;
    // Testing !!!!!

    return true;
}
 
void App::OpenTCPConnection()
{
    this->tcp_socket = new wxSocketClient();

    this->tcp_socket->SetEventHandler(*this, SOCKET_ID);
    this->tcp_socket->SetNotify(wxSOCKET_CONNECTION_FLAG |
                    wxSOCKET_INPUT_FLAG |
                    wxSOCKET_LOST_FLAG);
    this->tcp_socket->Notify(true);

    wxIPV4address addr;
    addr.Hostname("localhost");
    addr.Service(5001);

    this->tcp_socket->Connect(addr);
    this->tcp_socket->WaitOnConnect(5);
}

int App::OnExit()
{

    if (this->tcp_socket)
    {
        this->tcp_socket->Close();
        delete this->tcp_socket;
        this->tcp_socket = nullptr;
    }

    return wxApp::OnExit();
}

void App::OnSocketEvent(wxSocketEvent& event)
{
    switch ( event.GetSocketEvent() )
    {
        case wxSOCKET_INPUT:
            wxLogMessage("Input available on the socket");
            break;

        case wxSOCKET_LOST:
            wxLogMessage("Socket connection was unexpectedly lost.");
            break;

        case wxSOCKET_CONNECTION:
            wxLogMessage("... socket is now connected.");
            break;

        default:
            wxLogMessage("Unknown socket event!!!");
            break;
    }
}
