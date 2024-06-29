#include "SemaforStanje.h"
#include <fstream>
#include <iostream>
#include <sstream>

int SemaforStanje::getTrajanje() const
{
    return this->trajanje;
}

Stanje SemaforStanje::getStanje() const
{
    return this->stanje;
}

void SemaforStanje::setTrajanje(int t)
{
    this->trajanje = t;
}

void SemaforStanje::setStanje(Stanje s)
{
    this->stanje = s;
}

std::string SemaforStanje::getStanjeString()
{
    switch (stanje) {
    case Stanje::MIROVANJE:
            return "MIROVANJE";
            break;
        case Stanje::CRVENO:
            return "CRVENO";
            break;
        case Stanje::CRVENO_ZUTO:
            return "CRVENO_ZUTO";
            break;
        case Stanje::ZELENO:
            return "ZELENO";
            break;
        case Stanje::ZUTO:
            return "ZUTO";
            break;
        case Stanje::ZUTO_BLINKAJUCE:
            return "ZUTO_BLINKAJUCE";
            break;
        default:
            return "GRESKA";
    }
}

std::vector<SemaforStanje> SemaforStanje::ucitajStanja(const std::string& nazivFajla)
{
    std::vector<SemaforStanje> stanja;
    std::ifstream datoteka(nazivFajla);
    if (!datoteka.is_open()) {
        std::cerr << "Greška kod otvaranja datoteke!" << std::endl;
        return stanja;
    }
    std::string linija;
    while (getline(datoteka, linija)) {
        std::istringstream ss(linija);
        std::string stanjeStr;
        int trajanje;
        if (std::getline(ss, stanjeStr, ',') && (ss >> trajanje)) {
            auto it = stanjaString.find(stanjeStr);
            if (it != stanjaString.end()) {
                SemaforStanje stanje(it->second, trajanje);
                stanja.push_back(stanje);
            }
            else {
                std::cerr << "Pogresno stanje! " << stanjeStr << std::endl;
            }
        }
        else {
            std::cerr << "Greška prilikom èitanja linije: " << linija << std::endl;
        }
    }

    datoteka.close();

    return stanja;
}
