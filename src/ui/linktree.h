#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/webview.h>
#include <wx/treectrl.h>
#include <wx/srchctrl.h>
#include <wx/artprov.h>

#include "class/treeCtrl.h"

class LinkTree {
		wxPanel	*linkTreePanel;
		wxSplitterWindow *splitterWindow;

		wxPanel *splitPanelLeft;
		wxPanel *splitPanelRight;

		wxBoxSizer *splitPanelLeftSizer;
		wxBoxSizer *splitPanelRightSizer;
		wxBoxSizer* linkTreeSizer;

		// Left Side
		wxSearchCtrl *searchCtrl;
		wxToolBar *linkTreeToolBar;
		wxBoxSizer *linkTreeToolBarSizer;
		TreeCtrl *linkTree;

		wxTreeCtrl *tree;

		// Right Side
		wxWebView *webView;
		wxToolBar *webViewToolBar;

	public:
		LinkTree(wxNotebook* notebook);
		wxPanel *GetPanel();

		void OnTreeSelectionChanged(wxTreeEvent& evt);
		void OnSearch(wxCommandEvent& evt);
		wxTreeItemId FindItemByText(const wxTreeItemId& parent, const wxString& text);

};
