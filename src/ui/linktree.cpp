#include "linktree.h"
#include "class/treeCtrl.h"

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

	//Link Tree Tool Bar
	linkTreeToolBar = new wxToolBar(
		splitPanelLeft,
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTB_VERTICAL | wxTB_FLAT | wxTB_TEXT | wxNO_BORDER
	);

	linkTreeToolBar->AddTool(wxID_ADD, "", wxArtProvider::GetBitmap(wxART_PLUS, wxART_TOOLBAR), "Add a new topic");
	linkTreeToolBar->AddTool(wxID_NEW, "", wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR), "Add a new sub-topic");
	linkTreeToolBar->AddSeparator();
	linkTreeToolBar->AddTool(wxID_EDIT, "", wxArtProvider::GetBitmap(wxART_EDIT, wxART_TOOLBAR), "Edit");
	linkTreeToolBar->AddTool(wxID_DELETE, "", wxArtProvider::GetBitmap(wxART_DELETE, wxART_TOOLBAR), "Delete this topic");


	linkTreeToolBar->Realize();



	// This is an object from my TreeCtrl Class
	TreeCtrl *linkTree = new TreeCtrl(splitPanelLeft);
	//------------------------------------------

	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnAddTopic, linkTree, wxID_ADD);
	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnAddSubTopicFromToolBar, linkTree, wxID_NEW);
	linkTreeToolBar->Bind(wxEVT_TOOL, &TreeCtrl::OnDeleteNode, linkTree, wxID_DELETE);




	linkTreeToolBarSizer = new wxBoxSizer(wxHORIZONTAL);
	linkTreeToolBarSizer->Add(linkTreeToolBar, 0, wxEXPAND);
	linkTreeToolBarSizer->Add(linkTree->GetTree(), 1, wxEXPAND, 5);

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

	webViewToolBar->AddTool(wxID_BACKWARD, "", wxArtProvider::GetBitmap(wxART_GO_BACK, wxART_TOOLBAR));
	webViewToolBar->AddTool(wxID_FORWARD, "", wxArtProvider::GetBitmap(wxART_GO_FORWARD, wxART_TOOLBAR));
	webViewToolBar->AddTool(wxID_REFRESH, "", wxArtProvider::GetBitmap(wxART_REFRESH, wxART_TOOLBAR));





	webViewToolBar->Realize();

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