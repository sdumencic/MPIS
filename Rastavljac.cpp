#include "Rastavljac.h"

Rastavljac::Rastavljac()
{
    stanje = false;
}

Rastavljac::~Rastavljac()
{
    //dtor
}
bool Rastavljac::getStanje()
{
    return this->stanje;
}
void Rastavljac::setStanje(bool novo_stanje)
{
    this->stanje = novo_stanje;
}
