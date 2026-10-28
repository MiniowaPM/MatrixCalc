# MatrixCalc (wxWidgets GUI & CLI)

Desktopowa aplikacja kalkulatora macierzy z graficznym interfejsem użytkownika (GUI) opartym na bibliotece **wxWidgets** oraz z modułem konsolowym (CLI). Projekt zrealizowany w języku C++ w ramach przedmiotu *Metody Programowania* na Politechnice Morskiej w Szczecinie.

---

## Spis treści
- [Funkcjonalności](#funkcjonalności)
- [Architektura i struktura projektu](#architektura-i-struktura-projektu)
- [Wymagania systemowe](#wymagania-systemowe)
- [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
  - [Opcja 1: CMake + vcpkg (Zalecane)](#opcja-1-cmake--vcpkg-zalecane)
  - [Opcja 2: Visual Studio 2022](#opcja-2-visual-studio-2022)
  - [Wersja konsolowa (CLI)](#wersja-konsolowa-cli)
- [Obsługa programu](#obsługa-programu)
- [Materiały i założenia](#materiały-i-założenia)

---

## Funkcjonalności

### 1. Zarządzanie macierzami w magazynie
- **Tworzenie macierzy**: Definiowanie własnych wymiarów ($M \times N$) oraz nazwy.
- **Edycja wartości**: Interaktywny arkusz tabelaryczny zrealizowany za pomocą `wxGrid`.
- **Kopiowanie i klonowanie**: Możliwość powielania macierzy pod nową nazwą.
- **Szybki zapis**: Zapisywanie wyników operacji bezpośrednio do magazynu macierzy.
- **Usuwanie**: Kasowanie pojedynczych macierzy lub czyszczenie całego magazynu.
- **Import / Eksport**: Zapis macierzy do plików tekstowych oraz odczyt z dysku.

### 2. Operacje algebraiczne
Aplikacja implementuje silnik obliczeniowy `MatrixEquations` realizujący:
- **Dodawanie macierzy**: $C = A + B$ (dla macierzy o zgodnych wymiarach)
- **Odejmowanie macierzy**: $C = A - B$
- **Mnożenie macierzy**: $C = A \times B$ ($A_{m \times k} \cdot B_{k \times n}$)
- **Mnożenie przez skalar**: $C = k \cdot A$ ($k \in \mathbb{R}$)
- **Potęgowanie macierzy**: $A^n$
- **Transpozycja macierzy**: $A^T$
- **Wyznacznik macierzy**: $\det(A)$ metodą rozwinięcia Laplace'a
- **Macierz odwrotna**: $A^{-1}$
- **Rząd macierzy**: $\text{rank}(A)$

---

## Architektura i struktura projektu

Projekt został podzielony na warstwę interfejsu użytkownika, logikę obliczeniową oraz moduł persystencji:

```text
MatrixCalc-wxWidgets/
├── CMakeLists.txt              # Konfiguracja budowania CMake dla GUI i CLI
├── README.md                   # Niniejsza dokumentacja
├── assets/                     # Zasoby projektowe
├── icons/                      # Ikony paska narzędzi GUI (add, minus, copy, itp.)
├── include/                    # Pliki nagłówkowe C++
│   ├── App.h                   # Klasa główna aplikacji (wxApp)
│   ├── Globals.h               # Współdzielone struktury danych (Matrix, pamięć magazynu)
│   ├── MainFrame.h             # Główne okno aplikacji, obsługa zdarzeń i sizerów
│   └── MatrixEquations.h       # Deklaracja silnika obliczeniowego
├── src/                        # Pliki źródłowe C++
│   ├── App.cpp                 # Punkt wejścia aplikacji (wxIMPLEMENT_APP)
│   ├── MainFrame.cpp           # Implementacja interfejsu (wxGrid, wxChoice, pasek narzędzi)
│   └── MatrixEquations.cpp     # Implementacja operacji algebraicznych
├── cli_legacy/                 # Wersja konsolowa projektu
│   ├── ConsoleMenu.cpp         # Menu w konsoli tekstowej
│   └── MatrixCalc_Equations.h  # Silnik obliczeniowy wersji konsolowej
└── docs/                       # Dokumentacja i materiały pomocnicze
    ├── Materialy_Dydaktyczne.md
    └── Zalozenia_Projektu.md
```

### Kluczowe komponenty:
- **`App` (`wxApp`)**: Inicjalizuje pętlę zdarzeń biblioteki wxWidgets i tworzy okno `MainFrame`.
- **`MainFrame` (`wxFrame`)**: Dzieli interfejs na dwa panele:
  - *Panel lewy*: Lista zapisanych macierzy (`wxListView`) wraz z ich nazwami i wymiarami.
  - *Panel prawy*: Dynamiczne formularze wprowadzania danych, wybór macierzy operandów oraz interaktywny edytor siatki `wxGrid`.
  - *Pasek narzędzi*: Przyciski akcji z ikonami (Dodaj, Edytuj, Kopiuj, Usuń, Działania, Import, Eksport).
- **`MatrixEquations`**: Niezależny moduł czystego C++ operujący na wektorach dwuwymiarowych `std::vector<std::vector<float>>`.

---

## Wymagania systemowe

- **Kompilator**: C++17 lub nowszy (MSVC v143 / GCC 10+ / Clang 11+)
- **Biblioteka GUI**: [wxWidgets](https://www.wxwidgets.org/) 3.2+
- **System operacyjny**: Windows 10/11, Linux lub macOS

---

## Kompilacja i uruchomienie

### Opcja 1: CMake z automatycznym pobieraniem wxWidgets (FetchContent — Najwygodniejsze)

Projekt wspiera moduł **`FetchContent`**. Jeśli nie masz zainstalowanego wxWidgets na komputerze, CMake pobierze je automatycznie z oficjalnego repozytorium GitHub i skompiluje statycznie bez konieczności instalowania czegokolwiek:

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

> **Wskazówka**: Pierwsza kompilacja z pobieraniem wxWidgets zajmie kilka minut (biblioteka kompiluje się ze źródeł). Kolejne przebiegi są natychmiastowe. Wygenerowany plik `.exe` ma zaszyte biblioteki statycznie i nie wymaga instalacji żadnych DLL.

Możesz także wymusić pobieranie flagą:
```bash
cmake .. -DWX_FETCH_CONTENT=ON
```

### Opcja 2: CMake z menedżerem vcpkg (Dla posiadaczy zainstalowanego wxWidgets)

Jeśli posiadasz wxWidgets zainstalowane w systemie lub przez vcpkg, CMake wykryje je automatycznie i pominie pobieranie:

```bash
# Instalacja w vcpkg (opcjonalna):
vcpkg install wxwidgets:x64-windows

# Konfiguracja z vcpkg:
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=[ścieżka_do_vcpkg]/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release
```

### Opcja 3: Visual Studio 2022 (Tryb folderu CMake)

W Visual Studio 2022 wystarczy wybrać **File -> Open -> Folder** i wskazać katalog `MatrixCalc-wxWidgets`. Visual Studio automatycznie wykryje plik `CMakeLists.txt`, pobierze wxWidgets w tle i umożliwi uruchomienie programu jednym kliknięciem (**F5**).

### Wersja konsolowa (CLI)

Wersja konsolowa nie wymaga biblioteki wxWidgets i może zostać skompilowana dowolnym standardowym kompilatorem C++:

```bash
cd cli_legacy
g++ -std=c++17 ConsoleMenu.cpp -o MatrixCalcCLI
./MatrixCalcCLI
```

---

## Obsługa programu

1. **Dodawanie nowej macierzy**:
   - Kliknij ikonę **Add Matrix** na pasku narzędzi.
   - Wprowadź nazwę macierzy oraz liczbę wierszy i kolumn.
   - Kliknij **Submit**, a następnie uzupełnij wartości w tabeli i zatwierdź przyciskiem **Save Matrix**.
2. **Wykonywanie obliczeń**:
   - Kliknij ikonę **Mathematical Functions**.
   - Wybierz interesujące Cię działanie z listy rozwijanej (np. dodawanie, wyznacznik).
   - Wskaż macierze wejściowe lub podaj wartość skalara.
   - Kliknij **Submit**, aby zobaczyć wynik w dolnym panelu.
   - Możesz zapisać wynik operacji do magazynu za pomocą pola **Save as** i przycisku **Save**.
3. **Eksport i Import**:
   - Ikona **Export**: Zapisuje wybraną macierz do pliku tekstowego.
   - Ikona **Import**: Wczytuje macierz z pliku i dodaje ją do bieżącej sesji.

---

## Materiały i założenia

- [Założenia projektowe](docs/Zalozenia_Projektu.md)
- [Materiały dydaktyczne i kursy wxWidgets](docs/Materialy_Dydaktyczne.md)
