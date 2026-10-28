# Założenia Projektu - Struktura Organizacyjna Politechniki Morskiej w Szczecinie

## Cel projektu
Budowa hierarchicznej struktury danych (drzewo wielodrożne / N-arne) odzwierciedlającej oficjalny schemat organizacyjny wydziałów udostępniony na stronie Politechniki Morskiej w Szczecinie:
[Schemat organizacyjny Politechniki Morskiej](https://pm.szczecin.pl/pl/struktura/schemat-organizacyjny/)

## Wymagania funkcjonalne
- Dynamiczne tworzenie struktury drzewiastej w pamięci opartej na wskaźnikach.
- Możliwość dodawania nowych węzłów potomnych (`addNodes`) do dowolnego poziomu hierarchii.
- Rekurencyjne wyświetlanie struktury organizacyjnej z graficzną reprezentacją głębokości (wcięcia tabulatorami).
- Prawidłowe zwalnianie całej zaalokowanej dynamicznie pamięci w destruktorze (`deleteTree`).

## Terminy
- **Przewidywany czas wykonania projektu**: 3 tygodnie
- **Data oddania**: 24.04.2024
