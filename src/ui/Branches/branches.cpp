#include "branches.h"


Branches::Branches(wxNotebook* notebook) {
    
    branchesPanel = new wxPanel(notebook, wxID_ANY);
    splitterWindow = new wxSplitterWindow(branchesPanel, wxID_ANY);
    splitterWindow->SetMinimumPaneSize(250);
    
    
    // Create the left panel and all it's features ---------------------
    
    splitPanel1 = new wxPanel(splitterWindow, wxID_ANY);
    
    
    // Search bar to search links in the branches
    
    searchCtrl = new wxSearchCtrl(
        splitPanel1,
        wxID_ANY,
        "",
        wxDefaultPosition,
        wxDefaultSize,
        wxTE_PROCESS_ENTER
    );
    
    searchCtrl->ShowSearchButton(true);
    searchCtrl->ShowCancelButton(true);
    
    
    // Tool bar for the branches
    branchesToolBar = new wxToolBar(
        splitPanel1,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxTB_VERTICAL | wxTB_FLAT
    );

    
    branchesToolBar->AddTool(wxID_ANY, "Add Link", wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR));
    branchesToolBar->AddTool(wxID_ANY, "Rename", wxArtProvider::GetBitmap(wxART_EDIT, wxART_TOOLBAR));
    branchesToolBar->AddTool(wxID_ANY, "Delete", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR));
    
    
    
    
    branchesToolBar->Realize();
    
    
    
    
    
    
    
    
    wxTreeCtrl *treeCtrl = new wxTreeCtrl(splitPanel1, wxID_ANY, wxDefaultPosition, wxSize(250, 200));
    wxTreeItemId rootId = treeCtrl->AddRoot("Root");
    treeCtrl->AppendItem(rootId, "Node 1");
    wxTreeItemId child2Id = treeCtrl->AppendItem(rootId, "Node 2");
    treeCtrl->AppendItem(child2Id, "Child of node 2");
    treeCtrl->AppendItem(rootId, "Node 3");
    
    treeCtrl->ExpandAll();
    
    tool_branchesSizer = new wxBoxSizer(wxHORIZONTAL);
    tool_branchesSizer->Add(branchesToolBar, 0, wxEXPAND);
    tool_branchesSizer->Add(treeCtrl, 1, wxEXPAND, 5);
    
    
    
    
    
    
    splitPanel1Sizer = new wxBoxSizer(wxVERTICAL);
    splitPanel1Sizer->Add(searchCtrl, 0, wxEXPAND, 5);
    splitPanel1Sizer->Add(tool_branchesSizer, 1, wxEXPAND, 5);
    splitPanel1->SetSizer(splitPanel1Sizer);
    
    
    
    
    
    // Create the right panel and all it's features -----------------------------------
    
    splitPanel2 = new wxPanel(splitterWindow, wxID_ANY);
    
    
    // Toolbar for the webView
    browserToolBar = new wxToolBar(
        splitPanel2,
        wxID_ANY,
        wxDefaultPosition,
        wxDefaultSize,
        wxTB_HORIZONTAL | wxTB_FLAT
    );
    
    browserToolBar->AddTool(wxID_ANY, "Back", wxArtProvider::GetBitmap(wxART_GO_BACK, wxART_TOOLBAR));
    browserToolBar->AddTool(wxID_ANY, "Forward", wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR));
    browserToolBar->AddTool(wxID_ANY, "Refresh", wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR));
    
    browserToolBar->AddSeparator();
    browserToolBar->AddTool(wxID_ANY, "Open in Browser", wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR));
    
    browserToolBar->Realize();
    
    
    
    
    
    
    webView = wxWebView::New(splitPanel2, wxID_ANY, "https://www.duckduckgo.com/");
     
    splitPanel2Sizer = new wxBoxSizer(wxVERTICAL);
    splitPanel2Sizer->Add(browserToolBar, 0, wxEXPAND);
    splitPanel2Sizer->Add(webView, 1, wxEXPAND);
    splitPanel2->SetSizer(splitPanel2Sizer);
    
    

    
    
    
    
    
    
    
    splitterWindow->SplitVertically(splitPanel1, splitPanel2);
    
    branchesSizer = new wxBoxSizer(wxHORIZONTAL);
    branchesSizer->Add(splitterWindow, 1, wxEXPAND);
    branchesPanel->SetSizer(branchesSizer);
    
}

wxPanel* Branches::GetPanel() {
    return branchesPanel;
}







