#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.h"
#include <vector>

using namespace std;

class Moviment
{
private:
    vector<Posicio> cami;
    vector<Posicio> captures;
public:
    Moviment() {}
    
    void afegeixPas(const Posicio& pos);
    void afegeixCaptura(const Posicio& pos);
    
    vector<Posicio> getCami() const;
    vector<Posicio> getCaptures() const;
    
    bool esValid() const;
};

#endif