# PM-OrganizationalTree (Hierarchiczna Struktura Drzewiasta)

Projekt w języku C++ implementujący hierarchiczną strukturę danych (drzewo wielodrożne / N-arne) reprezentującą strukturę organizacyjną **Politechniki Morskiej w Szczecinie**. Projekt zrealizowany w ramach przedmiotu *Metody Programowania*.

---

## Spis treści
- [O projekcie](#o-projekcie)
- [Struktura danych i algorytmy](#struktura-danych-i-algorytmy)
- [Odwzorowana hierarchia uczelni](#odwzorowana-hierarchia-uczelni)
- [Struktura katalogów](#struktura-katalogów)
- [Kompilacja i uruchomienie](#kompilacja-i-uruchomienie)
  - [Opcja 1: Visual Studio 2022](#opcja-1-visual-studio-2022)
  - [Opcja 2: CMake (Dowolny system)](#opcja-2-cmake-dowolny-system)
  - [Opcja 3: Bezpośrednia kompilacja z terminala](#opcja-3-bezpośrednia-kompilacja-z-terminala)
- [Przykładowy wynik działania](#przykładowy-wynik-działania)
- [Materiały dydaktyczne](#materiały-dydaktyczne)

---

## O projekcie

Celem projektu jest odwzorowanie oficjalnej hierarchii jednostek organizacyjnych Politechniki Morskiej w Szczecinie na podstawie [schematu organizacyjnego PM](https://pm.szczecin.pl/pl/struktura/schemat-organizacyjny/).

Program modeluje relacje nadrzędności i podrzędności pomiędzy władzami uczelni (Rektor), wydziałami (Dziekani), jednostkami dydaktycznymi (Katedry, Centra) oraz laboratoriami badawczymi.

---

## Struktura danych i algorytmy

### 1. Węzeł drzewa (`Faculty`)
Każdy węzeł reprezentuje jednostkę organizacyjną i przechowuje:
- `name` (`std::string`): Nazwa jednostki (np. "Wydział Nawigacyjny Dziekan", "Katedra Informatyki").
- `departments` (`std::vector<Faculty*>`): Dynamiczna lista wskaźników do podrzędnych jednostek (dzieci węzła), co pozwala na tworzenie drzewa o dowolnym stopniu rozgałęzienia.

```cpp
struct Faculty {
    std::string name;
    std::vector<Faculty*> departments;

    Faculty(std::string name) : name(name) {}
};
```

### 2. Klasa zarządzająca (`University`)
- **Dynamiczne dodawanie węzłów (`addNodes`)**: Pozwala na dołączanie nowej jednostki do wskazanego węzła rodzica lub ustawienie korzenia (`rootElement`).
- **Rekurencyjne wyświetlanie (`displayElements`)**: Przechodzi drzewo w głąb (metoda zbliżona do pre-order), formatując wcięcia za pomocą tabulatorów w zależności od parametru `depth`.
- **Bezpieczne zarządzanie pamięcią (`deleteTree`)**: Destruktor klasy rekurencyjnie zwalnia dynamicznie zaalokowaną pamięć (`delete`), zapobiegając wyciekom pamięci (*memory leaks*).

---

## Odwzorowana hierarchia uczelni

1. **Rektor (Korzeń drzewa)**
   - **Wydział Nawigacyjny**
     - Dziekanat, Wydziałowe Centrum Kształcenia
     - Katedry: Inżynierii Ruchu Morskiego, Nawigacji Morskiej, Symulacji Morskich, Ratownictwa i Zarządzania Ryzykiem, Oceanotechniki i Budowy Okrętów, Geoinformatyki i Hydrografii, Geodezji i Pomiarów Offshore
   - **Wydział Mechaniczny**
     - Dziekanat, Wydziałowe Centrum Kształcenia (Laboratorium Siłowni Okrętowych, Laboratorium Technik Wytwarzania)
     - Centra i Katedry: Centrum Badania Paliw, Podstaw Budowy Maszyn, Siłowni Okrętowych, Diagnostyki Maszyn, Energetyki, Centrum Badawcze Recyklingu
   - **Wydział Inżynieryjno-Ekonomiczny Transportu**
     - Dziekanat, Wydziałowe Centrum Kształcenia
     - Katedry: Zarządzania i Logistyki, Gospodarki Morskiej, Procesów Technologicznych, Ochrony Środowiska i Towaroznawstwa
   - **Wydział Informatyczny i Telekomunikacyjny**
     - Dziekanat, Wydziałowe Centrum Kształcenia
     - Katedry: Informatyki, Telekomunikacji
   - **Wydział Mechatroniki i Elektrotechniki**
     - Dziekanat, Wydziałowe Centrum Kształcenia
     - Katedry: Elektrotechniki i Energoelektroniki, Automatyki Okrętowej

---

## Struktura katalogów

```text
PM-OrganizationalTree/
├── CMakeLists.txt                              # Konfiguracja kompilacji CMake
├── HierarchicznaStrukturaDanych_Drzewa.sln     # Plik rozwiązania Visual Studio 2022
├── HierarchicznaStrukturaDanych_Drzewa.vcxproj # Konfiguracja projektu C++ MSVC
├── HierarchicznaStrukturaDanych_Drzewa.vcxproj.filters
├── README.md                                   # Niniejsza dokumentacja
├── docs/                                       # Dokumentacja i materiały
│   ├── DrzewaPrezentacja.pptx                  # Prezentacja multimedialna na temat struktur drzewiastych
│   └── Zalozenia_Projektu.md                   # Wymagania i założenia projektowe
└── src/                                        # Kod źródłowy
    └── HierarchicznaStrukturaDanych_Drzewa.cpp # Główny program z implementacją drzewa
```

---

## Kompilacja i uruchomienie

### Opcja 1: Visual Studio 2022
1. Otwórz plik `HierarchicznaStrukturaDanych_Drzewa.sln`.
2. Ustaw konfigurację na `Debug` lub `Release` oraz platformę `x64`.
3. Naciśnij **F5** (Kompiluj i uruchom z debugowaniem) lub **Ctrl+F5**.

### Opcja 2: CMake (Dowolny system)
```bash
mkdir build && cd build
cmake ..
cmake --build .
./PM_OrganizationalTree
```

### Opcja 3: Bezpośrednia kompilacja z terminala
```bash
g++ -std=c++17 src/HierarchicznaStrukturaDanych_Drzewa.cpp -o PM_Tree
./PM_Tree
```

---

## Przykładowy wynik działania

```text
Struktura Organizacyjna Uczelni:
- Rektor
	- Wydział Nawigacyjny Dziekan
		- Dziekanat
		- Wydziałowe Centrum Kształcenia
		- Katedra Inżynierii Ruchu Morskiego
		- Katedra Nawigacji Morskiej
        ...
	- Wydział Mechaniczny Dziekan
		- Dziekanat
		- Wydziałowe Centrum Kształcenia
			- Laboratorium Siłowni Okrętowych
			- Laboratorium Technik Wytwarzania. Warsztaty Mechaniczne
        ...
```

---

## Materiały dydaktyczne

- [Prezentacja PowerPoint o drzewach](docs/DrzewaPrezentacja.pptx)
- [Założenia projektowe](docs/Zalozenia_Projektu.md)
