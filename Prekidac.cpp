#include "Prekidac.h"
#include "Rastavljac.h"
#include "RastavljacUzemljenja.h"
#include "LinijskiRastavljac.h"
#include "SabirnickiRastavljac.h"
#include <string>
#include <typeinfo>
#include <iostream>

using namespace std;

Prekidac::Prekidac()
{
    this->setStanje(false);
    this->setUpravljanje(true);
    this->setBioUpaljen(false);
}

Prekidac::~Prekidac()
{
    //dtor
}

bool Prekidac::getBioUpaljen(){
    return this->bioUpaljen;
}

void Prekidac::setBioUpaljen(bool jeli){
    this->bioUpaljen = jeli;
}

bool Prekidac::getStanje()
{
    return this->stanje;
}

void Prekidac::setStanje(bool novo_stanje)
{
    this->stanje = novo_stanje;
}

bool Prekidac::getUpravljanje()
{
    return this->upravljanje;
}

void Prekidac::setUpravljanje(bool novo_uprav)
{
    this->upravljanje = novo_uprav;
}

std::string Prekidac::getUpravljanjeString()
{
    // 1 daljinsko, 0 lokalno
    if(this->getUpravljanje() == 0){
        return "Lokalno";
    }
    else{
        return "Daljinsko";
    }
}

void Prekidac::upaliSve(std::vector<Rastavljac*> rast)
{
    this->setStanje(true);
    //this->setBioUpaljen(true);

    for(auto it : rast){
        if(typeid(*it) == typeid(RastavljacUzemljenja)){
            (*it).setStanje(false);
        }
        else{
            (*it).setStanje(true);
        }
    }
}
void Prekidac::ugasiSve(std::vector<Rastavljac*> rast)
{
    this->setStanje(false);
    //this->setBioUpaljen(false);

    for(auto it : rast){
        if(typeid(*it) == typeid(RastavljacUzemljenja)){
            (*it).setStanje(true);
        }
        else{
            (*it).setStanje(false);
        }
    }
}
