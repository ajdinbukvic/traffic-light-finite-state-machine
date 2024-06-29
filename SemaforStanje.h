#pragma once
#include <string>
#include <vector>
#include "Stanje.h"

class SemaforStanje
{
private:
	Stanje stanje;
	int trajanje;
public:
	SemaforStanje() : stanje(Stanje::MIROVANJE), trajanje(-1) {}
	SemaforStanje(Stanje s, int t) : stanje(s), trajanje(t) {}
	int getTrajanje() const;
	Stanje getStanje() const;
	void setTrajanje(int t);
	void setStanje(Stanje s);
	std::string getStanjeString();
	static std::vector<SemaforStanje> ucitajStanja(const std::string& nazivFajla);
};
