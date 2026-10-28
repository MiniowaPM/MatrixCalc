# Metody Programowania - Zagadnienia i Teoria

Notatki i zagadnienia z przedmiotu **Metody Programowania** (kod grupy: 31001), Politechnika Morska w Szczecinie.

---

## Zagadnienia prowadzonych zajęć

1. **Rekurencja**: Wykorzystanie rekurencji do rozwiązywania problemów algorytmicznych.
2. **Programowanie z nawrotami (Backtracking)**: Na przykładzie *problemu hetmanów*.
3. **Dziel i zwyciężaj (Divide and Conquer)**: Na przykładzie wyszukiwania przez podział binarny oraz algorytmu *QuickSort*.
4. **Listy wiązane**: Praktyczna implementacja list jedno- i dwukierunkowych oraz cyklicznych.
5. **Liniowe struktury danych**: Stosy i kolejki (LIFO, FIFO).
6. **Grafy**: Implementacja i przeszukiwanie struktur grafowych (BFS, DFS).
7. **Drzewa**: Implementacja i zastosowanie drzew dowolnego rzędu (N-arnych / wielodrożnych).
8. **Obiegi drzew**: Przechodzenie drzew (pre-order, in-order, post-order, level-order) i przykłady zastosowań.
9. **Programowanie zachłanne**: Na przykładzie algorytmu kompresji *Huffmana*.
10. **Programowanie dynamiczne**: Problem plecakowy, optymalne mnożenie łańcucha macierzy (*matrix chain multiplication*).

---

## Podstawowe pojęcia programowania obiektowego (OOP)

* **Klasy**: W programowaniu obiektowym klasa jest szablonem lub modelem definiującym cechy (pola / właściwości) oraz zachowania (metody) obiektów. Obiekty są konkretnymi instancjami klas.
* **Hermetyzacja (Encapsulation)**: Filar programowania obiektowego polegający na ukrywaniu wewnętrznej implementacji obiektów i udostępnianiu jedynie niezbędnych interfejsów do interakcji. Pola klasy są zwykle prywatne (`private`), a dostęp do nich odbywa się za pomocą metod publicznych (`gettery` i `settery`), co zapewnia kontrolę nad spójnością stanu obiektu.
* **Dziedziczenie (Inheritance)**: Mechanizm umożliwiający tworzenie nowych klas (klas podrzędnych / pochodnych) na bazie klas istniejących (klas bazowych / nadrzędnych). Klasy potomne przejmują właściwości i metody klasy bazowej oraz mogą je rozszerzać lub nadpisywać, co sprzyja reużywalności kodu.
* **Polimorfizm (Polymorphism)**: Zdolność do jednolitego traktowania obiektów różnych klas powiązanych wspólnym interfejsem lub klasą bazową. Umożliwia wywołanie metody o tej samej sygnaturze, która w zależności od rzeczywistego typu obiektu wywoła odpowiednią implementację (np. poprzez metody wirtualne `virtual`).
* **Abstrakcja (Abstraction)**: Proces wyodrębniania kluczowych cech obiektów z pominięciem szczegółów implementacyjnych nieistotnych w danym kontekście. Osiągana m.in. przez definicję interfejsów i klas czysto wirtualnych (`pure virtual functions`).
