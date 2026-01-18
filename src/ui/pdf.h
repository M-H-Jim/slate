#pragma once

#include <wx/wx.h>
#include <wx/sharedptr.h>
#include <wx/webview.h>
#include <wx/notebook.h>
#include <wx/splitter.h>


#include "PDFViewDocumentPanel.h"
#include "PDFViewArtProvider.h"
#include "private/PDFViewActivityPanel.h"

class PDF {
	wxSplitterWindow* splitterWindow;

	wxPanel *panel;
	wxPanel *bookmarksPanel;
	wxPanel *pdfViewerPanel;

	wxBoxSizer *sizer;
	wxBoxSizer *bookmarksSizer;
	wxBoxSizer *pdfViewerSizer;


	wxPDFView *pdfView;
	wxPDFViewBookmarksCtrl* bookmarks;
	

	public:
		PDF(wxNotebook *notebook);
		wxPanel *GetPanel();
};

