/**
* FITXER posicio.cpp
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer implementa els mètodes de la classe Posició.
*/

#include "posicio.h"
#include <string>

// Converteix un caràcter a minúscula (si és majúscula).
static char toLower(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return c + 32;
    }
    return c;
}

// Sobrecàrrega de l'operador << per mostrar la posició en format text.
ostream& operator<<(ostream& os, const Posicio& pos)
{
    os << pos.toString();
    return os;
}

// Construeix una Posicio des d'un string (ex: "a3").
Posicio::Posicio(const string& pos)
{
    char lletra = toLower(pos[0]);
    columna = lletra - 'a';
    int numFila = pos[1] - '0';
    fila = 8 - numFila;
}

// Construeix una Posicio des de coordenades numèriques.
Posicio::Posicio(int f, int c) : fila(f), columna(c)
{
}

// Retorna el valor de la fila (0 = primera fila superior).
int Posicio::getFila() const
{
    return fila;
}

// Retorna el valor de la columna (0 = columna 'a').
int Posicio::getColumna() const
{
    return columna;
}

// Compara si dues posicions són iguals (mateixa fila i columna).
bool Posicio::operator==(const Posicio& other) const
{
    return (fila == other.fila) && (columna == other.columna);
}

// Converteix la posició a un string en format de dames (ex: "a1").
string Posicio::toString() const
{
    char lletra = 'a' + columna;
    int numVisible = 8 - fila;
    return string(1, lletra) + to_string(numVisible);
}