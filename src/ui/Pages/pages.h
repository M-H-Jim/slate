#ifndef PAGES_H
#define PAGES_H

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/sizer.h>

/* This Notes/Summary/Personal knowledge Base in my application is called Pages. */

class Pages {
        wxPanel *pagesPanel;
        wxSplitterWindow *splitterWindow;
        
        wxPanel *splitPanel1;
        wxPanel *splitPanel2;
        
        wxBoxSizer *splitPanel1Sizer;
        wxBoxSizer *splitPanel2Sizer;
        wxBoxSizer *pagesSizer;
    
    public:
        Pages(wxNotebook *notebook);
        wxPanel* GetPanel();
    
    
};






#endif // PAGES_H
