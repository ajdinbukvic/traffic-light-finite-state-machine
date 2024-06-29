#include "Raskrsnica.h"
#include <thread>
#include "Konstante.h"
#include <iostream>
#include "Funkcije.cpp"

Semafor* Raskrsnica::getSemafor()
{
    return this->semafor;
}

PjesackiSemafor* Raskrsnica::getPjesackiSemafor()
{
    return this->pjesackiSemafor;
}

int Raskrsnica::getBrojVozila() const
{
    return this->brojVozila;
}

int Raskrsnica::getBrojPjesaka() const
{
    return this->brojPjesaka;
}

bool Raskrsnica::isNovoVozilo() const
{
    return this->novoVozilo;
}

bool Raskrsnica::isNoviPjesak() const
{
    return this->noviPjesak;
}

std::vector<PrijelazStanja> Raskrsnica::getSinhroniziraniPrijelazi()
{
    return this->sinhroniziraniPrijelazi;
}

void Raskrsnica::setSemafor(Semafor* s)
{
    this->semafor = s;
}

void Raskrsnica::setPjesackiSemafor(PjesackiSemafor* p)
{
    this->pjesackiSemafor = p;
}

void Raskrsnica::setBrojVozila(int n)
{
    this->brojVozila = n;
}

void Raskrsnica::setBrojPjesaka(int n)
{
    this->brojPjesaka = n;
}

void Raskrsnica::setNovoVozilo(bool n)
{
    this->novoVozilo = n;
}

void Raskrsnica::setNoviPjesak(bool n)
{
    this->noviPjesak = n;
}

void Raskrsnica::setSinhroniziraniPrijelazi(std::vector<PrijelazStanja> s)
{
    this->sinhroniziraniPrijelazi = s;
}

void Raskrsnica::povecajBrojVozila()
{
    this->brojVozila++;
}

void Raskrsnica::povecajBrojPjesaka()
{
    this->brojPjesaka++;
}

void Raskrsnica::simulirajRaskrsnicu()
{
    this->getSemafor()->setAktivan(true);
    this->getPjesackiSemafor()->setAktivan(true);
    ispisRaskrsnica();
    this->getSemafor()->promjeniTrenutnoStanje();
    this->getPjesackiSemafor()->promjeniTrenutnoStanje();
    bool pocetak = true;
    bool isVozila, isPjesaci;
    int trajanjeStanja;
    while (1) {
        isVozila = this->daLiImaMinVozila();
        isPjesaci = this->daLiImaMinPjesaka();
        ispisRaskrsnicaVrijednosti(this->getSemafor()->getTrenutnoStanje()->getStanjeString(), this->getPjesackiSemafor()->getTrenutnoStanje()->getStanjeString(), this->isNovoVozilo(), this->isNoviPjesak(), this->getBrojVozila(), this->getBrojPjesaka());
        if (this->getPjesackiSemafor()->getTrenutnoStanje()->getStanje() != Stanje::ZELENO) {
            if (this->getSemafor()->getTrenutnoStanje()->getStanje() != Stanje::CRVENO || pocetak) {
                pocetak = false;
                trajanjeStanja = this->trajanjeStanja(this->getSemafor()->getTrenutnoStanje()->getStanje(), false, isPjesaci);
                std::cout << "Semafor " << this->getSemafor()->getTrenutnoStanje()->getStanjeString() << " trajanje: " << trajanjeStanja << std::endl;
                if (!isPjesaci && this->getSemafor()->getTrenutnoStanje()->getStanje() == Stanje::ZELENO) {
                    std::cout << "Nema puno pjesaka! Produzeno trajanje ZELENOG na semaforu!" << std::endl;
                }
                if (this->getSemafor()->getTrenutnoStanje()->getStanje() == Stanje::ZELENO) {
                    this->setBrojVozila(0);
                    std::cout << "RESETOVAN BROJ VOZILA NA 0!" << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::seconds(trajanjeStanja));
            }
            this->getSemafor()->promjeniTrenutnoStanje();
        }
        if (this->getSemafor()->getTrenutnoStanje()->getStanje() == Stanje::CRVENO) {
            if (this->getPjesackiSemafor()->getTrenutnoStanje()->getStanje() == Stanje::ZELENO) {
                trajanjeStanja = this->trajanjeStanja(this->getPjesackiSemafor()->getTrenutnoStanje()->getStanje(), true, isVozila);
                std::cout << "Pjesacki semafor" << this->getPjesackiSemafor()->getTrenutnoStanje()->getStanjeString() << " trajanje: " << trajanjeStanja << std::endl;
                if (!isVozila) {
                    std::cout << "Nema puno vozila! Produzeno trajanje ZELENOG na pjesackom semaforu!" << std::endl;
                }
                this->setBrojPjesaka(0);
                std::cout << "RESETOVAN BROJ PJESAKA NA 0!" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(trajanjeStanja));
            }
            if (this->getSemafor()->getTrenutnoStanje()->getStanje() == Stanje::CRVENO && this->getPjesackiSemafor()->getTrenutnoStanje()->getStanje() == Stanje::CRVENO) {
                std::cout << "------------------------------------------------------------------------" << std::endl;
                ispisRaskrsnicaVrijednosti(this->getSemafor()->getTrenutnoStanje()->getStanjeString(), this->getPjesackiSemafor()->getTrenutnoStanje()->getStanjeString(), this->isNovoVozilo(), this->isNoviPjesak(), this->getBrojVozila(), this->getBrojPjesaka());
            }
            this->getPjesackiSemafor()->promjeniTrenutnoStanje();
        }
        std::cout << "------------------------------------------------------------------------" << std::endl;
        std::thread pjesaci([&]() {
            this->simulirajDolazakPjesaka(trajanjeStanja);
            });

        pjesaci.detach();
        std::thread vozila([&]() {
            this->simulirajDolazakVozila(trajanjeStanja);
            });

        vozila.detach();
    }
}

int Raskrsnica::trajanjeStanja(Stanje stanje, bool pjesacki, bool novoVoziloIliPjesak) {
    switch (stanje) {
        case Stanje::CRVENO: return CRVENO;
        case Stanje::CRVENO_ZUTO: return CRVENO_ZUTO;
        case Stanje::ZUTO: return ZUTO;
        case Stanje::ZELENO: {
            if (pjesacki) {
                if (novoVoziloIliPjesak) {
                    return MIN_ZELENO_PJESACI;
                }
                return MAX_ZELENO_PJESACI;
            }
            else {
                if (novoVoziloIliPjesak) {
                    return MIN_ZELENO_VOZILA;
                }
                return MAX_ZELENO_VOZILA;
            }
        }
    }
}

bool Raskrsnica::daLiImaMinVozila() const {
    return this->getBrojVozila() >= MIN_VOZILA;
}

bool Raskrsnica::daLiImaMinPjesaka() const {
    return this->getBrojPjesaka() >= MIN_PJESAKA;
}

void Raskrsnica::simulirajDolazakPjesaka(int trajanje) {
    int brojPjesaka = rand() % (trajanje / 2);
    brojPjesaka = std::min(std::max(brojPjesaka, 0), 5);
    for (int i = 0; i < brojPjesaka; i++) {
        std::cout << "Detektovan je novi pjesak!" << std::endl;
        this->povecajBrojPjesaka();
    }
}

void Raskrsnica::simulirajDolazakVozila(int trajanje) {
    int brojVozila = rand() % (trajanje / 2);
    brojVozila = std::min(std::max(brojVozila, 0), 3);
    for (int i = 0; i < brojVozila; i++) {
        std::cout << "Detektovano je novo vozilo!" << std::endl;
        this->povecajBrojVozila();
    }
}