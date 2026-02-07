#include "database.h"
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/msgdlg.h>

Database::Database() {}
Database::~Database() {
	Close();
}

bool Database::Open() {
	
	wxString exePath = wxStandardPaths::Get().GetExecutablePath();
	wxFileName fn(exePath);

	wxString dbPath = fn.GetPath() + "/slate.db";

	if(sqlite3_open(dbPath.mb_str(), &db) != SQLITE_OK) {
		wxMessageBox("Failed to open database");
		return false;
	}

	const char* sql =
		"CREATE TABLE IF NOT EXISTS nodes ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"parent_id INTEGER,"
		"title TEXT,"
		"link TEXT);"
		
		"CREATE TABLE IF NOT EXISTS pdf_nodes ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"parent_id INTEGER,"
		"title TEXT,"
		"path TEXT);";




	char *err = nullptr;

	if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK) {
		wxMessageBox(err);
		sqlite3_free(err);
		return false;
	}

	return true;
}

void Database::Close() {
	if (db) {
		sqlite3_close(db);
		db = nullptr;
	}
}

//bool database::savenode(int parentid, const wxtreectrl* tree, const wxtreeitemid& item) {
//	if (!item.isok() || item == tree->getrootitem()) {
//		return true;
//	}
//
//	nodedata* data = static_cast<nodedata*>(tree->getitemdata(item));
//	if (!data) {
//		return true;
//	}
//
//	const char* sql = "insert into nodes (parent_id, title, link) values (?, ?, ?);";
//	sqlite3_stmt* stmt = nullptr;
//
//	if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != sqlite_ok) {
//		return false;
//	}
//
//	sqlite3_bind_int(stmt, 1, parentid);
//	sqlite3_bind_text(stmt, 2, tree->getitemtext(item).mb_str(), -1, sqlite_transient);
//	sqlite3_bind_text(stmt, 3, data->url.mb_str(), -1, sqlite_transient);
//
//	if (sqlite3_step(stmt) != sqlite_done) {
//		sqlite3_finalize(stmt);
//		return false;
//	}
//
//	sqlite3_finalize(stmt);
//
//	wxtreeitemidvalue cookie;
//	wxtreeitemid child = tree->getfirstchild(item, cookie);
//	while (child.isok()) {
//		savenode(sqlite3_last_insert_rowid(db), tree, child);
//		child = tree->getnextchild(item, cookie);
//	}
//
//	return true;
//
//}

bool Database::SaveNode(
	const wxString& table,
	const wxString& valueColumn,
	int parentId,
	const wxTreeCtrl* tree,
	const wxTreeItemId& item
) {
	if (!item.IsOk() || item == tree->GetRootItem()) {
		return true;
	}

	NodeData* data = static_cast<NodeData*>(tree->GetItemData(item));
	if (!data) {
		return true;
	}

	wxString sql = wxString::Format(
		"INSERT INTO %s (parent_id, title, %s) VALUES (?, ?, ?);",
		table, valueColumn
	);

	sqlite3_stmt* stmt = nullptr;
	if (sqlite3_prepare_v2(db, sql.mb_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		return false;
	}

	sqlite3_bind_int(stmt, 1, parentId);
	sqlite3_bind_text(stmt, 2, tree->GetItemText(item).mb_str(), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, data->url.mb_str(), -1, SQLITE_TRANSIENT);

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		sqlite3_finalize(stmt);
		return false;
	}

	int newId = (int)sqlite3_last_insert_rowid(db);
	sqlite3_finalize(stmt);

	wxTreeItemIdValue cookie;
	wxTreeItemId child = tree->GetFirstChild(item, cookie);
	while (child.IsOk()) {
		if (!SaveNode(table, valueColumn, newId, tree, child)) {
			return false;
		}
		child = tree->GetNextChild(item, cookie);
	}
	return true;
}






//bool Database::SaveTree(const wxTreeCtrl* tree, const wxTreeItemId& root) {
//	sqlite3_exec(db, "DELETE FROM nodes;", nullptr, nullptr, nullptr);
//
//	wxTreeItemIdValue cookie;
//	wxTreeItemId child = tree->GetFirstChild(root, cookie);
//	while (child.IsOk()) {
//		SaveNode(0, tree, child);
//		child = tree->GetNextChild(root, cookie);
//	}
//	return true;
//}

bool Database::SaveLinksTree(const wxTreeCtrl* tree, const wxTreeItemId& root) {
	sqlite3_exec(db, "DELETE FROM nodes;", nullptr, nullptr, nullptr);

	wxTreeItemIdValue cookie;
	wxTreeItemId child = tree->GetFirstChild(root, cookie);
	while (child.IsOk()) {
		SaveNode("nodes", "link", 0, tree, child);
		child = tree->GetNextChild(root, cookie);
	}
	return true;
}
bool Database::SavePdfTree(const wxTreeCtrl* tree, const wxTreeItemId& root) {
	sqlite3_exec(db, "DELETE FROM pdf_nodes;", nullptr, nullptr, nullptr);
	wxTreeItemIdValue cookie;
	wxTreeItemId child = tree->GetFirstChild(root, cookie);
	while (child.IsOk()) {
		SaveNode("pdf_nodes", "path", 0, tree, child);
		child = tree->GetNextChild(root, cookie);
	}
	return true;
}




//
//bool Database::LoadTree(wxTreeCtrl* tree, const wxTreeItemId& parent, int parentId) {
//	const char* sql = "SELECT id, title, link FROM nodes WHERE parent_id = ?;";
//	sqlite3_stmt* stmt = nullptr;
//
//	if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK) {
//		return false;
//	}
//
//	sqlite3_bind_int(stmt, 1, parentId);
//
//	while (sqlite3_step(stmt) == SQLITE_ROW) {
//		int id = sqlite3_column_int(stmt, 0);
//		const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//		const char* link = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
//
//		wxTreeItemId item = tree->AppendItem(parent, wxString(title), -1, -1, new NodeData(NodeType::TOPIC, link));
//		LoadTree(tree, item, id);
//	}
//
//	sqlite3_finalize(stmt);
//	return true;
//}

bool Database::LoadTree(
	const wxString& table,
	const wxString& valueColumn,
	NodeType nodeType,
	wxTreeCtrl* tree,
	const wxTreeItemId& parent,
	int parentId
) {
	wxString sql = wxString::Format(
		"SELECT id, title, %s FROM %s WHERE parent_id = ? ORDER BY id;",
		valueColumn,
		table
	);

	sqlite3_stmt* stmt = nullptr;
	if (sqlite3_prepare_v2(db, sql.mb_str(), -1, &stmt, nullptr) != SQLITE_OK) {
		return false;
	}

	sqlite3_bind_int(stmt, 1, parentId);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));

		wxTreeItemId item = tree->AppendItem(
			parent,
			wxString(title),
			-1,
			-1,
			new NodeData(nodeType, wxString(value))
		);

		LoadTree(table, valueColumn, nodeType, tree, item, id);
	}

	sqlite3_finalize(stmt);
	return true;
}

bool Database::LoadLinksTree(wxTreeCtrl* tree, const wxTreeItemId& root) {
	tree->DeleteChildren(root);
	return LoadTree("nodes", "link", NodeType::TOPIC, tree, root);
}
bool Database::LoadPdfTree(wxTreeCtrl* tree, const wxTreeItemId& root) {
	tree->DeleteChildren(root);
	return LoadTree("pdf_nodes", "path", NodeType::PDF, tree, root);
}
