#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>

#include <wx/notebook.h>
#include <wx/calctrl.h>




class MainFrame : public wxFrame {
    
    // Panel, sizer, notebook
    
    wxPanel *panel;
    wxSizer *panelSizer;
    wxSizer *topSizer;
    
    
    wxNotebook *notebook;
    
    
    
    
    
    
    
    void OnCalendar(wxCommandEvent& event);
    
    
    
    
    
    
    public:
        MainFrame(const wxString& title);
};






#endif // MAINFRAME_H
