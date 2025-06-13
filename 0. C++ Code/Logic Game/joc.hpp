/**
* FITXER joc.hpp
* AUTOR Hugo Aguilar
* DATA 11/06/2025
* Aquest fitxer defineix la classe Joc.
*/

#ifndef JOC_H
#define JOC_H

#include "tauler.h"
#include "cuamoviments.h"
#include "info_joc.hpp"

/**
 * @brief Classe que coordina la lògica i la interacció del joc de dames.
 */
class Joc
{
private:
    Tauler m_tauler;               ///< Gestió del tauler
    CuaMoviments m_cua;            ///< Cua de moviments per al mode replay
    ModeJoc m_mode;                ///< Mode de joc (normal o replay)
    ColorFitxa m_torn;             ///< Torn actual (blanca o negra)
    bool m_finalPartida;           ///< Indica si la partida ha acabat
    ColorFitxa m_guanyador;        ///< Color guanyador en cas de final
    bool m_fitxaSeleccionada;      ///< Indica si hi ha una fitxa seleccionada
    Posicio m_posFitxaSeleccionada;///< Posició de la fitxa seleccionada
    vector<Posicio> m_movimentsValids; ///< Llista de moviments vàlids
    string m_nomFitxerMoviments;   ///< Nom del fitxer per guardar moviments
    string m_missatge;             ///< Missatge informatiu o d'error
    bool m_prevMouseStatus;        ///< Guarda l'estat anterior del ratolí

    /**
     * @brief Comprova si no queden moviments possibles per finalitzar la partida.
     */
    void comprovaFinalPartida();

    /**
     * @brief Converteix coordenades del ratolí a fila i columna del tauler.
     * @param mouseX Coordenada X del ratolí en píxels.
     * @param mouseY Coordenada Y del ratolí en píxels.
     * @param fila Sortida: fila calculada al tauler.
     * @param columna Sortida: columna calculada al tauler.
     * @return true si les coordenades estan dins del tauler.
     */
    bool mouseToBoard(int mouseX, int mouseY, int &fila, int &columna);

public:
    /**
     * @brief Constructor: inicialitza el joc en estat per defecte.
     */
    Joc();

    /**
     * @brief Inicialitza el joc amb mode i fitxers de configuració.
     * @param mode Mode de joc (normal o replay).
     * @param nomFitxerTauler Ruta al fitxer amb la configuració inicial del tauler.
     * @param nomFitxerMoviments Ruta al fitxer per carregar o guardar moviments.
     */
    void inicialitza(ModeJoc mode, const string &nomFitxerTauler, const string &nomFitxerMoviments);

    /**
     * @brief Actualitza l'estat del joc en resposta a esdeveniments del ratolí.
     * @param mousePosX Posició X del ratolí.
     * @param mousePosY Posició Y del ratolí.
     * @param mouseStatus true si s'ha fet clic.
     * @return false si no es vol sortir del bucle principal.
     */
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);

    /**
     * @brief Finalitza el joc i guarda els moviments si escau.
     */
    void finalitza();
};

#endif
