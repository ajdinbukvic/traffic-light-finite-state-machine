#include "PrijelazStanja.h"
#include <fstream>
#include <iostream>
#include <sstream>

Stanje PrijelazStanja::getStanjeIz() const
{
    return this->stanjeIz;
}

Stanje PrijelazStanja::getStanjeU() const
{
    return this->stanjeU;
}

void PrijelazStanja::setStanjeIz(Stanje s)
{
    this->stanjeIz = s;
}

void PrijelazStanja::setStanjeU(Stanje s)
{
    this->stanjeU = s;
}

std::map<Stanje, std::vector<Stanje>> PrijelazStanja::ucitajPrijelaze(const std::string& nazivFajla)
{
    std::map<Stanje, std::vector<Stanje>> prijelazi;
    std::ifstream datoteka(nazivFajla);
    if (!datoteka.is_open()) {
        std::cerr << "Greška kod otvaranja datoteke!" << std::endl;
        return prijelazi;
    }
    std::string linija;
    while (getline(datoteka, linija)) {
        std::istringstream ss(linija);
        std::string stanjeIzStr;
        std::string stanjeUStr;
        if (std::getline(ss, stanjeIzStr, ',') && std::getline(ss, stanjeUStr)) {
            Stanje stanjeIz = stanjaString[stanjeIzStr];
            Stanje stanjeU = stanjaString[stanjeUStr];
            prijelazi[stanjeIz].push_back(stanjeU);
        }
        else {
            std::cerr << "Greška prilikom èitanja linije: " << linija << std::endl;
        }
    }

    datoteka.close();

    return prijelazi;
}

std::vector<PrijelazStanja> PrijelazStanja::ucitajSinhroniziranePrijelaze(const std::string& nazivFajla)
{
    std::vector<PrijelazStanja> prijelazi;
    std::ifstream datoteka(nazivFajla);
    if (!datoteka.is_open()) {
        std::cerr << "Greška kod otvaranja datoteke!" << std::endl;
        return prijelazi;
    }
    std::string linija;
    while (getline(datoteka, linija)) {
        std::istringstream ss(linija);
        std::string stanjeIzStr;
        std::string stanjeUStr;
        if (std::getline(ss, stanjeIzStr, ',') && std::getline(ss, stanjeUStr)) {
            Stanje stanjeIz = stanjaString[stanjeIzStr];
            Stanje stanjeU = stanjaString[stanjeUStr];
            prijelazi.push_back(PrijelazStanja(stanjeIz, stanjeU));
        }
        else {
            std::cerr << "Greška prilikom èitanja linije: " << linija << std::endl;
        }
    }

    datoteka.close();

    return prijelazi;
}
