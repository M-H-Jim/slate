#include "mainframe.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

	wxIcon appIcon;
	appIcon.LoadFile("slate.png", wxBITMAP_TYPE_PNG);
	SetIcon(appIcon);


	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuHelp, "&Help");
	

	SetMenuBar(menuBar);
	CreateStatusBar();
	SetStatusText("Welcome to Slate");



	panel = new wxPanel(this, wxID_ANY);
	notebook = new wxNotebook(panel, wxID_ANY);

	linkTree = new LinkTree(notebook);
	notebook->AddPage(linkTree->GetPanel(), "Links");


	pdf = new PDF(notebook);
	notebook->AddPage(pdf->GetPanel(), "PDF Viewer");



	panelSizer = new wxBoxSizer(wxHORIZONTAL);
	panelSizer->Add(notebook, 1, wxEXPAND);
	panel->SetSizer(panelSizer);

	topSizer = new wxBoxSizer(wxHORIZONTAL);
	topSizer->SetMinSize(250, 100);
	topSizer->Add(panel, 1, wxEXPAND);
	SetSizerAndFit(topSizer);



	database = new Database();
	if (!database->Open()) {
		wxMessageBox("Failed to open database", "Error", wxICON_ERROR | wxOK);
	}
	database->LoadLinksTree(linkTree->GetTree(), linkTree->GetTreeCtrl()->GetHiddenRoot());
	database->LoadPdfTree(pdf->GetTree(), pdf->GetTreeCtrl()->GetHiddenRoot());








	Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);





}

void MainFrame::OnAbout(wxCommandEvent& evt) {


	wxAboutDialogInfo aboutInfo;

	aboutInfo.SetName("Slate");
	aboutInfo.AddDeveloper("M.H.Jim");
	aboutInfo.SetCopyright("© 2026 M.H.Jim. All rights reserved.");
	aboutInfo.SetDescription("Just another software\n\nBuilt with the following technologies:\n"
		"- wxWidgets (v3.3.1)\n"
		"- wxPDFViewer\n"
		"- SQLite3\n"
		"- Visual Studio (MSVC)\n"
		"- Internet Explorer (for webview backend)\n\n"
		"This project is open-source under the GNU General Public License.");
	aboutInfo.SetLicence(
		"GNU GENERAL PUBLIC LICENSE\n"
		"Version 2, June 1991\n\n"
		"Copyright (C) 1989, 1991 Free Software Foundation, Inc.\n"
		"This program is free software; you can redistribute it and/or\n"
		"modify it under the terms of the GNU General Public License as\n"
		"published by the Free Software Foundation; either version 2\n"
		"of the License, or (at your option) any later version.\n\n"
		"This program is distributed in the hope that it will be useful,\n"
		"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
		"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
		"GNU General Public License for more details.\n\n"
		"You should have received a copy of the GNU General Public License\n"
		"along with this program; if not, write to the Free Software\n"
		"Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA."
	);

	aboutInfo.SetWebSite("www.github.com/M-H-Jim/Slate", "GitHub Repository");

	aboutInfo.SetVersion("0.0.1");
	wxAboutBox(aboutInfo);

}

void MainFrame::OnClose(wxCloseEvent& evt) {
	if (linkTree) {
		database->SaveLinksTree(linkTree->GetTree(), linkTree->GetTreeCtrl()->GetHiddenRoot());
	}
	if(pdf) {
		database->SavePdfTree(pdf->GetTree(), pdf->GetTreeCtrl()->GetHiddenRoot());
	}
	evt.Skip();
}
