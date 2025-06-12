/**
* FITXER fitxa.cpp
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer implementa els mètodes de la classe Fitxa.
*/


#include "GraphicManager.h" // Necesario para IMAGE_NAME y GraphicManager
#include "info_joc.hpp"
#include "fitxa.h"

// Constructor: inicialitza tipus i color
Fitxa::Fitxa(TipusFitxa t, ColorFitxa c) : tipus(t), color(c) { }

void Fitxa::visualitza(int fila, int columna) const
{
    IMAGE_NAME grafic = GRAFIC_NUM_MAX;

    // Determinar el gráfico según el tipo y color de la ficha
    if (tipus == NORMAL)
        grafic = (color == BLANCA) ? GRAFIC_FITXA_BLANCA : GRAFIC_FITXA_NEGRA;
    else if (tipus == DAMA)
        grafic = (color == BLANCA) ? GRAFIC_DAMA_BLANCA : GRAFIC_DAMA_NEGRA;

    // Calcular las coordenadas en píxeles
    if (grafic != GRAFIC_NUM_MAX)
    {
        int posX = POS_X_TAULER + CASELLA_INICIAL_X + ((columna - 1) * AMPLADA_CASELLA);
        int posY = POS_Y_TAULER + CASELLA_INICIAL_Y + ((fila - 1) * ALCADA_CASELLA);
        GraphicManager::getInstance()->drawSprite(grafic, posX, posY);
    }
}

// Canvia el tipus de la fitxa
void Fitxa::setTipus(TipusFitxa t)
{
    tipus = t;
}

// Canvia el color de la fitxa
void Fitxa::setColor(ColorFitxa c)
{
    color = c;
}

// Converteix la fitxa a DAMA si és NORMAL
void Fitxa::promouADama()
{
    if (tipus == NORMAL)
    {
        tipus = DAMA;
    }
}

// Retorna el tipus actual
TipusFitxa Fitxa::getTipus() const
{
    return tipus;
}

// Retorna el color actual
ColorFitxa Fitxa::getColor() const
{
    return color;
}

// Retorna una còpia dels moviments vàlids
std::vector<Moviment> Fitxa::getMovimentsValids() const
{
    return movimentsValids;
}

// Afegeix un moviment vàlid si no és buit
void Fitxa::afegeixMovimentValid(const Moviment& m)
{
    if (m.esValid())
    {
        movimentsValids.push_back(m);
    }
}

// Elimina tots els moviments emmagatzemats
void Fitxa::netejaMoviments()
{
    movimentsValids.clear();
}
