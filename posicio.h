#ifndef POSICIO_H
#define POSICIO_H

#include <string>

using namespace std;

class Posicio
{
private:
    int fila;
    int columna;
public:
    // Constructor por defecto
    Posicio() : fila(-1), columna(-1) {}
    Posicio(const string& pos);
    Posicio(int f, int c);
    
    int getFila() const;
    int getColumna() const;
    
    bool operator==(const Posicio& other) const;
    string toString() const;
};

#endif