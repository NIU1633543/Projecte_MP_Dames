#include "fitxa.h"

// Constructor: Inicialitza la fitxa amb el tipus i color especificats (per defecte BUIT i SENSE_COLOR)
Fitxa::Fitxa(TipusFitxa t, ColorFitxa c) : tipus(t), color(c) {}

// Estableix el tipus de la fitxa (NORMAL, DAMA o BUIT)
void Fitxa::setTipus(TipusFitxa t)
{ 
    tipus = t; 
}

// Estableix el color de la fitxa (BLANCA, NEGRA o SENSE_COLOR)
void Fitxa::setColor(ColorFitxa c)
{ 
    color = c; 
}

// Promou la fitxa a DAMA si actualment és NORMAL
void Fitxa::promouADama()
{ 
    bool esNormal = (tipus == NORMAL);
    if(esNormal) { tipus = DAMA; }
}

// Retorna el tipus actual de la fitxa
TipusFitxa Fitxa::getTipus() const
{ 
    TipusFitxa tipusActual = tipus;
    return tipusActual; 
}

// Retorna el color actual de la fitxa
ColorFitxa Fitxa::getColor() const
{ 
    ColorFitxa colorActual = color;
    return colorActual; 
}

// Retorna una còpia de tots els moviments vàlids registrats per a la fitxa
vector<Moviment> Fitxa::getMovimentsValids() const
{ 
    vector<Moviment> llistaMoviments = movimentsValids;
    return llistaMoviments; 
}

// Afegeix un moviment vàlid a la llista interna de la fitxa
void Fitxa::afegeixMovimentValid(const Moviment& m)
{
    bool movimentNoBuit = m.esValid();
    if(movimentNoBuit) { movimentsValids.push_back(m); }
}

// Neteja tots els moviments vàlids emmagatzemats per a la fitxa
void Fitxa::netejaMoviments()
{
    movimentsValids.clear();
}