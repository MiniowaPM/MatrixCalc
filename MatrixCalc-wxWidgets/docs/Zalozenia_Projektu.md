# Założenia Projektu - MatrixCalc

## Opis ogólny
Kalkulator podstawowych działań na macierzach zrealizowany w języku C++ z graficznym interfejsem użytkownika (**wxWidgets**) oraz modułem konsolowym (**CLI**).

## Wymagania funkcjonalne
- **Zarządzanie macierzami w pamięci podręcznej**:
  - Tworzenie nowej macierzy o zadanym rozmiarze ($M \times N$).
  - Edycja wartości poszczególnych komórek w siatce tabeli (`wxGrid`).
  - Kopiowanie macierzy do nowego obiektu.
  - Usuwanie wybranej macierzy lub czyszczenie magazynu.
  - Szybki zapis wyników pośrednich pod nową nazwą.
- **Wizualizacja i podgląd**:
  - Wyświetlanie listy zapisanych macierzy wraz z ich wymiarami (`wxListView`).
  - Czytelny podgląd macierzy wynikowej lub wyznacznika/rzędu.
- **Wykonywanie operacji algebraicznych na macierzach**:
  - Dodawanie macierzy ($A + B$)
  - Odejmowanie macierzy ($A - B$)
  - Mnożenie macierzy ($A \times B$)
  - Mnożenie macierzy przez skalar ($k \cdot A$)
  - Potęgowanie macierzy ($A^n$)
  - Transpozycja macierzy ($A^T$)
  - Obliczanie wyznacznika macierzy kwadratowej ($\det A$)
  - Wyznaczanie macierzy odwrotnej ($A^{-1}$)
  - Wyznaczanie rzędu macierzy ($\text{rank}(A)$)
- **Persystencja danych**:
  - Eksport macierzy do pliku tekstowego.
  - Import macierzy z pliku zewnętrznego.
- **Interfejs**:
  - Panel GUI oparty o wxWidgets.
  - Alternatywny / prototypowy panel konsolowy (CLI).
