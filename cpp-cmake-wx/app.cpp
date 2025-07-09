#include <wx/wx.h>
#include "mainframe.h"

class Application : public wxApp
{
public:
    Application() = default;
    virtual bool OnInit();
};

bool Application::OnInit()
{
    MainFrame* mainFrame = new MainFrame(nullptr, wxID_ANY, "wxWidgets Application");
    mainFrame->Show(true);
    return true;
}

// Implement the application entry point
wxIMPLEMENT_APP(Application);
