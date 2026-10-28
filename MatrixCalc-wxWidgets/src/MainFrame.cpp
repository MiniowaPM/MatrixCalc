#include "MainFrame.h"
#include "MatrixEquations.h"
#include <wx/listctrl.h>
#include <wx/choice.h>
#include <wx/valnum.h>
#include <wx/image.h>
#include <wx/filename.h>
#include <wx/grid.h>
#include "Globals.h"
#include <fstream>
#include <sstream>

enum ButtonIDs {
	BUTTON_ID_ADD = 2,
	BUTTON_ID_DELETE = 3,
	BUTTON_ID_COPY = 4,
	BUTTON_ID_EDIT = 5,
	BUTTON_ID_MATFUNC = 6,
	BUTTON_ID_DROP = 7,
	BUTTON_ID_SAVE = 8
};

enum PanelIDs {
	PANEL_ID_TOOLBAR = 11,
	PANEL_ID_LISTBAR = 12,
	PANEL_ID_MAINSCREEN_RIGHT = 13,
	PANEL_ID_MAINSCREEN_LEFT = 14
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(BUTTON_ID_ADD, MainFrame::OnButtonClickedCreate)
EVT_BUTTON(BUTTON_ID_DELETE, MainFrame::OnButtonClickedDelete)
EVT_BUTTON(BUTTON_ID_COPY, MainFrame::OnButtonClickedCopy)
EVT_BUTTON(BUTTON_ID_EDIT, MainFrame::OnButtonClickedEdit)
EVT_BUTTON(BUTTON_ID_MATFUNC, MainFrame::OnButtonClickedMatFunc)
EVT_BUTTON(BUTTON_ID_DROP, MainFrame::OnButtonClickedDrop)
EVT_BUTTON(BUTTON_ID_SAVE, MainFrame::OnButtonClickedSaveMatrix)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 650)),
	  grid(nullptr),
	  matrixEquationInputChoice(nullptr),
	  equationInputsPanel(nullptr),
	  equationInputsPanelSizer(nullptr),
	  matrixInputChoiceFirst(nullptr),
	  matrixInputChoiceSecound(nullptr),
	  intValueInput(nullptr),
	  floatValueInput(nullptr),
	  saveDataButton(nullptr),
	  newMatrixName(nullptr)
{
	CreateStatusBar();
	SetStatusText("Gotowy");

	// Glowny kontener pionowy
	wxBoxSizer* topBotSizer = new wxBoxSizer(wxVERTICAL);

	// Pasek narzedziowy (ToolBar)
	wxPanel* toolBar = new wxPanel(this, PANEL_ID_TOOLBAR, wxDefaultPosition, wxDefaultSize);
	toolBar->SetBackgroundColour(wxColor(235, 238, 242));

	wxBoxSizer* toolBarSizer = new wxBoxSizer(wxHORIZONTAL);

	wxButton* buttonAdd     = loadAndDisplayButtons(toolBar, BUTTON_ID_ADD,     "icons/add.png",     "Dodaj macierz",      wxDefaultPosition);
	wxButton* buttonDelete  = loadAndDisplayButtons(toolBar, BUTTON_ID_DELETE,  "icons/minus.png",   "Usuń macierz",       wxDefaultPosition);
	wxButton* buttonCopy    = loadAndDisplayButtons(toolBar, BUTTON_ID_COPY,    "icons/copy.png",    "Kopiuj macierz",     wxDefaultPosition);
	wxButton* buttonEdit    = loadAndDisplayButtons(toolBar, BUTTON_ID_EDIT,    "icons/edit.png",    "Edytuj macierz",     wxDefaultPosition);
	wxButton* buttonMatFunc = loadAndDisplayButtons(toolBar, BUTTON_ID_MATFUNC, "icons/mat_func.png", "Działania",       wxDefaultPosition);
	wxButton* buttonDrop    = loadAndDisplayButtons(toolBar, BUTTON_ID_DROP,    "icons/delete.png",  "Wyczyść magazyn",    wxDefaultPosition);
	wxButton* buttonImport  = loadAndDisplayButtons(toolBar, wxID_ANY,          "icons/import.png",  "Import z pliku",     wxDefaultPosition);
	wxButton* buttonExport  = loadAndDisplayButtons(toolBar, wxID_ANY,          "icons/export.png",  "Eksport do pliku",   wxDefaultPosition);

	buttonImport->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClickedImport, this);
	buttonExport->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClickedExport, this);

	toolBarSizer->Add(buttonAdd,     0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonDelete,  0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonCopy,    0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonEdit,    0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonMatFunc, 0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonDrop,    0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonImport,  0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBarSizer->Add(buttonExport,  0, wxALL | wxALIGN_CENTER_VERTICAL, 4);
	toolBar->SetSizer(toolBarSizer);

	topBotSizer->Add(toolBar, 0, wxEXPAND | wxALL, 2);

	// Panel dolny - Lista + Obszar roboczy
	wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);

	// Panel boczny z lista macierzy
	wxPanel* listBar = new wxPanel(this, PANEL_ID_LISTBAR, wxDefaultPosition, wxSize(260, -1));
	listBar->SetBackgroundColour(wxColor(245, 246, 248));

	wxBoxSizer* listBarSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* listTitle = new wxStaticText(listBar, wxID_ANY, "Zapisane macierze:");
	wxFont titleFont = listTitle->GetFont();
	titleFont.SetWeight(wxFONTWEIGHT_BOLD);
	listTitle->SetFont(titleFont);
	listBarSizer->Add(listTitle, 0, wxALL, 6);

	listView = new wxListView(listBar, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_SINGLE_SEL);
	listView->AppendColumn("ID", wxLIST_FORMAT_LEFT, 40);
	listView->AppendColumn("Nazwa", wxLIST_FORMAT_LEFT, 110);
	listView->AppendColumn("Wymiary", wxLIST_FORMAT_LEFT, 80);
	listBarSizer->Add(listView, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
	listBar->SetSizer(listBarSizer);

	contentSizer->Add(listBar, 0, wxEXPAND);

	// Obszar roboczy (lewy panel akcji + prawy panel widoku/siatki)
	wxBoxSizer* workspaceSizer = new wxBoxSizer(wxHORIZONTAL);

	mainScreenLeft = new wxPanel(this, PANEL_ID_MAINSCREEN_LEFT, wxDefaultPosition, wxSize(240, -1));
	mainScreenLeft->SetBackgroundColour(wxColor(248, 249, 250));

	mainScreenRight = new wxPanel(this, PANEL_ID_MAINSCREEN_RIGHT, wxDefaultPosition, wxDefaultSize);
	mainScreenRight->SetBackgroundColour(wxColor(255, 255, 255));

	workspaceSizer->Add(mainScreenLeft, 0, wxEXPAND);
	workspaceSizer->Add(mainScreenRight, 1, wxEXPAND);

	contentSizer->Add(workspaceSizer, 1, wxEXPAND);
	topBotSizer->Add(contentSizer, 1, wxEXPAND);

	SetSizer(topBotSizer);
	loadListView();
}

wxButton* MainFrame::loadAndDisplayButtons(wxPanel* toolBar, const wxWindowID id, const wxString& imagePath, const wxString& label, const wxPoint& pointPosition) {
	if (!wxImage::FindHandler(wxBITMAP_TYPE_PNG)) {
		wxImage::AddHandler(new wxPNGHandler);
	}

	wxImage image;
	bool loaded = false;

	wxArrayString possiblePaths;
	possiblePaths.Add(imagePath);
	possiblePaths.Add("icons/" + wxFileName(imagePath).GetFullName());
	possiblePaths.Add("MatrixCalc-wxWidgets/icons/" + wxFileName(imagePath).GetFullName());
	possiblePaths.Add("../icons/" + wxFileName(imagePath).GetFullName());
	possiblePaths.Add("../../icons/" + wxFileName(imagePath).GetFullName());

	for (const auto& path : possiblePaths) {
		if (wxFileExists(path) && image.LoadFile(path, wxBITMAP_TYPE_PNG)) {
			loaded = true;
			break;
		}
	}

	wxButton* button = nullptr;
	if (loaded) {
		image = image.Scale(36, 36, wxIMAGE_QUALITY_HIGH);
		button = new wxButton(toolBar, id, wxEmptyString, pointPosition, wxSize(46, 46));
		button->SetBitmap(image);
	}
	else {
		button = new wxButton(toolBar, id, label, pointPosition, wxDefaultSize);
	}
	button->SetToolTip(label);
	return button;
}

void MainFrame::loadListView() {
	listView->DeleteAllItems();

	if (Matrices.empty()) {
		SetStatusText("Magazyn macierzy jest pusty");
	}
	else {
		long index = 0;
		for (const auto& matrix : Matrices) {
			wxString MatrixName(matrix.name);
			wxString MatrixSize(wxString::Format("%dx%d", matrix.rows, matrix.cols));
			long itemIndex = listView->InsertItem(index, wxString::Format("%ld", index + 1));
			listView->SetItem(itemIndex, 1, MatrixName);
			listView->SetItem(itemIndex, 2, MatrixSize);
			index++;
		}
		SetStatusText(wxString::Format("Liczba macierzy w magazynie: %zu", Matrices.size()));
	}
}

void MainFrame::OnButtonClickedCreate(wxCommandEvent& evt) {
	SetStatusText("Tworzenie nowej macierzy...");
	ClearMainPanels();

	wxTextEntryDialog nameDialog(this, "Wprowadź nazwę macierzy:", "Nowa macierz", "A");
	if (nameDialog.ShowModal() != wxID_OK) return;

	wxString newMatrixNameTemp = nameDialog.GetValue().Trim();
	if (newMatrixNameTemp.IsEmpty()) {
		ErrorMessageHandler("Nazwa macierzy nie może być pusta.");
		return;
	}
	std::string newMatrixName = std::string(newMatrixNameTemp.mb_str());
	if (matrixEquations.getMatrixByName(newMatrixName) != nullptr) {
		ErrorMessageHandler("Macierz o nazwie '" + newMatrixName + "' już istnieje.");
		return;
	}

	wxTextEntryDialog rowsDialog(this, "Wprowadź liczbę wierszy (1-50):", "Wymiary macierzy", "3");
	if (rowsDialog.ShowModal() != wxID_OK) return;
	long rowsVal = 0;
	if (!rowsDialog.GetValue().ToLong(&rowsVal) || rowsVal <= 0 || rowsVal > 50) {
		ErrorMessageHandler("Nieprawidłowa liczba wierszy (podaj wartość od 1 do 50).");
		return;
	}

	wxTextEntryDialog colsDialog(this, "Wprowadź liczbę kolumn (1-50):", "Wymiary macierzy", "3");
	if (colsDialog.ShowModal() != wxID_OK) return;
	long colsVal = 0;
	if (!colsDialog.GetValue().ToLong(&colsVal) || colsVal <= 0 || colsVal > 50) {
		ErrorMessageHandler("Nieprawidłowa liczba kolumn (podaj wartość od 1 do 50).");
		return;
	}

	int newMatrixRows = static_cast<int>(rowsVal);
	int newMatrixCols = static_cast<int>(colsVal);
	Matrix newMatrix = matrixEquations.createMatrix(newMatrixName, newMatrixRows, newMatrixCols);
	selectedMatrix = matrixEquations.getMatrixByName(newMatrixName);
	DisplayReadDataPanel(newMatrix);
	loadListView();
	SetStatusText("Utworzono macierz '" + newMatrixName + "'");
}

void MainFrame::OnButtonClickedDelete(wxCommandEvent& evt) {
	long selectedItem = -1;
	if (listView != nullptr && listView->GetItemCount() > 0) {
		selectedItem = listView->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	if (selectedItem == -1) {
		wxMessageBox("Najpierw zaznacz macierz na liście po lewej stronie.", "Informacja", wxOK | wxICON_INFORMATION, this);
		return;
	}

	wxString matrixNameTemp = listView->GetItemText(selectedItem, 1);
	std::string matrixName = std::string(matrixNameTemp.mb_str());

	int result = wxMessageBox(wxString::Format("Czy na pewno chcesz usunąć macierz '%s'?", matrixNameTemp),
		"Potwierdzenie usunięcia", wxOK | wxCANCEL | wxICON_QUESTION, this);
	if (result == wxOK) {
		if (selectedMatrix != nullptr && selectedMatrix->name == matrixName) {
			selectedMatrix = nullptr;
		}
		matrixEquations.deleteMatrix(matrixName);
		ClearMainPanels();
		loadListView();
		SetStatusText("Usunięto macierz '" + matrixName + "'");
	}
}

void MainFrame::OnButtonClickedCopy(wxCommandEvent& evt) {
	long selectedItem = -1;
	if (listView != nullptr && listView->GetItemCount() > 0) {
		selectedItem = listView->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	if (selectedItem == -1) {
		wxMessageBox("Najpierw zaznacz macierz na liście po lewej stronie.", "Informacja", wxOK | wxICON_INFORMATION, this);
		return;
	}

	wxString matrixNameInput = listView->GetItemText(selectedItem, 1);
	std::string matrixAName = std::string(matrixNameInput.mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAName);
	if (matrixA == nullptr) {
		ErrorMessageHandler("Nie znaleziono zaznaczonej macierzy.");
		return;
	}

	wxTextEntryDialog dialog(this, "Wprowadź nazwę nowej kopii:", "Kopiowanie macierzy", matrixNameInput + "_kopia");
	if (dialog.ShowModal() == wxID_OK) {
		wxString newMatrixNameInput = dialog.GetValue().Trim();
		if (newMatrixNameInput.IsEmpty()) {
			ErrorMessageHandler("Nazwa macierzy nie może być pusta.");
			return;
		}
		std::string matrixBName = std::string(newMatrixNameInput.mb_str());
		if (matrixEquations.getMatrixByName(matrixBName) == nullptr) {
			matrixEquations.copyMatrix(*matrixA, matrixBName);
			loadListView();
			SetStatusText("Skopiowano macierz jako '" + matrixBName + "'");
		}
		else {
			ErrorMessageHandler("Nazwa '" + matrixBName + "' jest już zajęta.");
		}
	}
}

void MainFrame::OnButtonClickedEdit(wxCommandEvent& evt) {
	long selectedItem = -1;
	if (listView != nullptr && listView->GetItemCount() > 0) {
		selectedItem = listView->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
	}
	if (selectedItem == -1) {
		wxMessageBox("Najpierw zaznacz macierz na liście po lewej stronie.", "Informacja", wxOK | wxICON_INFORMATION, this);
		return;
	}

	wxString matrixNameTemp = listView->GetItemText(selectedItem, 1);
	std::string matrixName = std::string(matrixNameTemp.mb_str());
	Matrix* matrix = matrixEquations.getMatrixByName(matrixName);
	if (matrix != nullptr) {
		selectedMatrix = matrix;
		DisplayReadDataPanel(*matrix);
		SetStatusText("Edycja macierzy '" + matrixName + "'");
	}
	else {
		ErrorMessageHandler("Nie znaleziono zaznaczonej macierzy.");
	}
}

void MainFrame::OnButtonClickedSaveMatrix(wxCommandEvent& evt) {
	if (grid == nullptr || selectedMatrix == nullptr) {
		ErrorMessageHandler("Brak aktywnej macierzy do zapisania.");
		return;
	}

	int rows = grid->GetNumberRows();
	int cols = grid->GetNumberCols();
	std::vector<std::vector<float>> newData(rows, std::vector<float>(cols, 0.0f));

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			wxString cellVal = grid->GetCellValue(i, j);
			double val = 0.0;
			if (!cellVal.ToDouble(&val)) {
				val = 0.0;
			}
			newData[i][j] = static_cast<float>(val);
		}
	}

	selectedMatrix->data = newData;
	matrixEquations.insertIntoMatrix(*selectedMatrix, newData);
	SetStatusText("Zapisano zmiany w macierzy '" + selectedMatrix->name + "'");
	wxMessageBox("Wartości macierzy zostały pomyślnie zaktualizowane.", "Sukces", wxOK | wxICON_INFORMATION, this);
	ClearMainPanels();
	loadListView();
}

void MainFrame::DisplayReadDataPanel(Matrix& matrix) {
	ClearMainPanels();

	// Lewy panel informacyjny
	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* titleText = new wxStaticText(mainScreenLeft, wxID_ANY, "Informacje:");
	wxFont boldFont = titleText->GetFont();
	boldFont.SetWeight(wxFONTWEIGHT_BOLD);
	titleText->SetFont(boldFont);

	std::string info = "Nazwa: " + matrix.name + "\nWymiary: " +
		std::to_string(matrix.rows) + " x " + std::to_string(matrix.cols);
	wxStaticText* infoLabel = new wxStaticText(mainScreenLeft, wxID_ANY, info);

	leftSizer->Add(titleText, 0, wxALL, 8);
	leftSizer->Add(infoLabel, 0, wxLEFT | wxRIGHT | wxBOTTOM, 8);
	leftSizer->AddStretchSpacer();

	wxButton* saveButton = new wxButton(mainScreenLeft, BUTTON_ID_SAVE, "Zapisz macierz");
	leftSizer->Add(saveButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10);
	leftSizer->AddStretchSpacer();
	mainScreenLeft->SetSizer(leftSizer);

	// Prawy panel - Arkusz z siatka
	wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
	grid = new wxGrid(mainScreenRight, wxID_ANY);
	grid->CreateGrid(matrix.rows, matrix.cols);

	for (int i = 0; i < matrix.rows; ++i) {
		for (int j = 0; j < matrix.cols; ++j) {
			grid->SetCellValue(i, j, wxString::Format("%.2f", matrix.data[i][j]));
			grid->SetCellEditor(i, j, new wxGridCellFloatEditor());
			grid->SetCellRenderer(i, j, new wxGridCellFloatRenderer(-1, 2));
		}
	}

	rightSizer->Add(grid, 1, wxEXPAND | wxALL, 6);
	mainScreenRight->SetSizer(rightSizer);

	mainScreenLeft->Layout();
	mainScreenRight->Layout();
}

void MainFrame::OnButtonClickedMatFunc(wxCommandEvent& evt) {
	SetStatusText("Wybór operacji matematycznej");
	ClearMainPanels();

	wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* label = new wxStaticText(mainScreenLeft, wxID_ANY, "Wybierz działanie:");
	wxFont boldFont = label->GetFont();
	boldFont.SetWeight(wxFONTWEIGHT_BOLD);
	label->SetFont(boldFont);
	leftSizer->Add(label, 0, wxALL, 8);

	wxArrayString matrixEquationChoices;
	matrixEquationChoices.Add("1. Dodawanie (A + B)");
	matrixEquationChoices.Add("2. Odejmowanie (A - B)");
	matrixEquationChoices.Add("3. Mnożenie macierzy (A * B)");
	matrixEquationChoices.Add("4. Mnożenie przez skalar (A * k)");
	matrixEquationChoices.Add("5. Potęgowanie macierzy (A^n)");
	matrixEquationChoices.Add("6. Transpozycja (A^T)");
	matrixEquationChoices.Add("7. Wyznacznik det(A)");
	matrixEquationChoices.Add("8. Macierz odwrotna (A^-1)");
	matrixEquationChoices.Add("9. Rząd macierzy rank(A)");

	matrixEquationInputChoice = new wxChoice(mainScreenLeft, wxID_ANY, wxDefaultPosition, wxDefaultSize, matrixEquationChoices);
	leftSizer->Add(matrixEquationInputChoice, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 8);

	equationInputsPanel = new wxPanel(mainScreenLeft, wxID_ANY);
	equationInputsPanelSizer = new wxBoxSizer(wxVERTICAL);
	equationInputsPanel->SetSizer(equationInputsPanelSizer);
	leftSizer->Add(equationInputsPanel, 1, wxEXPAND | wxALL, 4);

	mainScreenLeft->SetSizer(leftSizer);
	matrixEquationInputChoice->Bind(wxEVT_CHOICE, &MainFrame::DisplayEquationOptions, this);

	matrixEquationInputChoice->SetSelection(0);
	wxCommandEvent dummyEvent;
	DisplayEquationOptions(dummyEvent);
}

void MainFrame::OnButtonClickedDrop(wxCommandEvent& evt) {
	if (Matrices.empty()) {
		wxMessageBox("Magazyn macierzy jest już pusty.", "Informacja", wxOK | wxICON_INFORMATION, this);
		return;
	}
	int result = wxMessageBox("Czy na pewno chcesz usunąć WSZYSTKIE macierze z magazynu?",
		"Czyszczenie magazynu", wxOK | wxCANCEL | wxICON_WARNING, this);
	if (result == wxOK) {
		Matrices.clear();
		selectedMatrix = nullptr;
		ClearMainPanels();
		loadListView();
		SetStatusText("Magazyn został wyczyszczony");
	}
}

void MainFrame::OnButtonClickedImport(wxCommandEvent& evt) {
	SetStatusText("Importowanie macierzy...");
	wxFileDialog openFileDialog(this, "Wybierz plik do importu", "", "",
		"Pliki tekstowe (*.txt)|*.txt|Wszystkie pliki (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}
	ImportMatrixToFile(std::string(openFileDialog.GetPath().mb_str()));
}

void MainFrame::OnButtonClickedExport(wxCommandEvent& evt) {
	if (Matrices.empty()) {
		wxMessageBox("Brak macierzy do wyeksportowania.", "Informacja", wxOK | wxICON_INFORMATION, this);
		return;
	}
	SetStatusText("Eksportowanie macierzy...");
	wxFileDialog saveFileDialog(this, "Zapisz macierze do pliku", "", "Macierze.txt",
		"Pliki tekstowe (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	if (saveFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}
	std::string path = std::string(saveFileDialog.GetPath().mb_str());
	if (path.length() >= 4 && path.substr(path.length() - 4) == ".txt") {
		path = path.substr(0, path.length() - 4);
	}
	ExportMatrixToFile(path);
}

void MainFrame::CreateSingleMatrixInput() {
	if (equationInputsPanel == nullptr || equationInputsPanelSizer == nullptr) return;

	wxStaticText* label = new wxStaticText(equationInputsPanel, wxID_ANY, "Wybierz macierz A:");
	equationInputsPanelSizer->Add(label, 0, wxALL, 4);

	wxArrayString choices;
	for (const auto& matrix : Matrices) {
		choices.Add(matrix.name);
	}

	matrixInputChoiceFirst = new wxChoice(equationInputsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	if (!choices.IsEmpty()) {
		matrixInputChoiceFirst->SetSelection(0);
	}
	equationInputsPanelSizer->Add(matrixInputChoiceFirst, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
}

void MainFrame::CreateDualMatrixInput() {
	if (equationInputsPanel == nullptr || equationInputsPanelSizer == nullptr) return;

	wxArrayString choices;
	for (const auto& matrix : Matrices) {
		choices.Add(matrix.name);
	}

	wxStaticText* label1 = new wxStaticText(equationInputsPanel, wxID_ANY, "Wybierz macierz A:");
	equationInputsPanelSizer->Add(label1, 0, wxALL, 4);

	matrixInputChoiceFirst = new wxChoice(equationInputsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	if (!choices.IsEmpty()) {
		matrixInputChoiceFirst->SetSelection(0);
	}
	equationInputsPanelSizer->Add(matrixInputChoiceFirst, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);

	wxStaticText* label2 = new wxStaticText(equationInputsPanel, wxID_ANY, "Wybierz macierz B:");
	equationInputsPanelSizer->Add(label2, 0, wxALL, 4);

	matrixInputChoiceSecound = new wxChoice(equationInputsPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);
	if (choices.GetCount() > 1) {
		matrixInputChoiceSecound->SetSelection(1);
	}
	else if (!choices.IsEmpty()) {
		matrixInputChoiceSecound->SetSelection(0);
	}
	equationInputsPanelSizer->Add(matrixInputChoiceSecound, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
}

void MainFrame::CreateIntInput() {
	if (equationInputsPanel == nullptr || equationInputsPanelSizer == nullptr) return;

	wxStaticText* label = new wxStaticText(equationInputsPanel, wxID_ANY, "Wykładnik potęgi n:");
	equationInputsPanelSizer->Add(label, 0, wxALL, 4);

	intValueInput = new wxTextCtrl(equationInputsPanel, wxID_ANY, "2");
	equationInputsPanelSizer->Add(intValueInput, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
}

void MainFrame::CreateFloatInput() {
	if (equationInputsPanel == nullptr || equationInputsPanelSizer == nullptr) return;

	wxStaticText* label = new wxStaticText(equationInputsPanel, wxID_ANY, "Wartość skalara k:");
	equationInputsPanelSizer->Add(label, 0, wxALL, 4);

	floatValueInput = new wxTextCtrl(equationInputsPanel, wxID_ANY, "2.0");
	equationInputsPanelSizer->Add(floatValueInput, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 6);
}

void MainFrame::CreateSubmitDataButton() {
	if (equationInputsPanel == nullptr || equationInputsPanelSizer == nullptr) return;

	equationInputsPanelSizer->AddSpacer(8);
	saveDataButton = new wxButton(equationInputsPanel, wxID_ANY, "Oblicz wynik");
	equationInputsPanelSizer->Add(saveDataButton, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 6);
}

void MainFrame::ClearMatrixInputs() {
	if (equationInputsPanel != nullptr) {
		equationInputsPanel->DestroyChildren();
		equationInputsPanelSizer = new wxBoxSizer(wxVERTICAL);
		equationInputsPanel->SetSizer(equationInputsPanelSizer);
	}
	matrixInputChoiceFirst = nullptr;
	matrixInputChoiceSecound = nullptr;
	intValueInput = nullptr;
	floatValueInput = nullptr;
	saveDataButton = nullptr;

	mainScreenRight->DestroyChildren();
	mainScreenRight->SetSizer(nullptr);
	grid = nullptr;
	newMatrixName = nullptr;
	mainScreenRight->Layout();
}

void MainFrame::ClearMainPanels() {
	matrixEquationInputChoice = nullptr;
	equationInputsPanel = nullptr;
	equationInputsPanelSizer = nullptr;
	matrixInputChoiceFirst = nullptr;
	matrixInputChoiceSecound = nullptr;
	intValueInput = nullptr;
	floatValueInput = nullptr;
	saveDataButton = nullptr;
	grid = nullptr;
	newMatrixName = nullptr;

	mainScreenLeft->DestroyChildren();
	mainScreenLeft->SetSizer(nullptr);

	mainScreenRight->DestroyChildren();
	mainScreenRight->SetSizer(nullptr);

	mainScreenLeft->Layout();
	mainScreenRight->Layout();
}

void MainFrame::DisplayEquationOptions(wxCommandEvent& evt) {
	if (matrixEquationInputChoice == nullptr) return;

	int selection = matrixEquationInputChoice->GetSelection();
	ClearMatrixInputs();

	switch (selection) {
	case 0:
		CreateDualMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayAddMatrixResult, this);
		break;
	case 1:
		CreateDualMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplaySubMatrixResult, this);
		break;
	case 2:
		CreateDualMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayMultiplyByMatrixResult, this);
		break;
	case 3:
		CreateSingleMatrixInput();
		CreateFloatInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayMultiplyByValueResult, this);
		break;
	case 4:
		CreateSingleMatrixInput();
		CreateIntInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayPowerOfMatrixResult, this);
		break;
	case 5:
		CreateSingleMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayTransposeResult, this);
		break;
	case 6:
		CreateSingleMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayDeterminantResult, this);
		break;
	case 7:
		CreateSingleMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayInverseResult, this);
		break;
	case 8:
		CreateSingleMatrixInput();
		CreateSubmitDataButton();
		if (saveDataButton) saveDataButton->Bind(wxEVT_BUTTON, &MainFrame::DisplayRankResult, this);
		break;
	default:
		break;
	}

	if (equationInputsPanel != nullptr) {
		equationInputsPanel->Layout();
	}
	mainScreenLeft->Layout();
}

void MainFrame::DisplayAddMatrixResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr || matrixInputChoiceSecound == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	std::string matrixBstring = std::string(matrixInputChoiceSecound->GetStringSelection().mb_str());

	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);
	Matrix* matrixB = matrixEquations.getMatrixByName(matrixBstring);

	if (matrixA != nullptr && matrixB != nullptr) {
		Matrix matrixResult = matrixEquations.addMatrix(*matrixA, *matrixB);
		if (matrixResult.name != "matrixReadFail") {
			DisplayMatrixResult(matrixResult);
			SetStatusText("Obliczono: " + matrixAstring + " + " + matrixBstring);
		}
		else {
			ErrorMessageHandler("Niezgodne wymiary macierzy. Dodawanie wymaga macierzy o identycznych wymiarach.");
		}
	}
	else {
		ErrorMessageHandler("Wybierz obie macierze z listy.");
	}
}

void MainFrame::DisplaySubMatrixResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr || matrixInputChoiceSecound == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	std::string matrixBstring = std::string(matrixInputChoiceSecound->GetStringSelection().mb_str());

	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);
	Matrix* matrixB = matrixEquations.getMatrixByName(matrixBstring);

	if (matrixA != nullptr && matrixB != nullptr) {
		Matrix matrixResult = matrixEquations.subtractMatrix(*matrixA, *matrixB);
		if (matrixResult.name != "matrixReadFail") {
			DisplayMatrixResult(matrixResult);
			SetStatusText("Obliczono: " + matrixAstring + " - " + matrixBstring);
		}
		else {
			ErrorMessageHandler("Niezgodne wymiary macierzy. Odejmowanie wymaga macierzy o identycznych wymiarach.");
		}
	}
	else {
		ErrorMessageHandler("Wybierz obie macierze z listy.");
	}
}

void MainFrame::DisplayMultiplyByMatrixResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr || matrixInputChoiceSecound == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	std::string matrixBstring = std::string(matrixInputChoiceSecound->GetStringSelection().mb_str());

	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);
	Matrix* matrixB = matrixEquations.getMatrixByName(matrixBstring);

	if (matrixA != nullptr && matrixB != nullptr) {
		Matrix matrixResult = matrixEquations.multiplyMatrix(*matrixA, *matrixB);
		if (matrixResult.name != "matrixReadFail") {
			DisplayMatrixResult(matrixResult);
			SetStatusText("Obliczono: " + matrixAstring + " * " + matrixBstring);
		}
		else {
			ErrorMessageHandler("Niezgodne wymiary macierzy. Liczba kolumn pierwszej macierzy musi być równa liczbie wierszy drugiej.");
		}
	}
	else {
		ErrorMessageHandler("Wybierz obie macierze z listy.");
	}
}

void MainFrame::DisplayMultiplyByValueResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr || floatValueInput == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);

	double doubleValue = 1.0;
	if (!floatValueInput->GetValue().ToDouble(&doubleValue)) {
		doubleValue = 1.0;
	}

	if (matrixA != nullptr) {
		Matrix matrixResult = matrixEquations.multiplyMatrix(*matrixA, static_cast<float>(doubleValue));
		DisplayMatrixResult(matrixResult);
		SetStatusText(wxString::Format("Pomnożono macierz %s przez skalar %.2f", matrixAstring.c_str(), doubleValue));
	}
	else {
		ErrorMessageHandler("Wybierz macierz z listy.");
	}
}

void MainFrame::DisplayPowerOfMatrixResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr || intValueInput == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);

	long intValue = 1;
	if (!intValueInput->GetValue().ToLong(&intValue) || intValue < 1) {
		intValue = 1;
	}

	if (matrixA != nullptr) {
		Matrix matrixResult = matrixEquations.powerOfMatrix(*matrixA, static_cast<int>(intValue));
		DisplayMatrixResult(matrixResult);
		SetStatusText(wxString::Format("Podniesiono macierz %s do potęgi %ld", matrixAstring.c_str(), intValue));
	}
	else {
		ErrorMessageHandler("Wybierz macierz z listy.");
	}
}

void MainFrame::DisplayTransposeResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);

	if (matrixA != nullptr) {
		Matrix matrixResult = matrixEquations.transposeMatrix(*matrixA);
		DisplayMatrixResult(matrixResult);
		SetStatusText("Wyznaczono transpozycję macierzy " + matrixAstring);
	}
	else {
		ErrorMessageHandler("Wybierz macierz z listy.");
	}
}

void MainFrame::DisplayDeterminantResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);

	if (matrixA != nullptr) {
		if (matrixA->rows != matrixA->cols) {
			ErrorMessageHandler("Wyznacznik można obliczyć wyłącznie dla macierzy kwadratowych (wiersze = kolumny).");
			return;
		}
		float floatResult = matrixEquations.detMatrix(*matrixA);
		if (floatResult != 9999) {
			DisplayValueResult(floatResult, matrixAstring);
			SetStatusText("Obliczono wyznacznik macierzy " + matrixAstring);
		}
		else {
			ErrorMessageHandler("Błąd podczas obliczania wyznacznika.");
		}
	}
	else {
		ErrorMessageHandler("Wybierz macierz z listy.");
	}
}

void MainFrame::DisplayInverseResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);

	if (matrixA != nullptr) {
		if (matrixA->rows != matrixA->cols) {
			ErrorMessageHandler("Macierz odwrotną można wyznaczyć wyłącznie dla macierzy kwadratowych.");
			return;
		}
		Matrix matrixResult = matrixEquations.inverseMatrix(*matrixA);
		if (matrixResult.name != "matrixReadFail") {
			DisplayMatrixResult(matrixResult);
			SetStatusText("Wyznaczono macierz odwrotną do " + matrixAstring);
		}
		else {
			ErrorMessageHandler("Nie można odwrócić tej macierzy (wyznacznik jest równy 0 lub błąd wymiarów).");
		}
	}
	else {
		ErrorMessageHandler("Wybierz macierz z listy.");
	}
}

void MainFrame::DisplayRankResult(wxCommandEvent& evt) {
	if (matrixInputChoiceFirst == nullptr) return;

	std::string matrixAstring = std::string(matrixInputChoiceFirst->GetStringSelection().mb_str());
	Matrix* matrixA = matrixEquations.getMatrixByName(matrixAstring);

	if (matrixA != nullptr) {
		int intResult = matrixEquations.rankMatrix(*matrixA);
		DisplayValueResult(intResult, matrixAstring);
		SetStatusText("Obliczono rząd macierzy " + matrixAstring);
	}
	else {
		ErrorMessageHandler("Wybierz macierz z listy.");
	}
}

void MainFrame::DisplayMatrixResult(Matrix matrix) {
	mainScreenRight->DestroyChildren();
	mainScreenRight->SetSizer(nullptr);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

	wxStaticText* header = new wxStaticText(mainScreenRight, wxID_ANY, "Wynik operacji:");
	wxFont headerFont = header->GetFont();
	headerFont.SetWeight(wxFONTWEIGHT_BOLD);
	header->SetFont(headerFont);
	mainSizer->Add(header, 0, wxALL, 6);

	grid = new wxGrid(mainScreenRight, wxID_ANY);
	grid->CreateGrid(matrix.rows, matrix.cols);
	for (int i = 0; i < matrix.rows; ++i) {
		for (int j = 0; j < matrix.cols; ++j) {
			grid->SetCellValue(i, j, wxString::Format("%.2f", matrix.data[i][j]));
			grid->SetCellEditor(i, j, new wxGridCellFloatEditor());
			grid->SetCellRenderer(i, j, new wxGridCellFloatRenderer(-1, 2));
		}
	}
	mainSizer->Add(grid, 1, wxEXPAND | wxALL, 6);

	wxBoxSizer* saveSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* nameLabel = new wxStaticText(mainScreenRight, wxID_ANY, "Zapisz wynik jako:");
	saveSizer->Add(nameLabel, 0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 6);

	newMatrixName = new wxTextCtrl(mainScreenRight, wxID_ANY, "Wynik_" + matrix.name);
	saveSizer->Add(newMatrixName, 1, wxEXPAND | wxRIGHT, 6);

	wxButton* saveButton = new wxButton(mainScreenRight, wxID_ANY, "Zapisz do magazynu");
	saveButton->Bind(wxEVT_BUTTON, &MainFrame::QuickSaveHandler, this);
	saveSizer->Add(saveButton, 0, wxALIGN_CENTER_VERTICAL);

	mainSizer->Add(saveSizer, 0, wxEXPAND | wxALL, 6);
	mainScreenRight->SetSizer(mainSizer);

	resultMatrix = matrix;
	mainScreenRight->Layout();
}

void MainFrame::QuickSaveHandler(wxCommandEvent& evt) {
	if (newMatrixName == nullptr) return;

	wxString wxStringMatrixName = newMatrixName->GetValue().Trim();
	if (wxStringMatrixName.IsEmpty()) {
		ErrorMessageHandler("Wprowadź nazwę macierzy.");
		return;
	}

	std::string newName = std::string(wxStringMatrixName.mb_str());
	if (matrixEquations.getMatrixByName(newName) == nullptr) {
		matrixEquations.quickSaveMatrix(resultMatrix, newName);
		loadListView();
		SetStatusText("Zapisano macierz wynikową pod nazwą '" + newName + "'");
		wxMessageBox("Macierz wynikowa została pomyślnie dodana do magazynu.", "Sukces", wxOK | wxICON_INFORMATION, this);
	}
	else {
		ErrorMessageHandler("Nazwa '" + newName + "' jest już zajęta.");
	}
}

void MainFrame::DisplayValueResult(float FloatResult, std::string matrixName) {
	mainScreenRight->DestroyChildren();
	mainScreenRight->SetSizer(nullptr);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* header = new wxStaticText(mainScreenRight, wxID_ANY, "Wynik obliczeń:");
	wxFont font = header->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(font.GetPointSize() + 2);
	header->SetFont(font);
	sizer->Add(header, 0, wxALL, 12);

	std::string displayInfo = "Macierz: " + matrixName + "\nWartość: " + std::to_string(FloatResult);
	wxStaticText* resultData = new wxStaticText(mainScreenRight, wxID_ANY, displayInfo);
	resultData->SetFont(font);
	sizer->Add(resultData, 0, wxALL, 12);

	mainScreenRight->SetSizer(sizer);
	mainScreenRight->Layout();
}

void MainFrame::DisplayValueResult(int IntResult, std::string matrixName) {
	mainScreenRight->DestroyChildren();
	mainScreenRight->SetSizer(nullptr);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticText* header = new wxStaticText(mainScreenRight, wxID_ANY, "Wynik obliczeń:");
	wxFont font = header->GetFont();
	font.SetWeight(wxFONTWEIGHT_BOLD);
	font.SetPointSize(font.GetPointSize() + 2);
	header->SetFont(font);
	sizer->Add(header, 0, wxALL, 12);

	std::string displayInfo = "Macierz: " + matrixName + "\nRząd macierzy: " + std::to_string(IntResult);
	wxStaticText* resultData = new wxStaticText(mainScreenRight, wxID_ANY, displayInfo);
	resultData->SetFont(font);
	sizer->Add(resultData, 0, wxALL, 12);

	mainScreenRight->SetSizer(sizer);
	mainScreenRight->Layout();
}

void MainFrame::ExportMatrixToFile(std::string fileName) {
	std::ofstream file;
	file.open(fileName + ".txt");
	if (!file.is_open()) {
		ErrorMessageHandler("Nie można otworzyć pliku do zapisu: " + fileName);
		return;
	}

	for (Matrix& matrix : Matrices) {
		file << "Matrix name:" << matrix.name << "\n";
		file << matrix.cols << "\n";
		file << matrix.rows << "\n";
		for (int i = 0; i < matrix.rows; i++) {
			for (int j = 0; j < matrix.cols; j++) {
				file << matrix.data[i][j];
				if (j != matrix.cols - 1 || i != matrix.rows - 1) {
					file << ',';
				}
			}
		}
		file << "\n";
	}
	file.close();
	SetStatusText("Pomyślnie wyeksportowano macierze");
	wxMessageBox("Macierze zostały pomyślnie zapisane do pliku.", "Eksport zakończony", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::ImportMatrixToFile(std::string filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		ErrorMessageHandler("Nie można otworzyć pliku do odczytu!");
		return;
	}

	std::string line;
	int importedCount = 0;
	while (std::getline(file, line)) {
		if (line.empty()) continue;
		if (line.substr(0, 12) == "Matrix name:") {
			std::string matrixName = line.substr(12);
			int numCols = 0, numRows = 0;

			if (!std::getline(file, line)) break;
			try { numCols = std::stoi(line); } catch (...) { break; }

			if (!std::getline(file, line)) break;
			try { numRows = std::stoi(line); } catch (...) { break; }

			if (!std::getline(file, line)) break;

			if (numRows <= 0 || numCols <= 0 || numRows > 100 || numCols > 100) continue;

			Matrix matrix(matrixName, numRows, numCols);
			matrix.data.assign(numRows, std::vector<float>(numCols, 0.0f));

			std::stringstream ss(line);
			std::string cell;
			int rowIndex = 0;
			int colIndex = 0;

			while (std::getline(ss, cell, ',')) {
				if (!cell.empty()) {
					try {
						float val = std::stof(cell);
						if (rowIndex < numRows && colIndex < numCols) {
							matrix.data[rowIndex][colIndex] = val;
						}
					}
					catch (...) {}
				}
				colIndex++;
				if (colIndex >= numCols) {
					colIndex = 0;
					rowIndex++;
				}
			}

			// Jesli macierz o tej nazwie istnieje, dodajemy sufiks
			std::string finalName = matrixName;
			int suffix = 1;
			while (matrixEquations.getMatrixByName(finalName) != nullptr) {
				finalName = matrixName + "_" + std::to_string(suffix++);
			}
			matrix.name = finalName;

			Matrices.push_back(matrix);
			importedCount++;
		}
	}
	file.close();
	loadListView();
	SetStatusText(wxString::Format("Zaimportowano macierzy: %d", importedCount));
	wxMessageBox(wxString::Format("Zaimportowano %d macierzy z pliku.", importedCount), "Import zakończony", wxOK | wxICON_INFORMATION, this);
}

void MainFrame::ErrorMessageHandler(const std::string& errorMessage) {
	SetStatusText("Błąd: " + errorMessage);
	wxMessageBox(errorMessage, "Błąd", wxOK | wxICON_ERROR, this);
}
