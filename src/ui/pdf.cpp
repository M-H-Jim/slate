#include "pdf.h"
#include "class/treeCtrl.h"



PDF::PDF(wxNotebook* notebook) {
	panel = new wxPanel(notebook, wxID_ANY);

	sizer = new wxBoxSizer(wxHORIZONTAL);
	bookmarksSizer = new wxBoxSizer(wxVERTICAL);
	pdfViewerSizer = new wxBoxSizer(wxVERTICAL);

	wxSplitterWindow* outerSplitterWindow = new wxSplitterWindow(panel, wxID_ANY);
	outerSplitterWindow->SetMinimumPaneSize(100);

	splitterWindow = new wxSplitterWindow(outerSplitterWindow, wxID_ANY);
	splitterWindow->SetMinimumPaneSize(250);
	bookmarksPanel = new wxPanel(splitterWindow, wxID_ANY);
	pdfViewerPanel = new wxPanel(splitterWindow, wxID_ANY);
	
	pdfView = new wxPDFView(pdfViewerPanel, wxID_ANY);
	bookmarks = new wxPDFViewBookmarksCtrl(bookmarksPanel, wxID_ANY);
	bookmarks->SetPDFView(pdfView);


	bookmarksPanel->SetSizer(bookmarksSizer);
	pdfViewerPanel->SetSizer(pdfViewerSizer);

	bookmarksSizer->Add(bookmarks, 1, wxEXPAND);
	pdfViewerSizer->Add(pdfView, 1, wxEXPAND);


	splitterWindow->SplitVertically(bookmarksPanel, pdfViewerPanel);


	wxPanel* booklistPanel = new wxPanel(outerSplitterWindow, wxID_ANY);
	wxBoxSizer* booklistSizer = new wxBoxSizer(wxHORIZONTAL);

	TreeCtrl *booklistTree = new TreeCtrl(booklistPanel);
	booklistSizer->Add(booklistTree->GetTree(), 1, wxEXPAND);

	booklistPanel->SetSizer(booklistSizer);


	outerSplitterWindow->SplitVertically(booklistPanel, splitterWindow, 200);

	//sizer->Add(randomPanel, 1, wxEXPAND);
	//sizer->Add(splitterWindow, 1, wxEXPAND);
	sizer->Add(outerSplitterWindow, 1, wxEXPAND);

	pdfView->LoadFile("D:\\Books\\progit.pdf");
	panel->SetSizer(sizer);

}





wxPanel* PDF::GetPanel() {
	return panel;
}

