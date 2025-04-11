#ifndef FITXA_H
#define FITXA_H

#include "posicio.h"
#include "moviment.h"
#include <vector>

using namespace std;

enum TipusFitxa { NORMAL, DAMA, BUIT };
enum ColorFitxa { BLANCA, NEGRA, SENSE_COLOR };

class Fitxa
{
private:
    TipusFitxa tipus;
    ColorFitxa color;
    vector<Moviment> movimentsValids;

public:
    Fitxa(TipusFitxa t = BUIT, ColorFitxa c = SENSE_COLOR);
    
    void setTipus(TipusFitxa t);
    void setColor(ColorFitxa c);
    void promouADama();
    
    TipusFitxa getTipus() const;
    ColorFitxa getColor() const;
    vector<Moviment> getMovimentsValids() const;
    
    void afegeixMovimentValid(const Moviment& m);
    void netejaMoviments();
};

#endif