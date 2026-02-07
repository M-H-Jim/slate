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
	pdfViewToolBar->AddTool(ID_ROTATION, "", wxArtProvider::GetBitmap(wxART_PDFVIEW_ROTATE, wxART_TOOLBAR), "Rotate");
	pdfViewToolBar->AddSeparator();

	wxToggleButton* twoPageToggle = new wxToggleButton(pdfViewToolBar, ID_TOGGLE, "", wxDefaultPosition, wxSize(32, 32));
	twoPageToggle->SetBitmap(wxArtProvider::GetBitmap(wxART_PDFVIEW_TWO_PAGES, wxART_TOOLBAR));
	twoPageToggle->SetToolTip("Toggle Two Page View");
	pdfViewToolBar->AddControl(twoPageToggle);


	//pdfViewToolBar->AddTool(ID_TWO_PAGE, "", wxArtProvider::GetBitmap(wxART_PDFVIEW_TWO_PAGES, wxART_TOOLBAR), "Two Page View");
	//pdfViewToolBar->AddTool(ID_TWO_PAGE_COVER, "", wxArtProvider::GetBitmap(wxART_PDFVIEW_TWO_PAGES_COVER, wxART_TOOLBAR), "Single Page View");


	pdfViewToolBar->AddSeparator();
	pdfViewToolBar->AddTool(wxID_ZOOM_IN, "", wxArtProvider::GetBitmap(wxART_PDFVIEW_ZOOM_IN, wxART_TOOLBAR), "Zoom In");
	pdfViewToolBar->AddTool(wxID_ZOOM_OUT, "", wxArtProvider::GetBitmap(wxART_PDFVIEW_ZOOM_OUT, wxART_TOOLBAR), "Zoom Out");

	gotoPageTextCtrl = new wxTextCtrl(pdfViewToolBar, ID_GOTO_PAGE, "1", wxDefaultPosition, wxSize(80, -1), wxTE_PROCESS_ENTER);
	pdfViewToolBar->AddControl(gotoPageTextCtrl);
	pageCountLabel = new wxStaticText(pdfViewToolBar, wxID_ANY, wxString::Format(" / %d", pdfView->GetPageCount()));
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

	pdfViewToolBar->Bind(wxEVT_TOOL, &PDF::OnRotation, this, ID_ROTATION);



	pdfViewToolBar->Bind(wxEVT_TOGGLEBUTTON, [=](wxCommandEvent& evt) {
		if (evt.GetInt() == 1) {
			pdfView->SetDisplayFlags(wxPDFVIEW_DISPLAY_TWO_PAGE);
		}
		else {
			pdfView->SetDisplayFlags(wxPDFVIEW_DISPLAY_TWO_PAGE_COVER);
		}}, ID_TOGGLE);


	pdfViewToolBar->Bind(wxEVT_TEXT_ENTER, [=](wxCommandEvent&) {
		long pageNum;
		if (gotoPageTextCtrl->GetValue().ToLong(&pageNum)) {
			if (pageNum >= 1 && pageNum <= pdfView->GetPageCount()) {
				pdfView->GoToPage(pageNum);
			}
			else {
				wxMessageBox("Invalid page number.");
			}
		}
		else {
			wxMessageBox("Please enter a valid number.");
		}
		}, ID_GOTO_PAGE);

	
	pdfViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		pdfView->SetZoom(pdfView->GetZoom() + 0.1);
		}, wxID_ZOOM_IN);
	pdfViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		pdfView->SetZoom(pdfView->GetZoom() - 0.1);
		}, wxID_ZOOM_OUT);







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

	searchCtrl->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &PDF::OnSearch, this);

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

	data = dynamic_cast<NodeData*>(booklistTree->GetTree()->GetItemData(item));

	if (!data) {
		wxMessageBox("No data associated with this item.");
		return;
	}

	if (!pdfView->LoadFile(data->url)) {
		wxMessageBox("Failed to load PDF: " + data->url);
		return;
	}
	pageCountLabel->SetLabel(wxString::Format(" / %d", pdfView->GetPageCount()));

	pdfView->SetDisplayFlags(wxPDFVIEW_DISPLAY_TWO_PAGE_COVER);


}

void PDF::OnRotation(wxCommandEvent& evt) {

	wxPDFViewPageOrientation currentOrientation = pdfView->GetOrientation();
	wxPDFViewPageOrientation newOrientation;

	switch(currentOrientation) {
		case wxPDFVIEW_PAGE_ORIENTATION_LEFT:
			newOrientation = wxPDFVIEW_PAGE_ORIENTATION_UP;
			break;
		case wxPDFVIEW_PAGE_ORIENTATION_UP:
			newOrientation = wxPDFVIEW_PAGE_ORIENTATION_RIGHT;
			break;
		case wxPDFVIEW_PAGE_ORIENTATION_RIGHT:
			newOrientation = wxPDFVIEW_PAGE_ORIENTATION_DOWN;
			break;
		case wxPDFVIEW_PAGE_ORIENTATION_DOWN:
			newOrientation = wxPDFVIEW_PAGE_ORIENTATION_LEFT;
			break;
		default:
			newOrientation = wxPDFVIEW_PAGE_ORIENTATION_UP;
			break;
	}


	pdfView->SetOrientation(newOrientation);


	evt.Skip();
}


void PDF::OnSearch(wxCommandEvent& evt) {
	wxString query = searchCtrl->GetValue().Lower();
	if (query.IsEmpty()) {
		return;
	}
	wxTreeItemId root = booklistTree->GetTree()->GetRootItem();
	if (!root.IsOk()) {
		return;
	}

	wxTreeItemId foundItem = FindItemByText(root, query);
	if (foundItem.IsOk()) {
		booklistTree->GetTree()->SelectItem(foundItem);
		booklistTree->GetTree()->EnsureVisible(foundItem);
	}
	else {
		wxMessageBox("No matching item found.", "Search", wxOK | wxICON_INFORMATION);
	}

}

wxTreeItemId PDF::FindItemByText(const wxTreeItemId& parent, const wxString& text) {
	if (booklistTree->GetTree()->GetItemText(parent).Lower().Contains(text)) {
		return parent;
	}
	wxTreeItemIdValue cookie;
	wxTreeItemId child = booklistTree->GetTree()->GetFirstChild(parent, cookie);
	while (child.IsOk()) {
		wxTreeItemId found = FindItemByText(child, text);
		if (found.IsOk()) {
			return found;
		}
		child = booklistTree->GetTree()->GetNextChild(parent, cookie);
	}
	return wxTreeItemId();
}
