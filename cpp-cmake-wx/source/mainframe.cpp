#include "mainframe.h"
#include <wx/msgdlg.h>
#include <wx/aboutdlg.h>

// Event table
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_EXIT, MainFrame::OnExit)
    EVT_MENU(ID_ABOUT, MainFrame::OnAbout)
    EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxFrame(parent, id, title, wxDefaultPosition, wxSize(800, 600))
{
    CreateMenuBar();
    CreateStatusBar();
    
    Centre();
    SetStatusText("Ready");
}

void MainFrame::CreateMenuBar()
{
    wxMenuBar* menuBar = new wxMenuBar;
    
    // File menu
    wxMenu* fileMenu = new wxMenu;
    fileMenu->Append(ID_EXIT, "E&xit\tCtrl+Q", "Exit the application");
    
    // Help menu
    wxMenu* helpMenu = new wxMenu;
    helpMenu->Append(ID_ABOUT, "&About\tF1", "Show about dialog");
    
    // Add menus to menu bar
    menuBar->Append(fileMenu, "&File");
    menuBar->Append(helpMenu, "&Help");
    
    SetMenuBar(menuBar);
}

void MainFrame::CreateStatusBar()
{
    wxFrame::CreateStatusBar();
}

void MainFrame::OnExit(wxCommandEvent& WXUNUSED(event))
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxAboutDialogInfo info;
    info.SetName("wxWidgets Application");
    info.SetVersion("1.0.0");
    info.SetDescription("A wxWidgets application template");
    info.SetCopyright("(C) 2025");
    
    wxAboutBox(info, this);
}

void MainFrame::OnClose(wxCloseEvent& event)
{
    Destroy();
}
