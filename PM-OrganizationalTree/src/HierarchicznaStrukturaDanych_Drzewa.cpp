#include <iostream>
#include <string>
#include <vector>

struct Faculty {
    std::string name;
    std::vector<Faculty*> departments;

    Faculty(std::string name) : name(name) {}
};

class University {
public:
    Faculty* rootElement = nullptr;

    void displayElements(Faculty* departments, int depth = 0) {
        if (departments == nullptr) {
            return;
        }
        for (int i = 0; i < depth; i++) {
            std::cout << "\t";
        }
        std::cout << "- " << departments->name << "\n";
        for (Faculty* dept : departments->departments) {
            displayElements(dept, depth + 1);
        }
    }

    void addNodes(const std::string name, Faculty* node) {
        Faculty* newDepartment = new Faculty(name);
        if (node == nullptr) {
            rootElement = newDepartment;
        } else {
            node->departments.push_back(newDepartment);
        }
    }

    void displayTree() {
        if (rootElement == nullptr) {
            std::cout << "Struktura uczelni jest pusta." << std::endl;
        } else {
            std::cout << "Struktura Organizacyjna Uczelni:" << std::endl;
            displayElements(rootElement);
        }
    }

    ~University() {
        deleteTree(rootElement);
    }

    void deleteTree(Faculty* departments) {
        if (departments == nullptr) {
            return;
        }
        for (Faculty* dept : departments->departments) {
            deleteTree(dept);
        }
        delete departments;
    }
};

int main() {
    setlocale(LC_CTYPE, "Polish");

    University university;

    Faculty* rootElement = new Faculty("Rektor");
    university.addNodes("Wydział Nawigacyjny Dziekan", rootElement);
    university.addNodes("Wydział Mechaniczny Dziekan", rootElement);
    university.addNodes("Wydział Inżynieryjno-Ekonomiczny Transportu Dziekan", rootElement);
    university.addNodes("Wydział Informatyczny i Telekomunikacyjny Dziekan", rootElement);
    university.addNodes("Wydział Mechatroniki i Elektrotechniki Dziekan", rootElement);

    // Wydział Nawigacyjny
    Faculty* nawigacja = rootElement->departments[0];
    university.addNodes("Dziekanat", nawigacja);
    university.addNodes("Wydziałowe Centrum Kształcenia", nawigacja);
    university.addNodes("Katedra Inżynierii Ruchu Morskiego", nawigacja);
    university.addNodes("Katedra Nawigacji Morskiej", nawigacja);
    university.addNodes("Katedra Symulacji Morskich", nawigacja);
    university.addNodes("Katedra Ratownictwa i Zarządzania Ryzykiem", nawigacja);
    university.addNodes("Katedra Oceanotechniki i Budowy Okrętów", nawigacja);
    university.addNodes("Katedra Geoinformatyki i Hydrografii", nawigacja);
    university.addNodes("Katedra Geodezji i Pomiarów Offshore", nawigacja);

    // Wydział Mechaniczny
    Faculty* mechanika = rootElement->departments[1];
    university.addNodes("Dziekanat", mechanika);
    university.addNodes("Wydziałowe Centrum Kształcenia", mechanika);
    university.addNodes("Centrum Badania Paliw, Cieczy Roboczych i Ochrony Środowiska", mechanika);
    university.addNodes("Katedra Podstaw Budowy Maszyn i Materiałoznawstwa", mechanika);
    university.addNodes("Katedra Siłowni Okrętowych", mechanika);
    university.addNodes("Katedra Diagnostyki i Remontów Maszyn", mechanika);
    university.addNodes("Katedra Energetyki", mechanika);
    university.addNodes("Centrum Badawcze Recyklingu i Diagnostyki Elementów", mechanika);

    Faculty* wckMechanika = mechanika->departments[1];
    university.addNodes("Laboratorium Siłowni Okrętowych", wckMechanika);
    university.addNodes("Laboratorium Technik Wytwarzania. Warsztaty Mechaniczne", wckMechanika);

    // Wydział Inżynieryjno-Ekonomiczny Transportu
    Faculty* inzEkon = rootElement->departments[2];
    university.addNodes("Dziekanat", inzEkon);
    university.addNodes("Wydziałowe Centrum Kształcenia", inzEkon);
    university.addNodes("Katedra Zarządzania i Logistyki", inzEkon);
    university.addNodes("Katedra Gospodarki Morskiej i Systemów Transportowych", inzEkon);
    university.addNodes("Katedra Procesów Technologicznych", inzEkon);
    university.addNodes("Katedra Ochrony Środowiska i Towaroznawstwa", inzEkon);

    // Wydział Informatyczny i Telekomunikacyjny
    Faculty* infTel = rootElement->departments[3];
    university.addNodes("Dziekanat", infTel);
    university.addNodes("Wydziałowe Centrum Kształcenia", infTel);
    university.addNodes("Katedra Informatyki", infTel);
    university.addNodes("Katedra Telekomunikacji", infTel);

    // Wydział Mechatroniki i Elektrotechniki
    Faculty* mechElek = rootElement->departments[4];
    university.addNodes("Dziekanat", mechElek);
    university.addNodes("Wydziałowe Centrum Kształcenia", mechElek);
    university.addNodes("Katedra Elektrotechniki i Energoelektroniki", mechElek);
    university.addNodes("Katedra Automatyki Okrętowej", mechElek);

    university.rootElement = rootElement;

    university.displayTree();

    return 0;
}
