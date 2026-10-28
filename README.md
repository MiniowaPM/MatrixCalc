<<<<<<< HEAD
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
=======
# 🧮 MatrixCalc

**A cross-platform graphical matrix calculator built with C++ and wxWidgets.**

![C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![wxWidgets](https://img.shields.io/badge/GUI-wxWidgets-39A849?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-In_Development-orange?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

## 🚀 About The Project

**MatrixCalc** is a desktop application designed to perform mathematical operations on matrices quickly and intuitively. By leveraging the **wxWidgets** framework, the project aims to provide a native-feeling graphical user interface (GUI) across different operating systems (Windows, macOS, Linux) while keeping the computational backend lightning-fast in C++.

Whether you are a student solving linear algebra problems or a developer needing quick matrix transformations, MatrixCalc provides the essential tools in a clean windowed environment.

*Note: The project is currently undergoing configuration and structural improvements. The core code is available, and build system enhancements are on the roadmap.*

## ✨ Key Features (Planned & Implemented)

### 🧮 Core Matrix Operations
* **Basic Arithmetic:** Matrix Addition, Subtraction, and Multiplication.
* **Scalar Operations:** Multiply or divide a matrix by a scalar value.
* **Advanced Calculations:**
  * Determinant calculation.
  * Matrix Transposition.
  * Matrix Inversion.

### 🖥️ Graphical Interface
* **Dynamic Grids:** Input matrices of custom dimensions using a grid-based UI.
* **Native Look & Feel:** Utilizes wxWidgets to ensure the application looks native on your specific operating system.
* **Error Handling:** Visual alerts for invalid operations (e.g., trying to multiply incompatible matrices or inverting a singular matrix).

## 🏗️ Architecture & Tech Stack

* **Language:** C++ (Standard C++11 or higher)
* **GUI Framework:** [wxWidgets](https://www.wxwidgets.org/) (Version 3.x) - A C++ library that lets developers create applications for Windows, macOS, Linux, and other platforms with a single code base.

## 🔮 Roadmap (Next Steps)

Since the project is in early/restructuring phases, here are the immediate priorities:

* **🛠️ Build System Revamp:** Implement a robust `CMakeLists.txt` for easier cross-platform building and dependency resolution for wxWidgets.
* **🧹 Code Refactoring:** Separate the UI logic (wxWidgets events) strictly from the mathematical matrix processing logic.
* **🖼️ UI Polish & Screenshots:** Finalize the layout sizing and add high-quality screenshots to this README.
* **💾 Save/Load Feature:** Ability to export matrix results to `.txt` or `.csv` files.
>>>>>>> 93a622de0c23d19602c730ec50b78c2092fcbf1d
