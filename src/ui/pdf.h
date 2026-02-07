#pragma once

#include <wx/wx.h>
#include <wx/tglbtn.h>
#include <wx/sharedptr.h>
#include <wx/webview.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/srchctrl.h>
#include <wx/artprov.h>


//#include "PDFViewDocumentPanel.h"
//#include "PDFViewArtProvider.h"
//#include "private/PDFViewActivityPanel.h"

#include "PDFView.h"
#include "PDFViewBookmarksCtrl.h"
#include "PDFViewThumbnailListBox.h"
#include "PDFViewArtProvider.h"
#include "class/treeCtrl.h"

enum {
	ID_ROTATION = wxID_HIGHEST + 100,
	ID_TOGGLE,
	ID_GOTO_PAGE
};



class PDF {
	wxSplitterWindow *splitterWindow;
	wxSplitterWindow *outerSplitterWindow;

	wxPanel *pdfPanel;
	wxPanel	*leftPanel;
	wxPanel *bookmarksPanel;
	wxPanel *thumbnailsPanel;
	wxPanel *pdfViewerPanel;

	wxNotebook *bookmarkThumbnailNotebook;

	wxBoxSizer *sizer;
	wxBoxSizer *bookmarksSizer;
	wxBoxSizer *thumbnailsSizer;
	wxBoxSizer *pdfViewerSizer;
	wxStaticBoxSizer *booklistBoxSizer;
	wxBoxSizer *booklistTreeToolBarSizer;
	wxBoxSizer *leftPanelSizer;

	wxSearchCtrl *searchCtrl;

	wxToolBar *booklistToolBar;

	wxStaticBox	*booklistBox;

	TreeCtrl *booklistTree;




	wxPDFView *pdfView;
	wxPDFViewBookmarksCtrl* bookmarks;
	wxPDFViewThumbnailListBox* thumbnails;

	wxTextCtrl *gotoPageTextCtrl;
	wxStaticText *pageCountLabel;



	NodeData* data;



	public:
		PDF(wxNotebook *notebook);
		wxPanel *GetPanel();

		void OnSearch(wxCommandEvent& evt);
		wxTreeItemId FindItemByText(const wxTreeItemId& parent, const wxString& text);


		void OnTreeSelectionChanged(wxTreeEvent& evt);
		void OnRotation(wxCommandEvent& evt);

		wxTreeCtrl* GetTree() {
			return booklistTree->GetTree();
		}
		TreeCtrl* GetTreeCtrl() {
			return booklistTree;
		}

};

