#include <iostream>
#include <iomanip>
#include <string>
#include "Semafor.h"
#include "PjesackiSemafor.h"
#include "Raskrsnica.h"
#include <conio.h>

static void ispis() {
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(25) << std::left << "Trenutno stanje"
        << std::setw(25) << std::left << "Novo stanje"
        << std::setw(15) << std::left << "Aktivnost"
        << std::setw(15) << std::left << "Greska" << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}

static void ispisVrijednosti(std::string trenutnoStanje, std::string novoStanje, bool aktivnost, bool greska) {
    std::cout << std::setw(25) << std::left << trenutnoStanje
        << std::setw(25) << std::left << novoStanje
        << std::setw(15) << std::left << aktivnost
        << std::setw(15) << std::left << greska << std::endl;
}

static void ispisRaskrsnica() {
    std::cout << "------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(20) << std::left << "Semafor stanje"
        << std::setw(20) << std::left << "Pjesacki stanje"
        << std::setw(15) << std::left << "Broj vozila"
        << std::setw(15) << std::left << "Broj pjesaka" << std::endl;
    std::cout << "------------------------------------------------------------------------" << std::endl;
}

static void ispisRaskrsnicaVrijednosti(std::string semaforStanje, std::string pjesackiSemaforStanje, bool novoVozilo, bool noviPjesak, int brojVozila, int brojPjesaka) {
    std::cout << std::setw(20) << std::left << semaforStanje
        << std::setw(20) << std::left << pjesackiSemaforStanje
        << std::setw(15) << std::left << brojVozila
        << std::setw(15) << std::left << brojPjesaka << std::endl;
}

static void ispisStanja(bool pjesacki) {
    system("cls");
    std::cout << "------------------------------------------------------\n";
    std::cout << "\t\t*** STANJA***\n";
    std::cout << "------------------------------------------------------\n";
    if (pjesacki) {
        std::cout << "\t1. MIROVANJE\n";
        std::cout << "\t2. CRVENO\n";
        std::cout << "\t3. ZELENO\n";
    }
    else {
        std::cout << "\t1. MIROVANJE\n";
        std::cout << "\t2. CRVENO\n";
        std::cout << "\t3. CRVENO_ZUTO\n";
        std::cout << "\t4. ZELENO\n";
        std::cout << "\t5. ZUTO\n";
        std::cout << "\t6. ZUTO_BLINKAJUCE\n";
    }
}

static int glavniMenu() {
    int izbor;
    system("cls");
    std::cout << "------------------------------------------------------\n";
    std::cout << "\t\t*** GLAVNI MENU ***\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "\t1. Semafor\n";
    std::cout << "\t2. Pjesacki semafor\n";
    std::cout << "\t3. Raskrsnica - SIMULACIJA\n";
    std::cout << "\t4. Izlaz\n";
    std::cout << "\tUnesite vas izbor: ";
    std::cin >> izbor;
    if (izbor != 4) return izbor;
    else {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        return 0;
    }
}

static int pomocniMenu() {
    int izbor;
    system("cls");
    std::cout << "------------------------------------------------------\n";
    std::cout << "\t\t*** POMOCNI MENU ***\n";
    std::cout << "------------------------------------------------------\n";
    std::cout << "\t1. Simulacija\n";
    std::cout << "\t2. Simuliraj rucno\n";
    std::cout << "\t3. Testiranje prijelaza\n";
    std::cout << "\t4. Nazad\n";
    std::cout << "\tUnesite vas izbor: ";
    std::cin >> izbor;
    if (izbor != 4) return izbor;
    else {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        return 0;
    }
}

static void pokreniGlavniMenu() {
	int izbor;
	Semafor* s = new Semafor();
	PjesackiSemafor* p = new PjesackiSemafor();
	Raskrsnica* r = new Raskrsnica();
	while (izbor = glavniMenu()) {
		switch (izbor) {
		case 1:
			system("cls");
			int izbor2;
			while (izbor2 = pomocniMenu()) {
				switch (izbor2) {
				case 1:
					system("cls");
					s->simulirajPrijelazeStanja();
					break;
				case 2:
					system("cls");
					s->simulirajPrijelazeStanjaRucno();
					break;
				case 3:
					system("cls");
                    ispisStanja(false);
                    s->testirajPrijelaz();
					break;
				}
				std::cout << "\nPritisnite bilo koju tipku za nastavak\n";
				_getch();
			}
			break;
		case 2:
			system("cls");
			int izbor3;
			while (izbor3 = pomocniMenu()) {
				switch (izbor3) {
				case 1:
					system("cls");
					p->simulirajPrijelazeStanja();
					break;
				case 2:
					system("cls");
					p->simulirajPrijelazeStanjaRucno();
					break;
				case 3:
					system("cls");
                    ispisStanja(true);
                    p->testirajPrijelaz();
					break;
				}
				std::cout << "\nPritisnite bilo koju tipku za nastavak\n";
				_getch();
			}
			break;
		case 3:
			system("cls");
			r->simulirajRaskrsnicu();
			break;
		}
	}
}