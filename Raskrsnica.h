#pragma once
#include "Semafor.h"
#include "PjesackiSemafor.h"
class Raskrsnica
{
private:
	Semafor *semafor;
	PjesackiSemafor *pjesackiSemafor;
	int brojVozila;
	int brojPjesaka;
	bool noviPjesak;
	bool novoVozilo;
	std::vector<PrijelazStanja> sinhroniziraniPrijelazi;
public:
	Raskrsnica()
	{
		semafor = new Semafor();
		pjesackiSemafor = new PjesackiSemafor();
		brojVozila = 0;
		brojPjesaka = 0;
		noviPjesak = false;
		novoVozilo = false;
		sinhroniziraniPrijelazi = PrijelazStanja::ucitajSinhroniziranePrijelaze("raskrsnica_sinhronizacija.txt");
	}
	Semafor* getSemafor();
	PjesackiSemafor* getPjesackiSemafor();
	int getBrojVozila() const;
	int getBrojPjesaka() const;
	bool isNovoVozilo() const;
	bool isNoviPjesak() const;
	std::vector<PrijelazStanja> getSinhroniziraniPrijelazi();
	void setSemafor(Semafor* s);
	void setPjesackiSemafor(PjesackiSemafor* p);
	void setBrojVozila(int n);
	void setBrojPjesaka(int n);
	void setNovoVozilo(bool n);
	void setNoviPjesak(bool n);
	void setSinhroniziraniPrijelazi(std::vector<PrijelazStanja> s);
	void povecajBrojVozila();
	void povecajBrojPjesaka();
	void simulirajRaskrsnicu();
	int trajanjeStanja(Stanje s, bool p, bool n);
	bool daLiImaMinVozila() const;
	bool daLiImaMinPjesaka() const;
	void simulirajDolazakPjesaka(int t);
	void simulirajDolazakVozila(int t);
	~Raskrsnica() {
		delete semafor;
		delete pjesackiSemafor;
	}
};

