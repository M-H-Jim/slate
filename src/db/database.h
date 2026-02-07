#pragma once
#include <sqlite3.h>

#include "class/treeCtrl.h"
#include <wx/treectrl.h>


class Database {
	public:
		Database();
		~Database();

		bool Open();
		void Close();

		sqlite3 *db = nullptr;

		//bool SaveNode(int ParentId, const wxTreeCtrl* tree, const wxTreeItemId& item);

		bool SaveNode(
			const wxString& table,
			const wxString& valueColumn,
			int parentId,
			const wxTreeCtrl* tree,
			const wxTreeItemId& item
		);


		//bool SaveTree(const wxTreeCtrl *tree, const wxTreeItemId& root);

		bool SaveLinksTree(const wxTreeCtrl* tree, const wxTreeItemId& root);
		bool SavePdfTree(const wxTreeCtrl* tree, const wxTreeItemId& root);
		bool LoadTree(
			const wxString& table,
			const wxString& valueColumn,
			NodeType nodeType,
			wxTreeCtrl* tree,
			const wxTreeItemId& parent,
			int parentId = 0
		);


		//bool LoadTree(wxTreeCtrl* tree, const wxTreeItemId& parent, int parentId = 0);

		bool LoadLinksTree(wxTreeCtrl* tree, const wxTreeItemId& root);
		bool LoadPdfTree(wxTreeCtrl* tree, const wxTreeItemId& root);



};