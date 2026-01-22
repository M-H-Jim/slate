#include "pdf.h"
#include "class/treeCtrl.h"



PDF::PDF(wxNotebook* notebook) {
	pdfPanel = new wxPanel(notebook, wxID_ANY);

	sizer = new wxBoxSizer(wxHORIZONTAL);
	bookmarksSizer = new wxBoxSizer(wxVERTICAL);
	thumbnailsSizer = new wxBoxSizer(wxVERTICAL);
	pdfViewerSizer = new wxBoxSizer(wxVERTICAL);

	wxSplitterWindow* outerSplitterWindow = new wxSplitterWindow(pdfPanel, wxID_ANY);
	outerSplitterWindow->SetMinimumPaneSize(250);

	splitterWindow = new wxSplitterWindow(outerSplitterWindow, wxID_ANY);
	splitterWindow->SetMinimumPaneSize(250);
	bookmarksPanel = new wxPanel(splitterWindow, wxID_ANY);
	thumbnailsPanel = new wxPanel(splitterWindow, wxID_ANY);
	pdfViewerPanel = new wxPanel(splitterWindow, wxID_ANY);
	
	pdfView = new wxPDFView(pdfViewerPanel, wxID_ANY);
	bookmarks = new wxPDFViewBookmarksCtrl(bookmarksPanel, wxID_ANY);
	thumbnails = new wxPDFViewThumbnailListBox(thumbnailsPanel, wxID_ANY);
	bookmarks->SetPDFView(pdfView);
	thumbnails->SetPDFView(pdfView);
		

	bookmarksPanel->SetSizer(bookmarksSizer);
	thumbnailsPanel->SetSizer(thumbnailsSizer);
	pdfViewerPanel->SetSizer(pdfViewerSizer);

	bookmarksSizer->Add(bookmarks, 1, wxEXPAND);
	thumbnailsSizer->Add(thumbnails, 1, wxEXPAND);
	pdfViewerSizer->Add(pdfView, 1, wxEXPAND);


	bookmarkThumbnailNotebook = new wxNotebook(splitterWindow, wxID_ANY);
	bookmarkThumbnailNotebook->AddPage(bookmarksPanel, "Bookmarks");
	bookmarkThumbnailNotebook->AddPage(thumbnailsPanel, "Thumbnails");



	splitterWindow->SplitVertically(bookmarkThumbnailNotebook, pdfViewerPanel);

	//------------------------------------------------------
	// experimental

	wxPanel* leftPanel = new wxPanel(outerSplitterWindow, wxID_ANY);

	wxSearchCtrl* searchCtrl = new wxSearchCtrl(
		leftPanel,
		wxID_ANY,
		"",
		wxDefaultPosition,
		wxDefaultSize,
		wxTE_PROCESS_ENTER
	);
	searchCtrl->ShowSearchButton(true);
	searchCtrl->ShowCancelButton(true);

	// bind this search
	wxToolBar* booklistToolBar = new wxToolBar(
		leftPanel,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTB_VERTICAL | wxTB_FLAT | wxTB_TEXT | wxNO_BORDER
	);

	booklistToolBar->AddTool(wxID_ADD, "", wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR), "Add a new topic");


	booklistToolBar->Realize();

	wxStaticBox* booklistBox = new wxStaticBox(leftPanel, wxID_ANY, "Book List");
	wxStaticBoxSizer* booklistBoxSizer = new wxStaticBoxSizer(booklistBox, wxVERTICAL);
	TreeCtrl* booklistTree = new TreeCtrl(leftPanel);
	wxTreeCtrl* tree = booklistTree->GetTree();
	booklistBoxSizer->Add(booklistTree->GetTree(), 1, wxEXPAND | wxALL, 5);

	// Bind this 

	wxBoxSizer* booklistTreeToolBarSizer = new wxBoxSizer(wxHORIZONTAL);
	booklistTreeToolBarSizer->Add(booklistToolBar, 0, wxEXPAND);
	booklistTreeToolBarSizer->Add(booklistBoxSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);


	wxBoxSizer* leftPanelSizer = new wxBoxSizer(wxVERTICAL);
	leftPanelSizer->Add(searchCtrl, 0, wxEXPAND, 5);
	leftPanelSizer->Add(booklistTreeToolBarSizer, 1, wxEXPAND, 5);
	leftPanel->SetSizer(leftPanelSizer);



	// end experimental
	//------------------------------------------------------


	//wxPanel* booklistPanel = new wxPanel(outerSplitterWindow, wxID_ANY);
	//wxBoxSizer* booklistSizer = new wxBoxSizer(wxHORIZONTAL);

	//TreeCtrl *booklistTree = new TreeCtrl(booklistPanel);
	//booklistSizer->Add(booklistTree->GetTree(), 1, wxEXPAND);

	//booklistPanel->SetSizer(booklistSizer);


	//------------------------------------------------------


	//outerSplitterWindow->SplitVertically(booklistPanel, splitterWindow, 200);


	outerSplitterWindow->SplitVertically(leftPanel, splitterWindow, 200);





	//sizer->Add(randomPanel, 1, wxEXPAND);
	//sizer->Add(splitterWindow, 1, wxEXPAND);
	sizer->Add(outerSplitterWindow, 1, wxEXPAND);

	pdfView->LoadFile("D:\\Books\\progit.pdf");
	pdfPanel->SetSizer(sizer);

}





wxPanel* PDF::GetPanel() {
	return pdfPanel;
}

