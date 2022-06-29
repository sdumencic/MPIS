#include "APU.h"
#include "Prekidac.h"
#include "Rastavljac.h"
#include <vector>

APU::APU()
{
    this->stanje = true;
}

APU::~APU()
{
    //dtor
}
void APU::upaliPrekidac(std::vector<Rastavljac*> rast, Prekidac prekid)
{
    prekid.upaliSve(rast);
}

bool APU::getStanje(){
    return this->stanje;
}

void APU::setStanje(bool novoStanje){
    this->stanje = novoStanje;
}
