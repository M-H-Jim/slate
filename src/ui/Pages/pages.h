#ifndef PAGES_H
#define PAGES_H

//#include "../../../bitmaps"
#include "bold.xpm"
#include "italic.xpm"
#include "underline.xpm"


#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/artprov.h>
//#include <wx/combobox.h>
#include <wx/fontpicker.h>




/* This Notes/Summary/Personal knowledge Base in my application is called Pages. */

class Pages {
        wxPanel *pagesPanel;
        wxSplitterWindow *splitterWindow;
        
        wxPanel *splitPanel1;
        wxPanel *splitPanel2;
        
        wxBoxSizer *splitPanel1Sizer;
        wxBoxSizer *splitPanel2Sizer;
        wxBoxSizer *pagesSizer;
        
        
        // left panel
        
        
        
        
        
        
        
        
        // right panel
        
        wxToolBar *richTextCtrlToolBar;
        wxFontPickerCtrl *fontPicker;
        
        
        
        
        
        wxRichTextCtrl *richTextCtrl;
        
        
        
        
    
    public:
        Pages(wxNotebook *notebook);
        wxPanel* GetPanel();
    
    
};






#endif // PAGES_H
