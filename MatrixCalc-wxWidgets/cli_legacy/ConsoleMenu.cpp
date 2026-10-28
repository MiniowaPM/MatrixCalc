#include "MatrixCalc_Equations.h"

class ConsoleMenu {
public:
	matrixEquations calc;
	vector<Matrix> matrices;

	// Funkcja pustÄ… tworzÄ…ca nowÄ… macierz
	void createMatrix(string name, int rows, int cols){
		Matrix matrix(name, rows, cols);
		matrix.data.assign(rows, vector<float>(cols, 0.0));
		matrices.push_back(matrix);
	};
	// Szybki zapis macierzy
	void quickSaveMatrix(Matrix& curMatrix, string name) {
		Matrix matrix(name, curMatrix.rows, curMatrix.cols);
		matrix.data = curMatrix.data;
		matrices.push_back(matrix);
	}
	// Funkcja kopiujÄ…ca macierz z A do B
	void copyMatrix(Matrix& matrixA, Matrix& matrixB) {
		matrixB = matrixA;
	};
	// Funkcja zmiany wartoĹ›ci danej macierzy
	void editMatrix(Matrix& matrix, int selectedRow, int selectedCol) {
		if (selectedCol <= matrix.cols and selectedRow <= matrix.rows){
			for (int i = 0; i < matrix.cols; i++) {
				for (int j = 0; j < matrix.rows; j++) {
					if (selectedCol == i and selectedRow == j) {
						float value;
						cin >> value;
						cin.ignore();
						if (typeid(value) == typeid(float)) {
							matrix.data[j][i] = value;
						}
						else {
							cout << "Wprowadzono wartoĹ›Ä‡ o nie poprawnym typie danych";
							cin;
							cin.ignore();
							return;
						}
					}
				}
			}
		}
		else{
			cout << "Ĺąle wprowadzone dane. Nie istnieje taka komĂłrka.";
		}
	};
	// Funkcja wprowadzajÄ…ca dane do wybranej macierzy
	void insertIntoMatrix(Matrix& matrix) {
		for (int i = 0; i < matrix.cols; i++) {
			for (int j = 0; j < matrix.rows; j++) {
				float value;
				cout << "Pozycja " << j + 1 << "x" << i + 1 << " : ";
				cin >> value;
				cin.ignore();
				if (typeid(value) == typeid(float)) {
					matrix.data[j][i] = value;
				}
				else {
					cout << "Wprowadzono wartoĹ›Ä‡ o nie poprawnym typie danych";
					cin;
					cin.ignore();
					return;
				}
			}
		}
	}
	// Funkcaj wyĹ›wietlajÄ…ca nazwy stworzonych macierzy
	void listMatrices() {
		if (matrices.empty()) {
			cout << "Brak macierzy w magazynie \n";
		}
		else {
			cout << "Lista macierzy w magazynie: \n";
			for (auto& matrix : matrices) {
				cout << "\tNazwa: " << matrix.name << ", Rozmiar: " << matrix.rows << "x" << matrix.cols << "\n";
			}
		}
	};
	// Funkcja usuwajÄ…ca pojedynczy macierz
	void deleteMatrix(string name) {
		for (auto i = matrices.begin(); i != matrices.end(); ++i) {
			if (i->name == name){
				matrices.erase(i);
				cout << "Macierz o nazwie '" << name << "' zostaĹ‚a usuniÄ™ta.";
				return;
			}
		}
		cout << "Macierz o nazwie '" << name << "' nie istnieje. ProszÄ™ wprowadziÄ‡ prawidĹ‚owÄ… nazwÄ™.";
	};
	// Main Menu
	void mainMenu() {
		while (true) {
			system("cls");
			cout << "Kalkulator macierzy\n\nWybierz jednÄ… z poniĹĽszych opcji:\n";
			cout << "1. StwĂłrz macierz\n";
			cout << "2. WyĹ›wietl listÄ™ nazw zapisanych macierzy\n";
			cout << "3. Skopiuj macierz\n";
			cout << "4. Wprowadz dane do macierza\n";
			cout << "5. Edytuj dane w macierzu\n";
			cout << "6. UsuĹ„ pojedynczÄ… macierz z magazynu\n";
			cout << "7. UsuĹ„ wszystkie macierz z magazynu\n";
			cout << "8. DziaĹ‚ania na macierzach\n";
			cout << "9. ZakoĹ„cz dziaĹ‚anie programu\n\n";
			cout << "WybĂłr: ";
			int usrInput = -1;
			cin >> usrInput;
			cin.ignore();
			system("cls");
			switch (usrInput) {
				case 1: {
					int inputRow = -1, inputCol = -1;
					string inputName;
					cout << "WprowadĹş nazwÄ™ macierzy: ";
					cin >> inputName;
					cin.ignore();
					while (inputCol < 0 and inputRow < 0){
						cout << "WprowadĹş wymiary macierzy\n\tWporwadĹş iloĹ›Ä‡ rzÄ™dĂłw: ";
						cin >> inputRow;
						cin.ignore();
						cout << "\tWporwadĹş iloĹ›Ä‡ kolumn: ";
						cin >> inputCol;
						cin.ignore();
					}
					createMatrix(inputName, inputRow, inputCol);
					break;
				}
				case 2: {
					listMatrices();
					cin;
					cin.ignore();
					break;
				}
				case 3: {
					string inputNameA, inputNameB;
					cout << "WprowadĹş nazwÄ™ macierzy, ktĂłrÄ… chcesz skopiowaÄ‡: ";
					cin >> inputNameA;
					cin.ignore();
					cout << "\nWprowadĹş nazwÄ™ macierzy, do ktĂłrego chcesz skopiowaÄ‡: ";
					cin >> inputNameB;
					cin.ignore();
					auto source = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == inputNameA; });
					auto target = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == inputNameB; });
					if (source != matrices.end() and target != matrices.end()) {
						copyMatrix(*source, *target);
						cout << "\nMacierz zostaĹ‚a skopiowana.";
					}
					else{
						cout << "\nNie znaleĹşono tych macierzy.";
					}
					cin;
					cin.ignore();
					break;
				}
				case 4: {
					string inputName;
					cout << "WprowaĹş nazwÄ™ macierza, do ktĂłrego chcesz wprowadziÄ‡ dane: ";
					cin >> inputName;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == inputName; });
					if (typeid(*selectedMatrix) == typeid(Matrix)) {
						insertIntoMatrix(*selectedMatrix);
					}
					else {
						cout << "\nNie istnieje macierz o tej nazwie.";
					}
					break;
				}
				case 5: {
					int selectedRow, selectedCol;
					string inputName;
					cout << "WprowaĹş nazwÄ™ macierza, ktĂłry chcesz edytowaÄ‡: ";
					cin >> inputName;
					cin.ignore();
					cout << "WprowadĹş pozycjÄ™ macierzu ktĂłrÄ… chcesz edytowaÄ‡";
					cout << "\n\tWprowadz rzÄ…d: ";
					cin >> selectedRow;
					cin.ignore();
					cout << "\tWprowadz kolumnÄ™: ";
					cin >> selectedCol;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == inputName; });
					if (typeid(selectedCol) == typeid(int) and typeid(selectedRow) == typeid(int) and typeid(*selectedMatrix) == typeid(Matrix)){
						editMatrix(*selectedMatrix, selectedRow - 1, selectedCol - 1);
					}
					else {
						cout << "Wprowadzono nie prawidĹ‚owy typ danych rzÄ™du lub/i kolumny lub nie istnieje macierz o tej nazwie";
						cin;
						cin.ignore();
					}
					break;
				}
				case 6: {
					string inputName;
					cout << "Wybierz macierz, ktĂłrÄ… chcesz usunÄ…Ä‡: ";
					cin >> inputName;
					cin.ignore();
					deleteMatrix(inputName);
					cin;
					cin.ignore();
					break;
				}
				case 7: {
					string inputChoise;
					cout << "Czy na pewno chcesz usunÄ…Ä‡ wszystkie macierze?! (TAK/tak): ";
					cin >> inputChoise;
					cin.ignore();
					if (inputChoise == "TAK" or inputChoise == "tak") {
						matrices.clear();
					}
					break;
				}
				case 8: {
					equationsMenu();
					break;
				}
				case 9: {
					exit(0);
				}
				default:
					cout << "NieprawidĹ‚owy wybĂłr. ProszÄ™ wybraÄ‡ jeden z istniejÄ…cych";
					break;
			};
		};
	};
	// Funkcja save/display result
	void saveDisplayResult(Matrix result) {
		cout << "1. Zapisz wynik na nowej macierzy\n";
		cout << "2. WyĹ›wietl wynik\n";
		cout << "Wybierz dziaĹ‚anie, ktĂłre chcesz przeprowadziÄ‡: ";
		int displayChoise = -1;
		cin >> displayChoise;
		cin.ignore();
		if (displayChoise == 1) {
			cout << "WprowadĹş nazwÄ™ macierzy zawierajÄ…cej wynik tego obliczenia: ";
			string resultName;
			cin >> resultName;
			cin.ignore();
			quickSaveMatrix(result, resultName);
			cout << "Wynik zostaĹ‚ zapisany na macierzy " << resultName;
		}
		else if (displayChoise == 2) {
			calc.displayMatrix(result);
		}
		else {
			cout << "NieprawidĹ‚owy wybĂłr. ProszÄ™ wybraÄ‡ jeden z istniejÄ…cych";
		}
		cin;
		cin.ignore();
	};
	// Menu dziaĹ‚aĹ„
	void equationsMenu() {
		while (true){
			system("cls");
			cout << "Kalkulator macierzy\n\n";

			cout << "1. WyĹ›wietl macierz\n";
			cout << "2. Dodaj macierze\n";
			cout << "3. Odejmij macierze\n";
			cout << "4. PrzemnĂłrz macierze\n";
			cout << "5. PrzemnĂłrz macierz przez wartoĹ›Ä‡\n";
			cout << "6. PotÄ™gowanie macierzy\n";
			cout << "7. WyĹ›wietl macierz transponowanÄ…\n";
			cout << "8. WyĹ›wietl wyznacznik macierzy\n";
			cout << "9. Oblicz macierz odwrotnÄ…\n";
			cout << "10. WyĹ›wietl macierz rzÄ™du\n";
			cout << "11. WrĂłÄ‡ do menu gĹ‚Ăłwnego\n";

			cout << "Wybierz dziaĹ‚anie, ktĂłre chcesz przeprowadziÄ‡: ";
			int usrInput = -1;
			cin >> usrInput;
			system("cls");
			switch (usrInput) {
				case 1: {
					cout << "WyĹ›wietl macierz, ktĂłrÄ… chcesz wyĹ›wietlÄ‡: ";
					string inputName;
					cin >> inputName;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == inputName; });
					if (typeid(*selectedMatrix) == typeid(Matrix)) {
						calc.displayMatrix(*selectedMatrix);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tej nazwie.";
					}
					cin;
					cin.ignore();
					break;
				}
				case 2: {
					string matrixA, matrixB;
					cout << "\tDodawanie macierzy \n\n";
					cout << "Wprowadz pierwszÄ… macierz: ";
					cin >> matrixA;
					cin.ignore();
					cout << "WprowadĹş drugÄ… macierz: ";
					cin >> matrixB;
					cin.ignore();
					auto selectedMatrixA = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					auto selectedMatrixB = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixB; });
					if (typeid(*selectedMatrixA) == typeid(Matrix) and typeid(*selectedMatrixB) == typeid(Matrix)) {
						Matrix result = calc.addMatrix(*selectedMatrixA, *selectedMatrixB);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tych nazwach.";
					}
					break;
				}
				case 3: {
					string matrixA, matrixB;
					int displayChoise = -1;
					cout << "\tOdejmowanie macierzy \n\n";
					cout << "Wprowadz pierwszÄ… macierz: ";
					cin >> matrixA;
					cin.ignore();
					cout << "WprowadĹş drugÄ… macierz: ";
					cin >> matrixB;
					cin.ignore();
					auto selectedMatrixA = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					auto selectedMatrixB = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixB; });
					if (typeid(*selectedMatrixA) == typeid(Matrix) and typeid(*selectedMatrixB) == typeid(Matrix)) {
						Matrix result = calc.subtractMatrix(*selectedMatrixA, *selectedMatrixB);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tych nazwach.";
					}
					break;
				}
				case 4: {
					string matrixA, matrixB;
					int displayChoise = -1;
					cout << "\tPrzemnĂłrz macierze \n\n";
					cout << "Wprowadz pierwszÄ… macierz: ";
					cin >> matrixA;
					cin.ignore();
					cout << "WprowadĹş drugÄ… macierz: ";
					cin >> matrixB;
					cin.ignore();
					auto selectedMatrixA = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					auto selectedMatrixB = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixB; });
					if (typeid(*selectedMatrixA) == typeid(Matrix) and typeid(*selectedMatrixB) == typeid(Matrix)) {
						Matrix result = calc.multiplyMatrix(*selectedMatrixA, *selectedMatrixB);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tych nazwach.";
					}
					break;
				}
				case 5: {
					string matrixA;
					float multiplier;
					cout << "\tPrzemnĂłrz macierze \n\n";
					cout << "Wprowadz nazwÄ™ macierzy: ";
					cin >> matrixA;
					cin.ignore();
					cout << "WprowadĹş liczbÄ™ przez ktĂłrÄ… chcesz pomnorzyÄ‡ macierz: ";
					cin >> multiplier;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					if (typeid(*selectedMatrix) == typeid(Matrix) and typeid(multiplier) == typeid(int)) {
						Matrix result = calc.multiplyMatrix(*selectedMatrix, multiplier);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tych nazwach.";
					}
					break;
				}
				case 6: {
					string matrixA;
					int power;
					cout << "\tPotÄ™gowanie macierzy\n\n";
					cout << "Wprowadz nazwÄ™ macierzy: ";
					cin >> matrixA;
					cin.ignore();
					cout << "WprowadĹş potÄ™ge macierzy: ";
					cin >> power;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					if (typeid(*selectedMatrix) == typeid(Matrix) and typeid(power) == typeid(int)) {
						Matrix result = calc.powerOfMatrix(*selectedMatrix, power);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tych nazwach.";
					}
					break;
				}
				case 7: {
					string matrixA;
					cout << "\tWyĹ›wietl macierz transponowanÄ…\n\n";
					cout << "Wprowadz nazwÄ™ macierzy: ";
					cin >> matrixA;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					if (typeid(*selectedMatrix) == typeid(Matrix)) {
						Matrix result = calc.transposeMatrix(*selectedMatrix);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tych nazwach.";
					}
					break;
				}
				case 8: {
					string matrixA;
					cout << "\tWyĹ›wietl wyznacznik macierzy\n\n";
					cout << "Wprowadz nazwÄ™ macierzy: ";
					cin >> matrixA;
					cin.ignore();
					auto selectedMatrixA = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					if (typeid(selectedMatrixA) == typeid(Matrix)) {
						cout << "Wyznacznik macierzy: " << calc.detMatrix(*selectedMatrixA);
					}
					else {
						cout << "Nie istnieje macierz o tej nazwie.";
					}
					cin;
					cin.ignore();
					break;
				}
				case 9: {
					string matrixA;
					cout << "\tOblicz macierz odwrotnÄ…\n\n";
					cin >> matrixA;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					if (typeid(*selectedMatrix) == typeid(Matrix)) {
						Matrix result = calc.inverseMatrix(*selectedMatrix);
						saveDisplayResult(result);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tej nazwie.";
					}
					break;
				}
				case 10: {
					string matrixA;
					cout << "\tWyĹ›wietl macierz rzÄ™du\n\n";
					cout << "Wprowadz nazwÄ™ macierzy: ";
					cin >> matrixA;
					cin.ignore();
					auto selectedMatrix = find_if(matrices.begin(), matrices.end(), [&](const Matrix& matrix) { return matrix.name == matrixA; });
					if (typeid(*selectedMatrix) == typeid(Matrix)) {
						cout << "Wyznacznik macierzy: " << calc.rankMatrix(*selectedMatrix);
					}
					else {
						cout << "\nNie znaleĹşono macierzy o tej nazwie.";
					}
					cin;
					cin.ignore();
					break;
				}
				case 11: {
					mainMenu();
					break;
				}
				default: {
					cout << "NieprawidĹ‚owy wybĂłr. ProszÄ™ wybraÄ‡ jeden z istniejÄ…cych";
					break;
				}
			}
		}
	};
};

int main() {
	setlocale(LC_ALL, "pl_PL");
	system("cls");
	ConsoleMenu menu;
	menu.mainMenu();
	return 0;
};
