#ifndef APU_H
#define APU_H
#include "Rastavljac.h"
#include "Prekidac.h"
#include <vector>

class APU
{
    private:
        bool stanje;
    public:
        APU();
        virtual ~APU();
        void upaliPrekidac(std::vector<Rastavljac*>, Prekidac);
        bool getStanje();
        void setStanje(bool);

};

#endif // APU_H
