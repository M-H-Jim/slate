#pragma once

#include <wx/wx.h>
#include <wx/aboutdlg.h>
#include <wx/notebook.h>
#include <wx/splitter.h>

#include "ui/linktree.h"
#include "ui/pdf.h"
#include  "db/database.h"




class MainFrame : public wxFrame {


	LinkTree* linkTree;
	PDF *pdf;


	Database* database;


	wxPanel *panel;
	wxSizer *panelSizer;
	wxSizer *topSizer;

	wxNotebook *notebook;
	
	void OnAbout(wxCommandEvent& evt);
	void OnClose(wxCloseEvent& evt);


	public:
		MainFrame(const wxString& title);
};
