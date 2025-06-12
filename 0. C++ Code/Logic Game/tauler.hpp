/**
* FITXER tauler.hpp
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer defineix la classe Tauler.
*/

#ifndef TAULER_H
#define TAULER_H

#include "fitxa.h"
#include "posicio.h"
#include "moviment.h"
#include "GraphicManager.h" // For GraphicManager class, IMAGE_NAME enum, and GRAFIC_TAULER
#include "info_joc.hpp"     // For POS_X_TAULER, POS_Y_TAULER, etc.
#include <vector>
#include <string>

using namespace std;

/**
 * @brief Classe que representa el tauler de joc de dames.
 * Gestiona la colocació de fitxes, moviments vàlids i lògica del joc.
 */
class Tauler
{
private:
    Fitxa* tauler[8][8]; ///< Matriu 8x8 que emmagatzema les fitxes.

    /**
     * @brief Verifica si una posició es troba dins dels límits del tauler.
     * @param pos Posició a verificar.
     * @return true si la posició és vàlida.
     */
    bool esDinsTauler(const Posicio& pos) const;

    /**
     * @brief Comprova si una casilla està buida.
     * @param pos Posició a verificar.
     * @return true si la casella no conté cap fitxa.
     */
    bool esCasellaBuida(const Posicio& pos) const;

    /**
     * @brief Obté el color contrari al especificat.
     * @param color Color actual.
     * @return ColorFitxa contrari (BLANCA ↔ NEGRA).
     */
    ColorFitxa getColorContrari(ColorFitxa color) const;

    /**
     * @brief Calcula els moviments vàlids per a una fitxa normal.
     * @param fitxa Fitxa a analitzar.
     * @param pos Posició actual de la fitxa.
     */
    void calculaMovimentsNormals(Fitxa& fitxa, const Posicio& pos);

    /**
     * @brief Calcula els moviments vàlids per a una dama.
     * @param fitxa Dama a analitzar.
     * @param pos Posició actual de la dama.
     */
    void calculaMovimentsDama(Fitxa& fitxa, const Posicio& pos);

    /**
     * @brief Explora salts múltiples després d'una captura.
     * @param fitxa Fitxa que realitza el moviment.
     * @param movimentActual Moviment en curs.
     * @param posActual Posició actual després del salt.
     * @param direccio Direcció del moviment (0 per dama).
     */
    void exploraSaltMultiples(Fitxa& fitxa, Moviment& movimentActual, const Posicio& posActual, int direccio = 0);

public:
    /**
     * @brief Constructor. Inicialitza un tauler buit.
     */
    Tauler();

    /**
     * @brief Destructor. Allibera la memòria de les fitxes.
     */
    ~Tauler();

    /**
     * @brief Inicialitza el tauler des d'un fitxer.
     * @param nomFitxer Nom del fitxer amb la configuració inicial.
     */
    void inicialitza(const string& nomFitxer);

    /**
     * @brief Actualitza tots els moviments vàlids per a totes les fitxes.
     */
    void actualitzaMovimentsValids();

    /**
     * @brief Mou una fitxa d'una posició origen a destí si és vàlid.
     * @param origen Posició inicial de la fitxa.
     * @param desti Posició final desitjada.
     * @return true si el moviment s'ha realitzat amb èxit.
     */
    bool mouFitxa(const Posicio& origen, const Posicio& desti);

    /**
     * @brief Obté les posicions possibles per a una fitxa.
     * @param origen Posició de la fitxa.
     * @param nPosicions [out] Nombre de posicions possibles.
     * @param posicionsPossibles [out] Array amb les posicions vàlides.
     */
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);

    /**
     * @brief Converteix el tauler a una representació en text.
     * @return String amb el tauler en format llegible.
     */
    string toString() const;

    /**
     * @brief Visualitza el tauler gràficament.
     * Utilitza la classe GraphicManager per dibuixar el tauler i les fitxes.
     */
    void visualitza() const;

    /**
     * @brief Obté la fitxa en una posició específica.
     * @param pos Posició de la fitxa a obtenir.
     * @return Referència a la fitxa a la posició indicada.
     */
    Fitxa& getFitxa(const Posicio& pos);
};

#endif