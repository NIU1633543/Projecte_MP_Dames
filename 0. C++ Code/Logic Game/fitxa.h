/**
* FITXER fitxa.h
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer defineix la classe Fitxa.
*/

#ifndef FITXA_H
#define FITXA_H

#include "posicio.h"
#include "moviment.h"
#include <vector>

using namespace std;

/**
 * @brief Tipus possibles d'una fitxa en el joc de dames.
 */
enum TipusFitxa { NORMAL, DAMA, BUIT };

/**
 * @brief Colors possibles d'una fitxa.
 */
enum ColorFitxa { BLANCA, NEGRA, SENSE_COLOR };

/**
 * @brief Classe que representa una fitxa del joc de dames.
 * Gestiona el tipus, color i moviments vàlids de la fitxa.
 */
class Fitxa
{
private:
    TipusFitxa tipus;                ///< Tipus actual de la fitxa.
    ColorFitxa color;                ///< Color de la fitxa.
    vector<Moviment> movimentsValids; ///< Llista de moviments vàlids.

public:
    void visualitza(int posX, int posY) const;
    /**
     * @brief Constructor per defecte. Crea una fitxa buida.
     * @param t Tipus inicial (per defecte BUIT).
     * @param c Color inicial (per defecte SENSE_COLOR).
     */
    Fitxa(TipusFitxa t = BUIT, ColorFitxa c = SENSE_COLOR);
    
    /**
     * @brief Estableix el tipus de la fitxa.
     * @param t Nou tipus (NORMAL, DAMA o BUIT).
     */
    void setTipus(TipusFitxa t);
    
    /**
     * @brief Estableix el color de la fitxa.
     * @param c Nou color (BLANCA, NEGRA o SENSE_COLOR).
     */
    void setColor(ColorFitxa c);
    
    /**
     * @brief Promou la fitxa a DAMA si és de tipus NORMAL.
     */
    void promouADama();
    
    /**
     * @brief Obté el tipus actual de la fitxa.
     * @return TipusFitxa actual.
     */
    TipusFitxa getTipus() const;
    
    /**
     * @brief Obté el color actual de la fitxa.
     * @return ColorFitxa actual.
     */
    ColorFitxa getColor() const;
    
    /**
     * @brief Obté tots els moviments vàlids registrats.
     * @return Còpia del vector de moviments vàlids.
     */
    vector<Moviment> getMovimentsValids() const;
    
    /**
     * @brief Afegeix un moviment vàlid a la llista.
     * @param m Moviment vàlid a afegir.
     */
    void afegeixMovimentValid(const Moviment& m);
    
    /**
     * @brief Neteja tots els moviments emmagatzemats.
     */
    void netejaMoviments();
};

#endif