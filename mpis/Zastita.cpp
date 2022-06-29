#include "Zastita.h"
#include "Prekidac.h"
#include <vector>
#include <iostream>

Zastita::Zastita()
{
    this->stanje = false;
}

Zastita::~Zastita()
{
    //dtor
}

bool Zastita::getStanje()
{
    return this->stanje;
}
void Zastita::upaliZastitu(std::vector<Rastavljac*> rast,Prekidac &prekid)
{
    this->stanje = true;
    if(prekid.getStanje()){
        prekid.setBioUpaljen(true);
        prekid.ugasiSve(rast);
    }
}
void Zastita::ugasiZastitu(APU apu, std::vector<Rastavljac*> rast, Prekidac &prekid)
{
    this->stanje = false;
    if(apu.getStanje() && prekid.getBioUpaljen()){
        prekid.upaliSve(rast);
    }
}
