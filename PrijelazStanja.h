#pragma once
#include "SemaforStanje.h"
class PrijelazStanja
{
private:
	Stanje stanjeIz;
	Stanje stanjeU;
public:
	PrijelazStanja() : stanjeIz(Stanje::MIROVANJE), stanjeU(Stanje::MIROVANJE) {}
	PrijelazStanja(Stanje s1, Stanje s2) : stanjeIz(s1), stanjeU(s2) {}
	Stanje getStanjeIz() const;
	Stanje getStanjeU() const;
	void setStanjeIz(Stanje s);
	void setStanjeU(Stanje s);
	static std::map<Stanje, std::vector<Stanje>> ucitajPrijelaze(const std::string& nazivFajla);
	static std::vector<PrijelazStanja> ucitajSinhroniziranePrijelaze(const std::string& nazivFajla);
};

