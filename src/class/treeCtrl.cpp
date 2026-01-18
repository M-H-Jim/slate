#include "treeCtrl.h"

TreeCtrl::TreeCtrl(wxPanel* panel) {
	tree = new wxTreeCtrl(
		panel, 
		wxID_ANY,
		wxDefaultPosition,
		wxDefaultSize,
		wxTR_HIDE_ROOT | wxTR_LINES_AT_ROOT | wxTR_EDIT_LABELS | wxTR_HAS_BUTTONS
		);
	hiddenRoot = tree->AddRoot("Root");
	tree->AppendItem(hiddenRoot, "c language");
	//tree->AppendItem(hiddenRoot, "C language");
	//tree->AppendItem(hiddenRoot, "C language");
	//tree->AppendItem(hiddenRoot, "C language");

	tree->Bind(wxEVT_MENU, &TreeCtrl::OnAddTopic, this, ID_ADDTOPIC);
	tree->Bind(wxEVT_MENU, &TreeCtrl::OnAddSubTopic, this, ID_ADDSUBTOPIC);
	tree->Bind(wxEVT_MENU, &TreeCtrl::OnEditLink, this, ID_EDIT_LINK);
	tree->Bind(wxEVT_MENU, &TreeCtrl::OnDeleteNode, this, ID_DELETENODE);

	tree->Bind(wxEVT_TREE_ITEM_MENU, &TreeCtrl::OnTreeRightClick, this);
	tree->Bind(wxEVT_LEFT_DOWN, &TreeCtrl::OnTreeLeftClick, this);
	tree->Bind(wxEVT_TREE_BEGIN_DRAG, &TreeCtrl::OnBeginDrag, this);
	tree->Bind(wxEVT_TREE_END_DRAG, &TreeCtrl::OnEndDrag, this);


}

wxTreeCtrl* TreeCtrl::GetTree() const{
	return tree;
}

void TreeCtrl::OnAddTopic(wxCommandEvent& evt) {
	static int topicCounter = 1;
	wxString topicName = wxString::Format("Topic %d", topicCounter++);
	wxTreeItemId newTopic = tree->AppendItem(hiddenRoot, topicName, -1, -1, new NodeData("https://example.com"));
	tree->EditLabel(newTopic);

	tree->SelectItem(newTopic);
	tree->EnsureVisible(newTopic);

}

void TreeCtrl::OnTreeRightClick(wxTreeEvent& evt) {
	rightClickedItem = evt.GetItem();

	wxMenu menu;

	menu.Append(ID_EDIT_LINK, "Edit Link");
	menu.Append(ID_ADDSUBTOPIC, "Add New Sub-Topic");
	menu.Append(ID_ADDTOPIC, "Add New Topic");
	menu.AppendSeparator();
	menu.Append(ID_DELETENODE, "Delete");

	tree->PopupMenu(&menu);
}

void TreeCtrl::OnTreeLeftClick(wxMouseEvent& evt) {
	int flags = 0;
	wxTreeItemId item = tree->HitTest(evt.GetPosition(), flags);
	if (!item.IsOk()) {
		tree->UnselectAll();
	}
	evt.Skip();
}



void TreeCtrl::OnAddSubTopic(wxCommandEvent& evt) {

	    wxTreeItemId selected = tree->GetSelection();
	    
	    if(!selected.IsOk() || selected == hiddenRoot) {
	        wxMessageBox("Please select a topic to add a link under it");
	        return;
	    }


	static int subTopicCounter = 1;
	wxString subTopicName = wxString::Format("SubTopic %d", subTopicCounter++);
	wxTreeItemId newSubTopic = tree->AppendItem(rightClickedItem, subTopicName, -1, -1, new NodeData("https://example.com"));

	//tree->EditLabel(newSubTopic);

	tree->SelectItem(newSubTopic);
	tree->EnsureVisible(newSubTopic);
}

void TreeCtrl::OnAddSubTopicFromToolBar(wxCommandEvent& evt) {
	wxTreeItemId selected = tree->GetSelection();

	if (!selected.IsOk() || selected == hiddenRoot) {
		wxMessageBox("Please select a topic to add a sub-topic under it");
		return;
	}

	static int subTopicCounter = 1;
	wxString subTopicName = wxString::Format("SubTopic %d", subTopicCounter++);

	wxTreeItemId newSubTopic = tree->AppendItem(selected, subTopicName, -1, -1, new NodeData("https://exmaple.com"));

	//tree->EditLabel(newSubTopic);

	tree->SelectItem(newSubTopic);
	tree->EnsureVisible(newSubTopic);
}



void TreeCtrl::OnEditLink(wxCommandEvent& evt) {
	if (!rightClickedItem.IsOk()) {
		return;
	}
	auto *data = static_cast<NodeData*>(tree->GetItemData(rightClickedItem));
	if (!data) {
		return;
	}
	wxTextEntryDialog dialog(
		tree,
		"Enter link:",
		"Edit Link",
		data->url
	);

	if(dialog.ShowModal() == wxID_OK) {
		data->url = dialog.GetValue();
	}
}

void TreeCtrl::OnDeleteNode(wxCommandEvent& evt) {

	wxTreeItemId nodeToDelete;

	if (rightClickedItem.IsOk()) {
		nodeToDelete = rightClickedItem;
	}
	else {
		nodeToDelete = tree->GetSelection();
	}

	if (!nodeToDelete.IsOk() || nodeToDelete == hiddenRoot) {
		wxMessageBox("Cannot delete this root");
		return;
	}

	int key = wxMessageBox(
		"Delete this topic and all it's sub-topics?",
		"Confirm Deletion",
		wxYES_NO | wxICON_WARNING,
		tree
	);
	if (key != wxYES) {
		return;
	}

	tree->Delete(nodeToDelete);
	tree->UnselectAll();
	rightClickedItem = wxTreeItemId();
}





void TreeCtrl::OnBeginDrag(wxTreeEvent& evt) {
	wxTreeItemId item = evt.GetItem();
	if (!item.IsOk() || item == hiddenRoot) {
		return;
	}
	draggedItem = item;
	evt.Allow();

}


wxTreeItemId TreeCtrl::CloneSubtree(const wxTreeItemId& source, const wxTreeItemId& newParent) {
	auto *data = source.IsOk() ? static_cast<NodeData*>(tree->GetItemData(source)) : nullptr;

	wxTreeItemId newItem = tree->AppendItem(newParent, tree->GetItemText(source), -1, -1, data ? new NodeData(*data) : nullptr);
	
	wxTreeItemIdValue cookie;
	wxTreeItemId child = tree->GetFirstChild(source, cookie);

	while (child.IsOk()) {
		CloneSubtree(child, newItem);
		child = tree->GetNextChild(source, cookie);
	}
	return newItem;
}

void TreeCtrl::OnEndDrag(wxTreeEvent& evt) {
	if (!draggedItem.IsOk()) {
		return;
	}

	wxTreeItemId target = evt.GetItem();

	if (!target.IsOk()) {
		target = hiddenRoot;
	}
	else if (target == draggedItem) {
		return;
	}

	wxTreeItemId parent = target;
	while (parent.IsOk()) {
		if (parent == draggedItem) {
			return;
		}
		parent = tree->GetItemParent(parent);
	}

	wxTreeItemId newItem = CloneSubtree(draggedItem, target);
	tree->SelectItem(newItem);
	tree->EnsureVisible(newItem);

	tree->Delete(draggedItem);

	draggedItem = wxTreeItemId();
}