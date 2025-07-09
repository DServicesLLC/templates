#pragma once

#include <wx/wx.h>
#include <wx/frame.h>

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent, wxWindowID id, const wxString& title);
    ~MainFrame() = default;

private:
    // Event handlers
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    // UI creation
    void CreateMenuBar();
    void CreateStatusBar();

    // Menu IDs
    enum
    {
        ID_EXIT = wxID_HIGHEST + 1,
        ID_ABOUT
    };

    DECLARE_EVENT_TABLE()
};
