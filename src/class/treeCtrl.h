#pragma once

#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/treectrl.h>
#include <wx/tipwin.h>

enum {
	ID_ADDTOPIC = wxID_HIGHEST + 1,
	ID_ADDSUBTOPIC,
	ID_ADDPDF,
	ID_ADDSUBPDF,
	ID_DELETENODE,
	ID_EDIT_LINK
};

enum class NodeType {
	TOPIC,
	PDF
};




class NodeData : public wxTreeItemData {
	public:
		NodeType type;
		wxString url;
		NodeData(NodeType t, const wxString& u = " ") : type(t), url(u) {}
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

		void OnAddPDF(wxCommandEvent& evt);
		void OnAddSubPDF(wxCommandEvent& evt);
		


		void OnBeginDrag(wxTreeEvent& evt);
		void OnEndDrag(wxTreeEvent& evt);
		void OnTreeRightClick(wxTreeEvent& evt);
		void OnTreeLeftClick(wxMouseEvent& evt);

		wxTreeItemId CloneSubtree(const wxTreeItemId& source, const wxTreeItemId& newParent);
};
