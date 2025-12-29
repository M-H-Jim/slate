#include "../../mainframe.h"

#include <wx/artprov.h>

void MainFrame::OnCalendar(wxCommandEvent& event) {
    
    
    wxDialog* calDialog = new wxDialog(
        this,
        wxID_ANY,
        "Calendar",
        wxDefaultPosition,
        wxDefaultSize,
        wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER
    );

    calDialog->SetIcon(wxArtProvider::GetIcon(wxART_WX_LOGO));
    calDialog->SetBackgroundColour(*wxBLACK);

    wxCalendarCtrl* calendar = new wxCalendarCtrl(
        calDialog,
        wxID_ANY,
        wxDefaultDateTime,
        wxDefaultPosition,
        wxDefaultSize,
        wxCAL_SHOW_HOLIDAYS
    );


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(calendar, 1, wxEXPAND | wxALL, 10);

    calDialog->SetSizerAndFit(sizer);
    calDialog->CenterOnParent();

    calDialog->ShowModal();
    calDialog->Destroy();
    
}



