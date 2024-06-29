#include "Semafor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "Funkcije.cpp"

SemaforStanje* Semafor::getTrenutnoStanje()
{
    return this->trenutnoStanje;
}

std::vector<SemaforStanje> Semafor::getStanja()
{
    return this->stanja;
}

std::map<Stanje, std::vector<Stanje>> Semafor::getPrijelazi()
{
    return this->prijelazi;
}

bool Semafor::isAktivan() const
{
    return this->aktivan;
}

bool Semafor::isGreska() const
{
    return this->greska;
}

void Semafor::setTrenutnoStanje(SemaforStanje *s)
{
    this->trenutnoStanje = s;
}

void Semafor::setStanja(std::vector<SemaforStanje> s)
{
    this->stanja = s;
}

void Semafor::setPrijelazi(std::map<Stanje, std::vector<Stanje>> p)
{
    this->prijelazi = p;
}

void Semafor::setAktivan(bool a)
{
    this->aktivan = a;
}

void Semafor::setGreska(bool g)
{
    this->greska = g;
}

void Semafor::promjeniTrenutnoStanje()
{
    auto prijelazi = this->getPrijelazi();
    auto stanja = this->getStanja();
    auto it = prijelazi.find(this->getTrenutnoStanje()->getStanje());
    if (it != prijelazi.end()) {
        std::vector<Stanje> pronadjeniPrijelazi = it->second;
        if (this->isAktivan()) {
            Stanje sljedeceStanje = pronadjeniPrijelazi[0];
            auto it = std::find_if(stanja.begin(), stanja.end(), [sljedeceStanje](SemaforStanje s) {
                return s.getStanje() == sljedeceStanje;
                });
            SemaforStanje* novoStanje = new SemaforStanje(it->getStanje(), it->getTrajanje());
            this->setTrenutnoStanje(novoStanje);
        }
        if (this->isGreska() || !this->isAktivan()) {
            Stanje sljedeceStanje = pronadjeniPrijelazi[1];
            auto it = std::find_if(stanja.begin(), stanja.end(), [sljedeceStanje](SemaforStanje s) {
                return s.getStanje() == sljedeceStanje;
                });
            SemaforStanje* novoStanje = new SemaforStanje(it->getStanje(), it->getTrajanje());
            this->setTrenutnoStanje(novoStanje);
        }
    }
}

void Semafor::simulirajPrijelazeStanjaRucno()
{
    std::string trenutnoStanjeStr;
    int unos;
    std::cout << "Unesite -1 za KRAJ programa!" << std::endl;
    while (true) {
        std::cout << "Izaberite aktivnost semafora: " << std::endl;
        std::cout << "0. FALSE" << std::endl;
        std::cout << "1. TRUE" << std::endl;
        std::cout << "UNOS: ";
        std::cin >> unos;
        if (unos == -1) std::exit(0);
        if (unos < 0 || unos > 1) unos = 1;
        this->setAktivan(unos);
        std::cout << "Izaberite pojavu greske na semaforu: " << std::endl;
        std::cout << "0. FALSE" << std::endl;
        std::cout << "1. TRUE" << std::endl;
        std::cout << "UNOS: ";
        std::cin >> unos;
        if (unos == -1) std::exit(0);
        if (unos < 0 || unos > 1) unos = 0;
        this->setGreska(unos);
        ispis();
        trenutnoStanjeStr = this->getTrenutnoStanje()->getStanjeString();
        this->promjeniTrenutnoStanje();
        ispisVrijednosti(trenutnoStanjeStr, this->getTrenutnoStanje()->getStanjeString(), this->isAktivan(), this->isGreska());
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
    }
}

void Semafor::simulirajPrijelazeStanja()
{
    std::string trenutnoStanjeStr;
    ispis();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int brojac = 0;
    while (true) {
        int randomBit1 = std::rand() % 2;
        int randomBit2 = std::rand() % 2;
        if (brojac % 5 == 0) this->setAktivan(randomBit1);
        if (brojac % 10 == 0) this->setGreska(randomBit2);
        std::this_thread::sleep_for(std::chrono::seconds(this->getTrenutnoStanje()->getTrajanje()));
        trenutnoStanjeStr = this->getTrenutnoStanje()->getStanjeString();
        this->promjeniTrenutnoStanje();
        ispisVrijednosti(trenutnoStanjeStr, this->getTrenutnoStanje()->getStanjeString(), this->isAktivan(), this->isGreska());
        brojac++;
    }
}

void Semafor::testirajPrijelaz()
{
    auto prijelazi = this->getPrijelazi();
    auto stanja = this->getStanja();
    int iz, u;
    do
    {
        std::cout << "Unesite redni broj stanja IZ: ";
        std::cin >> iz;
        if (iz <= 0 || iz > stanja.size()) std::cout << "Greska! Unesite pravilan broj!" << std::endl;
    } while (iz <= 0 || iz > stanja.size());
    SemaforStanje stanjeIz = stanja[iz - 1];
    std::cout << "Odabrano stanje IZ: " << stanjeIz.getStanjeString() << std::endl;
    auto it = prijelazi.find(stanjeIz.getStanje());
    if (it != prijelazi.end()) {
        std::cout << "Stanja U za odabrano stanje IZ:" << std::endl;
        for (const auto& stanje : it->second) {
            SemaforStanje* s = new SemaforStanje(stanje, -1);
            std::cout << s->getStanjeString() << std::endl;
        }
    }
    do
    {
        std::cout << "Unesite redni broj stanja U: ";
        std::cin >> u;
        if (u <= 0 || u > stanja.size()) std::cout << "Greska! Unesite pravilan broj!" << std::endl;
    } while (u <= 0 || u > stanja.size());
    SemaforStanje stanjeU = stanja[u - 1];
    std::cout << "Odabrano stanje U: " << stanjeU.getStanjeString() << std::endl;
    std::cout << "Stanja IZ za odabrano stanje U:" << std::endl;
    for (const auto& vrijednost : prijelazi) {
        for (const auto& stanje : vrijednost.second) {
            if (stanje == stanjeU.getStanje()) {
                SemaforStanje* s = new SemaforStanje(vrijednost.first, -1);
                std::cout << s->getStanjeString() << std::endl;
            }
        }
    }
    if (it != prijelazi.end()) {
        const std::vector<Stanje>& vrijednosti = it->second;
        if (std::find(vrijednosti.begin(), vrijednosti.end(), stanjeU.getStanje()) != vrijednosti.end()) {
            std::cout << "Postoji prijelaz IZ stanja " << stanjeIz.getStanjeString() << " U stanje " << stanjeU.getStanjeString() << std::endl;
        }
        else {
            std::cout << "Ne postoji prijelaz IZ stanja " << stanjeIz.getStanjeString() << " U stanje " << stanjeU.getStanjeString() << std::endl;
        }
    }
}
