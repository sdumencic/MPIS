#ifndef ZASTITA_H
#define ZASTITA_H
#include "Rastavljac.h"
#include "Prekidac.h"
#include "APU.h"
#include <vector>

class Zastita
{
    private:
        bool stanje;

    public:
        Zastita();
        virtual ~Zastita();
        bool getStanje();
        void upaliZastitu(std::vector<Rastavljac*>, Prekidac &);
        void ugasiZastitu(APU, std::vector<Rastavljac*>, Prekidac &);

    protected:


};

#endif // ZASTITA_H
