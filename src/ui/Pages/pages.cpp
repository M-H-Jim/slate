#include "pages.h"


Pages::Pages(wxNotebook* notebook) {
    pagesPanel = new wxPanel(notebook, wxID_ANY);
    splitterWindow = new wxSplitterWindow(pagesPanel, wxID_ANY);
    splitterWindow->SetMinimumPaneSize(250);
    
    // Create the left panel and all it's features ------------------------------
    
    splitPanel1 = new wxPanel(splitterWindow, wxID_ANY);
    
    
    
    splitPanel1Sizer = new wxBoxSizer(wxVERTICAL);
    splitPanel1->SetSizer(splitPanel1Sizer);
    
    
    
    
    
    // Create the right panel and all it's features ----------------------
    
    splitPanel2 = new wxPanel(splitterWindow, wxID_ANY);
    
    
    
    splitPanel1Sizer = new wxBoxSizer(wxVERTICAL);
    splitPanel2->SetSizer(splitPanel2Sizer);
    
    
    
    
    splitterWindow->SplitVertically(splitPanel1, splitPanel2);
    
    pagesSizer = new wxBoxSizer(wxHORIZONTAL);
    pagesSizer->Add(splitterWindow, 1, wxEXPAND);
    pagesPanel->SetSizer(pagesSizer);
    
    
    
}




wxPanel* Pages::GetPanel() {
    return pagesPanel;
}
