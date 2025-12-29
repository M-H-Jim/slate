#ifndef MENUBAR_H
#define MENUBAR_H

#include <wx/wx.h>

enum {
    ID_CALENDAR = wxID_HIGHEST + 1
};







class MenuBar {
    
        wxMenuBar *menuBar;

        wxMenu *menuFile;
        wxMenu *menuSettings;
        wxMenu *menuMore;
        wxMenu *menuAbout;
        
        
        
    public:
        MenuBar();
        wxMenuBar *Get();
        
        
        
        
        
        
        
        
        
        
        
        
};


#endif // MENUBAR_H
