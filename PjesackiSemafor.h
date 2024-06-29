#pragma once
#include "Semafor.h"
class PjesackiSemafor : public Semafor
{
private:
	SemaforStanje* trenutnoStanjePjesacki;
public:
	PjesackiSemafor()
	{
		trenutnoStanjePjesacki = new SemaforStanje();
		this->setStanja(SemaforStanje::ucitajStanja("stanja_pjesacki.txt"));
		this->setPrijelazi(PrijelazStanja::ucitajPrijelaze("prijelazi_pjesacki.txt"));
	}
	SemaforStanje* getTrenutnoStanjePjesacki();
	void setTrenutnoStanjePjesacki(SemaforStanje* s);
};

