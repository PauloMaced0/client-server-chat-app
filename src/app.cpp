#include "main_frame.h"
#include "app.h"
#include <iostream>
#include <ostream>
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("ChatUP!");
    mainFrame->SetClientSize(900, 600);
    mainFrame->Center();
    mainFrame->Show();
    std::cout << "Hello World from the terminal" << std::endl;
    return true;
}
 
 
