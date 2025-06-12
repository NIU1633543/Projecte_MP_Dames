/**
* FITXER moviment.h
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer defineix la classe Moviment.
*/

#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.h"
#include <vector>

using namespace std;

/**
 * @brief Classe que representa un moviment en el joc de dames.
 * Conté el camí recorregut i les captures realitzades.
 */
class Moviment
{
private:
    vector<Posicio> cami;      ///< Seqüència de posicions del moviment.
    vector<Posicio> captures;  ///< Posicions on s'han capturat fitxes.

public:
    /**
     * @brief Constructor per defecte. Crea un moviment buit.
     */
    Moviment() {}

    Moviment(const Posicio& origen, const Posicio& desti) {
        cami.push_back(origen);
        cami.push_back(desti);
    };
    
    /**
     * @brief Afegeix una posició al camí del moviment.
     * @param pos Posició a afegir.
     */
    void afegeixPas(const Posicio& pos);
    
    /**
     * @brief Registra una posició on s'ha capturat una fitxa.
     * @param pos Posició de la captura.
     */
    void afegeixCaptura(const Posicio& pos);
    
    /**
     * @brief Obté una còpia del camí complet.
     * @return Vector amb totes les posicions del camí.
     */
    vector<Posicio> getCami() const;
    
    /**
     * @brief Obté una còpia de les captures realitzades.
     * @return Vector amb posicions de captures.
     */
    vector<Posicio> getCaptures() const;
    
    /**
     * @brief Verifica si el moviment és vàlid.
     * @return true Si conté almenys un pas al camí.
     */
    bool esValid() const;
};

#endif