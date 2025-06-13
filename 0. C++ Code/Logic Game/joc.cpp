/**
 * FITXER moviment.cpp
 * AUTOR Hugo Aguilar
 * DATA 11/06/2025
 * Aquest fitxer implementa els mètodes de la classe Joc.
 */

#include "joc.hpp"
#include "GraphicManager.h"
#include <fstream>
#include <sstream>

// Constructor: estableix estat inicial i carrega la configuració per defecte.
Joc::Joc() : m_mode(MODE_JOC_NONE),
             m_torn(BLANCA),
             m_finalPartida(false),
             m_guanyador(SENSE_COLOR),
             m_fitxaSeleccionada(false),
             m_posFitxaSeleccionada(-1, -1),
             m_prevMouseStatus(false)
{
    inicialitza(MODE_JOC_NORMAL, "./data/Games/tauler_inicial.txt", "./data/Games/moviments.txt");
}

// Converteix coordenades del ratolí a fila i columna del tauler.
bool Joc::mouseToBoard(int mouseX, int mouseY, int &fila, int &columna)
{
    int boardX = mouseX - (POS_X_TAULER + CASELLA_INICIAL_X);
    int boardY = mouseY - (POS_Y_TAULER + CASELLA_INICIAL_Y);

    if (boardX < 0 || boardY < 0)
        return false;

    columna = boardX / AMPLADA_CASELLA;
    fila = boardY / ALCADA_CASELLA;

    return (fila >= 0 && fila < NUM_FILES_TAULER &&
            columna >= 0 && columna < NUM_COLS_TAULER);
}

// Inicialitza o reinicia el joc segons el mode.
void Joc::inicialitza(ModeJoc mode, const string &nomFitxerTauler, const string &nomFitxerMoviments)
{
    m_mode = mode;
    m_torn = BLANCA;
    m_finalPartida = false;
    m_guanyador = SENSE_COLOR;
    m_fitxaSeleccionada = false;
    m_movimentsValids.clear();
    m_nomFitxerMoviments = nomFitxerMoviments;

    m_tauler.inicialitza(nomFitxerTauler);
    m_tauler.actualitzaMovimentsValids();

    if (mode == MODE_JOC_REPLAY)
    {
        ifstream fitxer(nomFitxerMoviments);
        if (!fitxer.is_open())
        {
            cerr << "ERROR: Can't open file: " << nomFitxerTauler << endl;
            return;
        }
        if (fitxer.is_open())
        {
            string linia;
            while (getline(fitxer, linia))
            {
                stringstream ss(linia);
                string sorg, sdest;
                ss >> sorg >> sdest;
                Posicio origen(sorg);
                Posicio desti(sdest);
                Moviment mov;
                mov.afegeixPas(origen);
                mov.afegeixPas(desti);
                m_cua.afegeix(mov);
            }
            fitxer.close();
        }
    }
}

// Gestiona esdeveniments del ratolí i actualitza la lògica i la vista del joc.
bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    // Dibujar elementos estéticos
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
    m_tauler.visualitza();
    int fila, columna;

    bool clickEdge = mouseStatus && !m_prevMouseStatus;
    m_prevMouseStatus = mouseStatus;

    if (m_mode == MODE_JOC_NORMAL && mouseToBoard(mousePosX, mousePosY, fila, columna))
    {
        Posicio posClic(fila, columna);
        Fitxa &fitxa = m_tauler.getFitxa(posClic);

        if (mouseStatus)
        {
            if (!m_fitxaSeleccionada)
            {
                // Seleccionar ficha si es del jugador actual
                if (fitxa.getTipus() != BUIT && fitxa.getColor() == m_torn)
                {
                    m_fitxaSeleccionada = true;
                    m_posFitxaSeleccionada = posClic;

                    // Obtener movimientos válidos
                    m_movimentsValids.clear();
                    int nPosicions = 0;
                    Posicio posicionsPossibles[20];
                    m_tauler.getPosicionsPossibles(m_posFitxaSeleccionada, nPosicions, posicionsPossibles);

                    for (int i = 0; i < nPosicions; i++)
                    {
                        m_movimentsValids.push_back(posicionsPossibles[i]);
                    }
                }
            }
            else
            {
                // Mover ficha si el destino es válido
                bool destiValid = false;
                for (const Posicio &desti : m_movimentsValids)
                {
                    if (desti == posClic)
                    {
                        destiValid = true;
                        break;
                    }
                }

                if (destiValid)
                {
                    if (m_tauler.mouFitxa(m_posFitxaSeleccionada, posClic))
                    {
                        // Cambiar turno después de mover
                        m_torn = (m_torn == BLANCA) ? NEGRA : BLANCA;
                        m_cua.afegeix(Moviment(m_posFitxaSeleccionada, posClic));
                    }
                }

                // Reset selección
                m_fitxaSeleccionada = false;
                m_movimentsValids.clear();
            }
        }
    }

    if (m_mode == MODE_JOC_REPLAY && clickEdge)
    {
        // Si quedan movimientos por reproducir, saca el siguiente
        if (!m_cua.estaBuida())
        {
            Moviment mov;
            if (m_cua.treu(mov))
            {
                vector<Posicio> cami = mov.getCami();
                if (cami.size() >= 2)
                {
                    // mueve la pieza del primer al último paso
                    m_tauler.mouFitxa(cami.front(), cami.back());
                    // refresca movimientos y cambia turno
                    m_tauler.actualitzaMovimentsValids();
                    m_torn = (m_torn == BLANCA) ? NEGRA : BLANCA;
                    m_missatge.clear();
                }
            }
        }
        else
        {
            // ya no hay más movimientos
            m_missatge = "No more moves!";
        }
    }

    // Mostrar posiciones válidas si hay ficha seleccionada
    if (m_fitxaSeleccionada)
    {
        for (const Posicio &pos : m_movimentsValids)
        {
            int posX = POS_X_TAULER + CASELLA_INICIAL_X + (pos.getColumna() * AMPLADA_CASELLA);
            int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + (pos.getFila() * ALCADA_CASELLA);
            GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, static_cast<float>(posX), static_cast<float>(posY));
        }
    }

    // Mostrar información del juego
    int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
    string torn = (m_torn == BLANCA) ? "White" : "Black";
    string mode;
    if (m_mode == MODE_JOC_NORMAL)
        mode = "Normal";
    else if (m_mode == MODE_JOC_REPLAY)
        mode = "Replay";
    else
        mode = "None";
    string info = "Mode: " + mode + " | Turn: " + torn;

    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, static_cast<float>(POS_X_TAULER), static_cast<float>(posTextY), 0.8f, info);
    // Si hay mensaje, lo mostramos en rojo justo debajo
    if (!m_missatge.empty())
    {
        GraphicManager::getInstance()->drawFont(
            FONT_RED_30,
            static_cast<float>(POS_X_TAULER),
            static_cast<float>(posTextY + 30),
            0.8f,
            m_missatge);
    }

    // Comprobar si el juego ha terminado
    comprovaFinalPartida();
    return false;
}

// Comprova si la partida ha acabat sense moviments possibles.
void Joc::comprovaFinalPartida()
{
    bool teMovimentsBlanques = false;
    bool teMovimentsNegres = false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Fitxa fitxa = m_tauler.getFitxa(Posicio(i, j));
            if (!fitxa.getMovimentsValids().empty())
            {
                if (fitxa.getColor() == BLANCA)
                    teMovimentsBlanques = true;
                else if (fitxa.getColor() == NEGRA)
                    teMovimentsNegres = true;
            }
        }
    }

    if (!teMovimentsBlanques)
    {
        m_finalPartida = true;
        m_guanyador = NEGRA;
    }
    else if (!teMovimentsNegres)
    {
        m_finalPartida = true;
        m_guanyador = BLANCA;
    }
}

// Finalitza el joc i desa els moviments si escau.
void Joc::finalitza()
{
    if (m_mode == MODE_JOC_NORMAL && !m_cua.estaBuida())
    {
        ofstream fitxer(m_nomFitxerMoviments);
        if (fitxer.is_open())
        {
            vector<Moviment> moviments = m_cua.aVector();
            for (const Moviment &mov : moviments)
            {
                vector<Posicio> cami = mov.getCami();
                if (cami.size() >= 2)
                {
                    fitxer << cami[0].toString() << " " << cami.back().toString() << endl;
                }
            }
            fitxer.close();
        }
    }
}
