#include "mainframe.h"
#include "ui/linktree.h"
#include "ui/pdf.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {


	panel = new wxPanel(this, wxID_ANY);
	notebook = new wxNotebook(panel, wxID_ANY);

	LinkTree *linkTree = new LinkTree(notebook);
	notebook->AddPage(linkTree->GetPanel(), "Links");

	PDF *pdf = new PDF(notebook);
	notebook->AddPage(pdf->GetPanel(), "PDF Viewer");


	panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(250, 100);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);

}