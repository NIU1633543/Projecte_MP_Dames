#include "moviment.h"

// Afegeix una posició al camí del moviment
void Moviment::afegeixPas(const Posicio& pos)
{
    cami.push_back(pos);  // Emmagatzema la posició a la llista de passos
}

// Afegeix una posició on s'ha capturat una fitxa contrària
void Moviment::afegeixCaptura(const Posicio& pos)
{
    captures.push_back(pos);  // Emmagatzema la posició capturada
}

// Retorna una còpia del camí complet del moviment
vector<Posicio> Moviment::getCami() const
{
    vector<Posicio> camiCopia = cami;  // Còpia per mantenir encapsulació
    return camiCopia;
}

// Retorna una còpia de totes les captures d'aquest moviment
vector<Posicio> Moviment::getCaptures() const
{
    vector<Posicio> capturesCopia = captures;  // Còpia per mantenir encapsulació
    return capturesCopia;
}

// Verifica si el moviment és vàlid (conté almenys un pas)
bool Moviment::esValid() const
{
    bool tePassos = !cami.empty();  // Moviment vàlid si té com a mínim un pas
    return tePassos;
}