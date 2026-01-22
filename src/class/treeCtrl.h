#pragma once

#include <wx/wx.h>
#include <wx/treectrl.h>
#include <wx/tipwin.h>

enum {
	ID_ADDTOPIC = wxID_HIGHEST + 1,
	ID_ADDSUBTOPIC,
	ID_DELETENODE,
	ID_EDIT_LINK
};



class NodeData : public wxTreeItemData {
	public:
		wxString url;
		NodeData(const wxString& u = " ") : url(u) {}
};

class TreeCtrl {
		wxTreeCtrl *tree;
		wxTreeItemId hiddenRoot;
		wxTreeItemId rightClickedItem;
		wxTreeItemId draggedItem;
	public:
		TreeCtrl(wxPanel* panel);
		wxTreeCtrl* GetTree() const;
		void OnAddTopic(wxCommandEvent& evet);
		void OnAddSubTopic(wxCommandEvent& evt);
		void OnAddSubTopicFromToolBar(wxCommandEvent& evt);
		void OnEditLink(wxCommandEvent& evt);
		void OnDeleteNode(wxCommandEvent& evt);
		void OnEditNode(wxCommandEvent& evt);

		void OnBeginDrag(wxTreeEvent& evt);
		void OnEndDrag(wxTreeEvent& evt);
		void OnTreeRightClick(wxTreeEvent& evt);
		void OnTreeLeftClick(wxMouseEvent& evt);

		wxTreeItemId CloneSubtree(const wxTreeItemId& source, const wxTreeItemId& newParent);
};
