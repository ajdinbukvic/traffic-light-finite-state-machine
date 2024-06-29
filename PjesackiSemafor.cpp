#include "PjesackiSemafor.h"

SemaforStanje* PjesackiSemafor::getTrenutnoStanjePjesacki()
{
    return this->trenutnoStanjePjesacki;
}

void PjesackiSemafor::setTrenutnoStanjePjesacki(SemaforStanje* s)
{
    this->trenutnoStanjePjesacki = s;
}
