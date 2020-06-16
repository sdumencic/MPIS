#ifndef PREKIDAC_H
#define PREKIDAC_H
#include "Rastavljac.h"
#include "RastavljacUzemljenja.h"
#include "LinijskiRastavljac.h"
#include "SabirnickiRastavljac.h"
#include <string>
#include <vector>


class Prekidac
{
    private:
        bool stanje;
        bool upravljanje; // 1 daljinsko, 0 lokalno
        bool bioUpaljen;

    public:
        Prekidac();
        virtual ~Prekidac();
        void upaliSve(std::vector<Rastavljac*>);
        void ugasiSve(std::vector<Rastavljac*>);
        bool getStanje();
        void setStanje(bool);
        bool getUpravljanje();
        void setUpravljanje(bool);
        std::string getUpravljanjeString();

        bool getBioUpaljen();
        void setBioUpaljen(bool);


    protected:


};

#endif // PREKIDAC_H
