#include "app.h"
#include "mainframe.h"
#include "db/database.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {



	SetAppearance(Appearance::System);

	wxImage::AddHandler(new wxPNGHandler);
	wxPDFViewArtProvider::Initialize();

	MainFrame* mainFrame = new MainFrame("slate");
	mainFrame->SetClientSize(1500, 800);
	mainFrame->Center();
	mainFrame->Show();

	return true;
}