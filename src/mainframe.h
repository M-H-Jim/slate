#pragma once

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/splitter.h>

class MainFrame : public wxFrame {

	wxPanel *panel;
	wxSizer *panelSizer;
	wxSizer *topSizer;

	wxNotebook *notebook;
	

	public:
		MainFrame(const wxString& title);
};
