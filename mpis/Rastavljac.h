#ifndef RASTAVLJAC_H
#define RASTAVLJAC_H


class Rastavljac
{
    private:
        bool stanje;

    public:
        Rastavljac();
        virtual ~Rastavljac();
        bool getStanje();
        void setStanje(bool);
};

#endif // RASTAVLJAC_H
