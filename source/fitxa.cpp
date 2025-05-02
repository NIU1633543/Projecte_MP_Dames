/**
* FITXER fitxa.cpp
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer implementa els mètodes de la classe Fitxa.
*/


#include "fitxa.h"

// Constructor: inicialitza tipus i color
Fitxa::Fitxa(TipusFitxa t, ColorFitxa c) : tipus(t), color(c) { }

// Canvia el tipus de la fitxa
void Fitxa::setTipus(TipusFitxa t)
{
    tipus = t;
}

// Canvia el color de la fitxa
void Fitxa::setColor(ColorFitxa c)
{
    color = c;
}

// Converteix la fitxa a DAMA si és NORMAL
void Fitxa::promouADama()
{
    if (tipus == NORMAL)
    {
        tipus = DAMA;
    }
}

// Retorna el tipus actual
TipusFitxa Fitxa::getTipus() const
{
    return tipus;
}

// Retorna el color actual
ColorFitxa Fitxa::getColor() const
{
    return color;
}

// Retorna una còpia dels moviments vàlids
std::vector<Moviment> Fitxa::getMovimentsValids() const
{
    return movimentsValids;
}

// Afegeix un moviment vàlid si no és buit
void Fitxa::afegeixMovimentValid(const Moviment& m)
{
    if (m.esValid())
    {
        movimentsValids.push_back(m);
    }
}

// Elimina tots els moviments emmagatzemats
void Fitxa::netejaMoviments()
{
    movimentsValids.clear();
}
