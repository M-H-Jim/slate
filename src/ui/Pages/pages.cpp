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
    
    
    // Writing space
    
    richTextCtrlToolBar = new wxToolBar(
        splitPanel2,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxTB_HORIZONTAL | wxTB_FLAT
    );
    
    fontPicker = new wxFontPickerCtrl(richTextCtrlToolBar, wxID_ANY,
                                      wxNullFont,
                                      wxDefaultPosition,
                                      wxSize(200, 30),
                                      wxFNTP_USEFONT_FOR_LABEL | wxFNTP_FONTDESC_AS_LABEL);
    
    
    
    
    //------------------------------------------------------------------
    richTextCtrlToolBar->AddCheckTool(wxID_BOLD, "B", wxBitmap(bold_xpm));
    richTextCtrlToolBar->AddCheckTool(wxID_ITALIC, "I", wxBitmap(italic_xpm));
    richTextCtrlToolBar->AddCheckTool(wxID_UNDERLINE, "U", wxBitmap(underline_xpm));
    richTextCtrlToolBar->AddCheckTool(wxID_STRIKETHROUGH, "S", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR));
    //------------------------------------------------------------------
    richTextCtrlToolBar->AddControl(fontPicker);
    
    
    
    richTextCtrlToolBar->Realize();
    
    
    
    
    richTextCtrl = new wxRichTextCtrl(
        splitPanel2,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_MULTILINE |wxTE_RICH2 | wxTE_PROCESS_TAB
    );
    

    
    
    
    
    
    
    
    splitPanel2Sizer = new wxBoxSizer(wxVERTICAL);
    splitPanel2Sizer->Add(richTextCtrlToolBar, 0, wxEXPAND);
    splitPanel2Sizer->Add(richTextCtrl, 1, wxEXPAND);
    splitPanel2->SetSizer(splitPanel2Sizer);
    
    
    
    
    
    
    //----------------------------------------
    
    splitterWindow->SplitVertically(splitPanel1, splitPanel2);
    
    pagesSizer = new wxBoxSizer(wxHORIZONTAL);
    pagesSizer->Add(splitterWindow, 1, wxEXPAND);
    pagesPanel->SetSizer(pagesSizer);
    
    
    
}




wxPanel* Pages::GetPanel() {
    return pagesPanel;
}
