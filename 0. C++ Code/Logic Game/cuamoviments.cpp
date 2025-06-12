/**
* FITXER moviment.cpp
* AUTOR Hugo Aguilar
* DATA 11/06/2025
* Aquest fitxer implementa els mètodes de la classe CuaMoviments.
*/

#include "cuamoviments.h"

// Constructor: inicialitza els punters primer i ultim a nullptr.
CuaMoviments::CuaMoviments() : primer(nullptr), ultim(nullptr) {}

// Destructor: allibera tots els nodes de la cua.
CuaMoviments::~CuaMoviments()
{
    while (primer != nullptr)
    {
        Node *aux = primer;
        primer = primer->seg;
        delete aux;
    }
}

// Afegeix un moviment al final de la cua.
void CuaMoviments::afegeix(const Moviment &moviment)
{
    Node *nou = new Node(moviment);
    if (estaBuida())
        primer = nou;
    else
        ultim->seg = nou;
    ultim = nou;
}

// Extreu el primer moviment de la cua i l'emmagatzema a 'moviment'.
bool CuaMoviments::treu(Moviment &moviment)
{
    if (estaBuida())
        return false;

    moviment = primer->moviment;
    Node *aux = primer;
    primer = primer->seg;
    delete aux;

    if (primer == nullptr)
        ultim = nullptr;

    return true;
}

// Comprova si la cua està buida.
bool CuaMoviments::estaBuida() const
{
    return primer == nullptr;
}

// Genera un vector amb tots els moviments de la cua.
vector<Moviment> CuaMoviments::aVector() const
{
    vector<Moviment> resultat;
    Node *actual = primer;
    while (actual != nullptr)
    {
        resultat.push_back(actual->moviment);
        actual = actual->seg;
    }
    return resultat;
}