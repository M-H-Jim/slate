#ifndef BRANCHES_H
#define BRANCHES_H


#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/webview.h>
#include <wx/treectrl.h>
#include <wx/srchctrl.h>
#include <wx/artprov.h>


/* This LinkTree feature in my application is called branches. Don't think it as something else. */


class Branches {
        wxPanel *branchesPanel;
        wxSplitterWindow *splitterWindow;
        
        wxPanel *splitPanel1;
        wxPanel *splitPanel2;
        
        wxBoxSizer *splitPanel1Sizer;
        wxBoxSizer *splitPanel2Sizer;
        wxBoxSizer *branchesSizer;
        
        
        
        // left panel
        wxSearchCtrl *searchCtrl;
        
        wxToolBar *branchesToolBar;
        
        
        
        wxBoxSizer *tool_branchesSizer;
        
        
        // right panel
        wxWebView *webView;
        
        wxToolBar *browserToolBar;
        
        
        
    public:
        Branches(wxNotebook *notebook);
        wxPanel* GetPanel();
    
};


#endif // BRANCHES_H
