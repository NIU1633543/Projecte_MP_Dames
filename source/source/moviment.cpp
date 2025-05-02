/**
* FITXER moviment.cpp
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer implementa els mètodes de la classe Moviment.
*/

#include "moviment.h"

// Afegeix una posició al camí del moviment
void Moviment::afegeixPas(const Posicio& pos)
{
    cami.push_back(pos);
}

// Registra una posició on s'ha capturat una fitxa
void Moviment::afegeixCaptura(const Posicio& pos)
{
    captures.push_back(pos);
}

// Retorna una còpia del camí per mantenir encapsulació
vector<Posicio> Moviment::getCami() const
{
    return cami;
}

// Retorna una còpia de les captures per mantenir encapsulació
vector<Posicio> Moviment::getCaptures() const
{
    return captures;
}

// Determina si el moviment té almenys un pas
bool Moviment::esValid() const
{
    return !cami.empty();
}