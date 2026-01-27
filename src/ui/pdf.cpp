#include "pdf.h"



PDF::PDF(wxNotebook* notebook) {
	pdfPanel = new wxPanel(notebook, wxID_ANY);

	sizer = new wxBoxSizer(wxHORIZONTAL);
	bookmarksSizer = new wxBoxSizer(wxVERTICAL);
	thumbnailsSizer = new wxBoxSizer(wxVERTICAL);
	pdfViewerSizer = new wxBoxSizer(wxVERTICAL);

	outerSplitterWindow = new wxSplitterWindow(pdfPanel, wxID_ANY);
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
	
	// temporary hardcoded PDF file path
	pdfView->LoadFile("D:\\Books\\progit.pdf");


	bookmarksPanel->SetSizer(bookmarksSizer);
	thumbnailsPanel->SetSizer(thumbnailsSizer);
	pdfViewerPanel->SetSizer(pdfViewerSizer);

	bookmarksSizer->Add(bookmarks, 1, wxEXPAND);
	thumbnailsSizer->Add(thumbnails, 1, wxEXPAND);
	pdfViewerSizer->Add(pdfView, 1, wxEXPAND);

	wxToolBar *pdfViewToolBar = new wxToolBar(
		pdfViewerPanel,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTB_HORIZONTAL | wxTB_TEXT | wxNO_BORDER
	);

	pdfViewToolBar->AddTool(wxID_BACKWARD, "", wxArtProvider::GetBitmap(wxART_GO_BACK, wxART_TOOLBAR), "Show previous page");
	pdfViewToolBar->AddTool(wxID_FORWARD, "", wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR), "Show next Page");
	pdfViewToolBar->AddTool(wxID_FIRST, "", wxArtProvider::GetBitmap(wxART_GOTO_FIRST, wxART_TOOLBAR), "Show first page");
	pdfViewToolBar->AddTool(wxID_LAST, "", wxArtProvider::GetBitmap(wxART_GOTO_LAST, wxART_TOOLBAR), "Show last page");



	wxStaticText* pageCountLabel = new wxStaticText(pdfViewToolBar, wxID_ANY, wxString::Format(" / %d", pdfView->GetPageCount()));
	pdfViewToolBar->AddControl(pageCountLabel);



	pdfViewToolBar->Realize();

	wxBoxSizer* pdfViewToolBarSizer = new wxBoxSizer(wxVERTICAL);
	pdfViewToolBarSizer->Add(pdfViewToolBar, 0, wxEXPAND);
	pdfViewToolBarSizer->Add(pdfView, 1, wxEXPAND);
	pdfViewerPanel->SetSizer(pdfViewToolBarSizer);





	bookmarkThumbnailNotebook = new wxNotebook(splitterWindow, wxID_ANY);
	bookmarkThumbnailNotebook->AddPage(bookmarksPanel, "Bookmarks");
	bookmarkThumbnailNotebook->AddPage(thumbnailsPanel, "Thumbnails");



	splitterWindow->SplitVertically(bookmarkThumbnailNotebook, pdfViewerPanel, 200);



	pdfViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		pdfView->NavigateToPage(wxPDFVIEW_PAGE_NAV_PREV);
		}, wxID_BACKWARD);

	pdfViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		pdfView->NavigateToPage(wxPDFVIEW_PAGE_NAV_NEXT);
		}, wxID_FORWARD);
	pdfViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		pdfView->NavigateToPage(wxPDFVIEW_PAGE_NAV_FIRST);
		}, wxID_FIRST);
	pdfViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		pdfView->NavigateToPage(wxPDFVIEW_PAGE_NAV_LAST);
		}, wxID_LAST);


	//------------------------------------------------------
	// experimental

	leftPanel = new wxPanel(outerSplitterWindow, wxID_ANY);

	searchCtrl = new wxSearchCtrl(
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
	booklistToolBar = new wxToolBar(
		leftPanel,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTB_VERTICAL | wxTB_FLAT | wxTB_TEXT | wxNO_BORDER
	);

	booklistToolBar->AddTool(wxID_ADD, "", wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR), "Add a new topic");
	booklistToolBar->AddTool(wxID_NEW, "", wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR), "Add a new sub-topic");
	booklistToolBar->AddTool(wxID_EDIT, "", wxArtProvider::GetBitmap(wxART_EDIT, wxART_TOOLBAR), "Edit");
	booklistToolBar->AddSeparator();
	booklistToolBar->AddTool(wxID_DELETE, "", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR), "Delete this topic");

	booklistToolBar->Realize();

	booklistBox = new wxStaticBox(leftPanel, wxID_ANY, "Book List");
	booklistBoxSizer = new wxStaticBoxSizer(booklistBox, wxVERTICAL);
	booklistTree = new TreeCtrl(leftPanel);
	booklistBoxSizer->Add(booklistTree->GetTree(), 1, wxEXPAND | wxALL, 5);

	booklistTree->GetTree()->Bind(wxEVT_TREE_SEL_CHANGED, &PDF::OnTreeSelectionChanged, this);


	booklistToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnAddPDF, booklistTree, wxID_ADD);
	booklistToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnAddSubPDF, booklistTree, wxID_NEW);
	booklistToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnEditNode, booklistTree, wxID_EDIT);
	booklistToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnDeleteNode, booklistTree, wxID_DELETE);

	// Bind this 


	booklistTreeToolBarSizer = new wxBoxSizer(wxHORIZONTAL);
	booklistTreeToolBarSizer->Add(booklistToolBar, 0, wxEXPAND);
	booklistTreeToolBarSizer->Add(booklistBoxSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);


	leftPanelSizer = new wxBoxSizer(wxVERTICAL);
	leftPanelSizer->Add(searchCtrl, 0, wxEXPAND, 5);
	leftPanelSizer->Add(booklistTreeToolBarSizer, 1, wxEXPAND, 5);
	leftPanel->SetSizer(leftPanelSizer);



	// end experimental
	//------------------------------------------------------


	outerSplitterWindow->SplitVertically(leftPanel, splitterWindow, 200);

	sizer->Add(outerSplitterWindow, 1, wxEXPAND);


	pdfPanel->SetSizer(sizer);

}





wxPanel* PDF::GetPanel() {
	return pdfPanel;
}

void PDF::OnTreeSelectionChanged(wxTreeEvent& evt) {
	wxTreeItemId item = evt.GetItem();
	if (!item.IsOk()) {
		return;
	}

	NodeData* data = dynamic_cast<NodeData*>(booklistTree->GetTree()->GetItemData(item));

	if (!data) {
		wxMessageBox("No data associated with this item.");
		return;
	}

	pdfView->LoadFile(data->url);

}