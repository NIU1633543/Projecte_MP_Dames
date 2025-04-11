#include "posicio.h"

// Función auxiliar: Convierte un carácter a minúscula
char toLower(char c)
{
    bool esMajuscula = (c >= 'A' && c <= 'Z');
    
    char resultat = c;
    // ASCII: Las mayúsculas (A=65, Z=90) se convierten en minúsculas (a=97) sumando 32
    if (esMajuscula) { resultat = c + 32; }

    return resultat;
}

// Constructor: Convierte string (ex: "a1") a coordenades internas
Posicio::Posicio(const string& pos)
{
    char lletra = toLower(pos[0]);  // Asegura minúscula
    columna = lletra - 'a';         // 'a'→0, 'b'→1...
    
    int numFila = pos[1] - '0';     // '1' → 1 (enter)
    fila = 8 - numFila;             // "a1" es fila 7 en el tablero (índex 0)
}

// Constructor con coordenadas explícitas
Posicio::Posicio(int f, int c) : fila(f), columna(c) {}

// Retorna la fila segons el sistema intern (0=primera fila superior)
int Posicio::getFila() const
{
    int filaActual = fila;
    return filaActual;
}

// Retorna la columna segons el sistema intern (0=primera columna 'a')
int Posicio::getColumna() const
{
    int columnaActual = columna;
    return columnaActual;
}

// Operador d'igualtat: Compara fila i columna
bool Posicio::operator==(const Posicio& other) const
{
    bool iguals = (fila == other.fila) && (columna == other.columna);
    return iguals;
}

// Converteix la posició a string (ex: 7,0 -> "a1")
string Posicio::toString() const
{
    char lletra = 'a' + columna;
    int numVisible = 8 - fila;
    string resultat = string(1, lletra) + to_string(numVisible);
    return resultat;
}