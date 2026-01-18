#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/webview.h>
#include <wx/treectrl.h>
#include <wx/srchctrl.h>
#include <wx/artprov.h>


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
		wxTreeCtrl *linkTreeCtrl;

		// Right Side
		wxWebView *webView;
		wxToolBar *webViewToolBar;

	public:
		LinkTree(wxNotebook* notebook);
		wxPanel *GetPanel();



};
