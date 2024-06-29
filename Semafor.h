#pragma once
#include "SemaforStanje.h"
#include "PrijelazStanja.h"
class Semafor
{
private:
	SemaforStanje *trenutnoStanje;
	std::vector<SemaforStanje> stanja;
	std::map<Stanje, std::vector<Stanje>> prijelazi;
	bool aktivan;
	bool greska;
public:
	Semafor()
	{
		trenutnoStanje = new SemaforStanje();
		stanja = SemaforStanje::ucitajStanja("stanja.txt");
		prijelazi = PrijelazStanja::ucitajPrijelaze("prijelazi.txt");
		aktivan = false;
		greska = false;
	}
	SemaforStanje* getTrenutnoStanje();
	std::vector<SemaforStanje> getStanja();
	std::map<Stanje, std::vector<Stanje>> getPrijelazi();
	bool isAktivan() const;
	bool isGreska() const;
	void setTrenutnoStanje(SemaforStanje *s);
	void setStanja(std::vector<SemaforStanje> s);
	void setPrijelazi(std::map<Stanje, std::vector<Stanje>> p);
	void setAktivan(bool a);
	void setGreska(bool g);
	void promjeniTrenutnoStanje();
	void simulirajPrijelazeStanjaRucno();
	void simulirajPrijelazeStanja();
	void testirajPrijelaz();
	~Semafor() {
		delete trenutnoStanje;
	}
};

