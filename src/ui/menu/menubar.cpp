#include "menubar.h"






MenuBar::MenuBar() {
    menuBar = new wxMenuBar;
    menuFile = new wxMenu;
    menuSettings = new wxMenu;
    menuMore = new wxMenu;
    menuAbout = new wxMenu;
    
    
    
    menuMore->Append(ID_CALENDAR, "Calendar");
    
    
    
    
    
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuSettings, "&Settings");
    menuBar->Append(menuMore, "&More");
    menuBar->Append(menuAbout, "&About");
    
    
    
}

wxMenuBar *MenuBar::Get() {
    return menuBar;
}
