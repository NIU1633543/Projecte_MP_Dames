#ifndef TAULER_H
#define TAULER_H

#include "fitxa.h"
#include "posicio.h"
#include "moviment.h"
#include <vector>
#include <string>

using namespace std;

class Tauler
{
private:
    Fitxa tauler[8][8];

    // --- Funciones auxiliares privadas ---
    /**
     * @brief Verifica si una posición está dentro de los límites del tablero.
     * @param pos Posición a verificar.
     * @return true si 0 ≤ fila < 8 y 0 ≤ columna < 8.
     */
    bool esDinsTauler(const Posicio& pos) const;

    /**
     * @brief Verifica si una casilla está vacía.
     * @param pos Posición a verificar.
     * @return true si la casilla es de tipo BUIT.
     */
    bool esCasellaBuida(const Posicio& pos) const;

    /**
     * @brief Actualiza todos los movimientos válidos para todas las fichas del tablero.
     * Recorre cada casilla del tablero:
     * - Si está vacía, la ignora.
     * Si contiene una ficha, calcula sus movimientos según su tipo (normal/dama).
     */
    ColorFitxa getColorContrari(ColorFitxa color) const;

    /**
     * @brief Calcula los movimientos válidos para una ficha normal.
     * Para fichas normales:
     * - Movimientos simples: 1 casilla diagonal adelante (dirección según color).
     * - Capturas: Saltar sobre una ficha contraria a una casilla vacía.
     * - Saltos múltiples: Encadenar capturas si es posible.
     * @param fitxa Referencia a la ficha actual.
     * @param pos Posición actual de la ficha.
     * */
    void calculaMovimentsNormals(Fitxa& fitxa, const Posicio& pos);

    /**
     * @brief Calcula los movimientos válidos para una dama.
     * Para damas:
     * - Movimientos libres en cualquier dirección diagonal.
     * - Capturas a distancia: Saltar sobre fichas contrarias con casilla vacía detrás.
     * - Capturas múltiples en todas las direcciones posibles.
     * @param fitxa Referencia a la dama.
     * @param pos Posición actual de la dama.
     */
    void calculaMovimentsDama(Fitxa& fitxa, const Posicio& pos);

    void exploraSaltMultiples(Fitxa& fitxa, Moviment& movimentActual, const Posicio& posActual);

public:
    // --- Constructor ---
    Tauler();

    // --- Métodos públicos principales ---
    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();

    /**
     * @brief Mueve una ficha desde una posición origen a una destino.
     * 
     * Pasos:
     * 1. Verifica si el destino está en los movimientos válidos de la ficha.
     * 2. Si es válido:
     * - Mueve la ficha al destino.
     * - Elimina las fichas capturadas.
     * - Promociona a dama si llega a la última fila.
     * 
     * @param origen Posición inicial de la ficha.
     * @param desti Posición destino.
     * @return true si el movimiento se realizó con éxito.
     */
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    string toString() const;
};

#endif