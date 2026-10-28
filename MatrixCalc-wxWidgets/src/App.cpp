#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/image.h>
#include "Globals.h"

wxIMPLEMENT_APP(App);

std::vector<Matrix> Matrices;
Matrix* selectedMatrix = nullptr;

bool App::OnInit() {
	wxInitAllImageHandlers();

	MainFrame* mainFrame = new MainFrame("Matrix Calc");
	mainFrame->SetClientSize(1000, 650);
	mainFrame->SetMinSize(wxSize(800, 500));
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
