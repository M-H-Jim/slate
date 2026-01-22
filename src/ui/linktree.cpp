#include "linktree.h"


LinkTree::LinkTree(wxNotebook* notebook) {
	linkTreePanel = new wxPanel(notebook, wxID_ANY);
	splitterWindow = new wxSplitterWindow(linkTreePanel, wxID_ANY);
	splitterWindow->SetMinimumPaneSize(250);


	// Left Side
	splitPanelLeft = new wxPanel(splitterWindow, wxID_ANY);

	//Search Control
	searchCtrl = new wxSearchCtrl(
		splitPanelLeft,
		wxID_ANY,
		"",
		wxDefaultPosition,
		wxDefaultSize,
		wxTE_PROCESS_ENTER
	);
	searchCtrl->ShowSearchButton(true);
	searchCtrl->ShowCancelButton(true);

	searchCtrl->Bind(wxEVT_SEARCHCTRL_SEARCH_BTN, &LinkTree::OnSearch, this);

	//Link Tree Tool Bar
	linkTreeToolBar = new wxToolBar(
		splitPanelLeft,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTB_VERTICAL | wxTB_FLAT | wxTB_TEXT | wxNO_BORDER
	);

	linkTreeToolBar->AddTool(wxID_ADD, "", wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR), "Add a new topic");
	linkTreeToolBar->AddTool(wxID_NEW, "", wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR), "Add a new sub-topic");
	linkTreeToolBar->AddTool(wxID_EDIT, "", wxArtProvider::GetBitmap(wxART_EDIT, wxART_TOOLBAR), "Edit");
	linkTreeToolBar->AddSeparator();
	linkTreeToolBar->AddTool(wxID_DELETE, "", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR), "Delete this topic");


	linkTreeToolBar->Realize();



	// This is an object from my TreeCtrl Class
	wxStaticBox *treeBox = new wxStaticBox(splitPanelLeft, wxID_ANY, "Link Tree");
	wxStaticBoxSizer* treeBoxSizer = new wxStaticBoxSizer(treeBox, wxVERTICAL);
	linkTree = new TreeCtrl(splitPanelLeft);
	tree = linkTree->GetTree();
	treeBoxSizer->Add(linkTree->GetTree(), 1, wxEXPAND | wxALL, 5);

	tree->Bind(wxEVT_TREE_SEL_CHANGED, &LinkTree::OnTreeSelectionChanged, this);


	//------------------------------------------

	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnAddTopic, linkTree, wxID_ADD);
	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnAddSubTopicFromToolBar, linkTree, wxID_NEW);
	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnEditNode, linkTree, wxID_EDIT);
	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnDeleteNode, linkTree, wxID_DELETE);




	linkTreeToolBarSizer = new wxBoxSizer(wxHORIZONTAL);
	linkTreeToolBarSizer->Add(linkTreeToolBar, 0, wxEXPAND);
	//linkTreeToolBarSizer->Add(linkTree->GetTree(), 1, wxEXPAND, 5);
	linkTreeToolBarSizer->Add(treeBoxSizer, 1, wxEXPAND | wxLEFT | wxRIGHT, 5);


	splitPanelLeftSizer = new wxBoxSizer(wxVERTICAL);
	splitPanelLeftSizer->Add(searchCtrl, 0, wxEXPAND, 5);
	splitPanelLeftSizer->Add(linkTreeToolBarSizer, 1, wxEXPAND, 5);
	splitPanelLeft->SetSizer(splitPanelLeftSizer);



	// Right Side

	splitPanelRight = new wxPanel(splitterWindow, wxID_ANY);

	webViewToolBar = new wxToolBar(
		splitPanelRight,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTB_HORIZONTAL | wxTB_FLAT
	);

	webViewToolBar->AddTool(wxID_BACKWARD, "", wxArtProvider::GetBitmap(wxART_GO_BACK, wxART_TOOLBAR), "Back");
	webViewToolBar->AddTool(wxID_FORWARD, "", wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR), "Forward");
	webViewToolBar->AddTool(wxID_REFRESH, "", wxArtProvider::GetBitmap(wxART_REFRESH, wxART_TOOLBAR), "Reload");
	webViewToolBar->AddSeparator();
	webViewToolBar->AddTool(wxID_STOP, "", wxArtProvider::GetBitmap(wxART_CROSS_MARK), "Stop");

	webViewToolBar->Realize();


	webViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		webView->GoBack();
		}, wxID_BACKWARD);

	webViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		webView->GoForward();
		}, wxID_FORWARD);

	webViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		webView->Reload();
		}, wxID_REFRESH);

	webViewToolBar->Bind(wxEVT_TOOL, [=](wxCommandEvent&) {
		webView->Stop();
		}, wxID_STOP);







	webView = wxWebView::New(splitPanelRight, wxID_ANY, "https://www.duckduckgo.com");

	splitPanelRightSizer = new wxBoxSizer(wxVERTICAL);
	splitPanelRightSizer->Add(webViewToolBar, 0, wxEXPAND);
	splitPanelRightSizer->Add(webView, 1, wxEXPAND);
	splitPanelRight->SetSizer(splitPanelRightSizer);

	splitterWindow->SplitVertically(splitPanelLeft, splitPanelRight);

	linkTreeSizer = new wxBoxSizer(wxHORIZONTAL);
	linkTreeSizer->Add(splitterWindow, 1, wxEXPAND);
	linkTreePanel->SetSizer(linkTreeSizer);


}

wxPanel* LinkTree::GetPanel() {
	return linkTreePanel;
}

void LinkTree::OnTreeSelectionChanged(wxTreeEvent& evt) {
	wxTreeItemId item = evt.GetItem();
	if (!item.IsOk()) {
		return;
	}

	auto *data = static_cast<NodeData*>(tree->GetItemData(item));
	if (!data || data->url.IsEmpty()) {
		return;
	}
	webView->LoadURL(data->url);
}

void LinkTree::OnSearch(wxCommandEvent& evt) {
	wxString query = searchCtrl->GetValue().Lower();
	if (query.IsEmpty()) {
		return;
	}
	wxTreeItemId root = linkTree->GetTree()->GetRootItem();
	if (!root.IsOk()) {
		return;
	}

	wxTreeItemId foundItem = FindItemByText(root, query);
	if (foundItem.IsOk()) {
		linkTree->GetTree()->SelectItem(foundItem);
		linkTree->GetTree()->EnsureVisible(foundItem);
	}
	else {
		wxMessageBox("No matching item found.", "Search", wxOK | wxICON_INFORMATION);
	}

}

wxTreeItemId LinkTree::FindItemByText(const wxTreeItemId& parent, const wxString& text) {
	if (linkTree->GetTree()->GetItemText(parent).Lower().Contains(text)) {
		return parent;
	}
	wxTreeItemIdValue cookie;
	wxTreeItemId child = linkTree->GetTree()->GetFirstChild(parent, cookie);
	while (child.IsOk()) {
		wxTreeItemId found = FindItemByText(child, text);
		if (found.IsOk()) {
			return found;
		}
		child = linkTree->GetTree()->GetNextChild(parent, cookie);
	}
	return wxTreeItemId();
}