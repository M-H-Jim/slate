#pragma once

#include <wx/wx.h>
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

class PDF {
	wxSplitterWindow* splitterWindow;

	wxPanel *pdfPanel;
	wxPanel *bookmarksPanel;
	wxPanel *thumbnailsPanel;
	wxPanel *pdfViewerPanel;

	wxNotebook *bookmarkThumbnailNotebook;

	wxBoxSizer *sizer;
	wxBoxSizer *bookmarksSizer;
	wxBoxSizer *thumbnailsSizer;
	wxBoxSizer *pdfViewerSizer;


	wxPDFView *pdfView;
	wxPDFViewBookmarksCtrl* bookmarks;
	wxPDFViewThumbnailListBox* thumbnails;
	

	public:
		PDF(wxNotebook *notebook);
		wxPanel *GetPanel();
};

