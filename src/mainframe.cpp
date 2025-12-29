#include "mainframe.h"
#include "../src/ui/menu/menubar.h"
#include "../src/ui/branches/branches.h"


#include <wx/splitter.h>



MainFrame::MainFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title) {
    
    MenuBar menu;
    SetMenuBar(menu.Get());
    
    Bind(wxEVT_MENU, &MainFrame::OnCalendar, this, ID_CALENDAR);
    
    
    
    
    
    panel = new wxPanel(this, wxID_ANY);
    notebook = new wxNotebook(panel, wxID_ANY);
    ////////////////////////////////////////////////////
    
    Branches branches(notebook);
    notebook->AddPage(branches.GetPanel(), "Branches");
    
    
    
    
    
    
    
    
    
    
//    notebook->AddPage(text1, "Tab 1");
    
    
    
    
    
    
    
    
    wxTextCtrl *text2 = new wxTextCtrl(notebook, wxID_ANY, "Tab 2 contents");
    notebook->AddPage(text2, "Tab 2");
    wxTextCtrl *text3 = new wxTextCtrl(notebook, wxID_ANY, "Tab 3 contents");
    notebook->AddPage(text3, "Tab 3");
    wxTextCtrl *text4 = new wxTextCtrl(notebook, wxID_ANY, "Tab 4 contents");
    notebook->AddPage(text4, "Tab 4");   
    
    
    
    
    panelSizer = new wxBoxSizer(wxHORIZONTAL);
    panelSizer->Add(notebook, 1, wxEXPAND);
    panel->SetSizer(panelSizer);
    
    
    topSizer = new wxBoxSizer(wxHORIZONTAL);
    topSizer->SetMinSize(250, 100);
    topSizer->Add(panel, 1, wxEXPAND);
    SetSizerAndFit(topSizer);
    
    
    
}




