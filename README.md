# Metody Programowania — Projekty Zaliczeniowe

Repozytorium zawierające projekty programistyczne zrealizowane w języku **C++** w ramach przedmiotu **Metody Programowania** na **Politechnice Morskiej w Szczecinie**.

---

## Przegląd projektów

W repozytorium znajdują się dwa główne projekty oraz zbiór materiałów teoretycznych:

| Projekt | Opis | Technologie | Ścieżka |
| :--- | :--- | :--- | :--- |
| **[MatrixCalc](MatrixCalc-wxWidgets/)** | Zaawansowany kalkulator macierzy z graficznym interfejsem użytkownika (GUI) oraz modułem konsolowym (CLI). Obsługuje dodawanie, odejmowanie, mnożenie, transpozycję, wyznacznik, odwracanie, rząd oraz import/eksport danych. | C++17, wxWidgets 3.2, CMake, wxGrid | [`MatrixCalc-wxWidgets/`](MatrixCalc-wxWidgets/) |
| **[PM-OrganizationalTree](PM-OrganizationalTree/)** | Implementacja wielodrożnego drzewa hierarchicznego (N-arnego) odwzorowującego schemat organizacyjny Politechniki Morskiej w Szczecinie (Rektor $\rightarrow$ Wydziały $\rightarrow$ Katedry $\rightarrow$ Laboratoria). | C++17, STL (vector), Visual Studio / CMake | [`PM-OrganizationalTree/`](PM-OrganizationalTree/) |
| **[Notatki i Teoria](docs/MetodyProgramowania_Notatki.md)** | Zestawienie zagadnień realizowanych na zajęciach (rekurencja, backtracking, drzewa, grafy, programowanie dynamiczne) oraz filary programowania obiektowego (OOP). | Markdown | [`docs/MetodyProgramowania_Notatki.md`](docs/MetodyProgramowania_Notatki.md) |

---

## Struktura Repozytorium

```text
MatrixCalc/
├── .gitignore                          # Ignorowane pliki tymczasowe, binarne i VS (.vs, x64, *.pdb itp.)
├── README.md                           # Główny opis repozytorium (ten plik)
│
├── docs/                               # Wspólne notatki i materiały teoretyczne
│   └── MetodyProgramowania_Notatki.md  # Sylabus, zagadnienia z zajęć i definicje OOP
│
├── MatrixCalc-wxWidgets/               # Projekt 1: Kalkulator Macierzy (GUI + CLI)
│   ├── CMakeLists.txt                  # Skrypt budowania CMake dla GUI i CLI
│   ├── README.md                       # Szczegółowa dokumentacja kalkulatora macierzy
│   ├── icons/                          # Zasoby graficzne (ikony paska narzędzi)
│   ├── include/                        # Nagłówki (.h): App, MainFrame, Globals, MatrixEquations
│   ├── src/                            # Źródła (.cpp): App, MainFrame, MatrixEquations
│   ├── cli_legacy/                     # Wersja konsolowa projektu (ConsoleMenu.cpp)
│   └── docs/                           # Założenia projektowe i materiały dydaktyczne wxWidgets
│
└── PM-OrganizationalTree/              # Projekt 2: Struktura Drzewiasta (Politechnika Morska)
    ├── CMakeLists.txt                  # Skrypt budowania CMake
    ├── HierarchicznaStrukturaDanych_Drzewa.sln     # Rozwiązanie Visual Studio 2022
    ├── HierarchicznaStrukturaDanych_Drzewa.vcxproj # Konfiguracja projektu MSVC
    ├── README.md                       # Szczegółowa dokumentacja struktury drzewiastej
    ├── docs/                           # Prezentacja PowerPoint oraz założenia projektu
    └── src/                            # Źródło C++ z implementacją hierarchii drzewa
```

---

## Wymagania systemowe

- **Kompilator C++**: Obsługa standardu **C++17** lub nowszego:
  - MSVC v143 (Visual Studio 2022)
  - GCC 10+
  - Clang 11+
- **Narzędzie do budowania**: [CMake](https://cmake.org/) (wersja $\ge 3.16$) lub Visual Studio 2022.
- **Biblioteki zewnętrzne**:
  - [wxWidgets 3.2+](https://www.wxwidgets.org/) – wymagane wyłącznie dla projektu `MatrixCalc-wxWidgets`. Projekt `PM-OrganizationalTree` oraz moduł `cli_legacy` korzystają wyłącznie ze standardowej biblioteki C++ (STL).

---

## Szybki Start

### 1. Budowanie kalkulatora macierzy (`MatrixCalc-wxWidgets`)

Projekt wspiera automatyczne pobieranie wxWidgets za pomocą modułu CMake **`FetchContent`** — nie musisz instalować żadnych bibliotek ręcznie:

```bash
cd MatrixCalc-wxWidgets
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

*Uwaga: Jeśli posiadasz już wxWidgets (np. zainstalowane przez `vcpkg`), CMake wykryje je automatycznie, co przyspieszy pierwsze budowanie.*

Szczegółowe instrukcje konfiguracji i obsługi znajdują się w [`MatrixCalc-wxWidgets/README.md`](MatrixCalc-wxWidgets/README.md).

### 2. Budowanie struktury drzewiastej (`PM-OrganizationalTree`)

Projekt można skompilować za pomocą CMake, rozwiązania Visual Studio lub bezpośrednio z poziomu terminala:

```bash
cd PM-OrganizationalTree
mkdir build && cd build
cmake ..
cmake --build .
./PM_OrganizationalTree
```

Szczegółowe instrukcje konfiguracji i omówienie algorytmów znajdują się w [`PM-OrganizationalTree/README.md`](PM-OrganizationalTree/README.md).

---

## Uczelnia i Przedmiot

- **Uczelnia**: Politechnika Morska w Szczecinie
- **Kierunek**: Informatyka
- **Przedmiot**: Metody Programowania
