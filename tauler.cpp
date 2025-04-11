#include "tauler.h"
#include <fstream>

// Constructor: Inicialitza tot el tauler amb fitxes BUIT i color SENSE_COLOR
Tauler::Tauler()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            tauler[i][j] = Fitxa(); // Totes les posicions comencen buides i sense color
        }
    }
}

// --- MÈTODE inicialitza ---
void Tauler::inicialitza(const string& nomFitxer)
{
    ifstream fitxer(nomFitxer); // 1. Obrir fitxer en mode lectura
    
    if (!fitxer.is_open())
    { // Verificar si s'ha pogut obrir el fitxer
        return; // Si no es pot obrir, no fem res
    }

    string linia;
    while (getline(fitxer, linia))
    {   // 2. Llegir cada línia del fitxer
        // 3. Processar cada línia:
        // Format esperat: "TipusFitxa Posicio" (ex: "O a1", "X b3")
        size_t espai = linia.find(' ');
        if (espai == string::npos) continue; // Ignorar línies mal formades (rompe la iteración)

        // Extreure tipus de fitxa i posició
        string tipusStr = linia.substr(0, espai);
        string posStr = linia.substr(espai + 1);
        
        // Convertir string a objecte Posicio (ex: "a1" → fila 7, columna 0)
        Posicio pos(posStr); 

        // Determinar tipus i color de la fitxa
        TipusFitxa tipus;
        ColorFitxa color;
        if (tipusStr == "O")        // Fitxa normal blanca
        {
            tipus = NORMAL;
            color = BLANCA;
        }
        else if (tipusStr == "X")   // Fitxa normal negra
        {
            tipus = NORMAL;
            color = NEGRA;
        }
        else if (tipusStr == "D")   // Dama blanca
        {
            tipus = DAMA;
            color = BLANCA;
        }
        else if (tipusStr == "R")   // Dama negra
        {
            tipus = DAMA;
            color = NEGRA;
        }
        else
        {
            continue; // Tipus desconegut, ignorar (rompe la iteración)
        }

        // Col·locar la fitxa al tauler
        if (pos.getFila() >= 0 && pos.getFila() < 8 && pos.getColumna() >= 0 && pos.getColumna() < 8)
        {
            tauler[pos.getFila()][pos.getColumna()] = Fitxa(tipus, color);
        }
    }
    
    fitxer.close(); // 4. Tancar fitxer
}

// --- Helpers para movimientos ---
/**
 * @brief Verifica si una posición está dentro de los límites del tablero.
 * @param pos Posición a verificar.
 * @return true si 0 ≤ fila < 8 y 0 ≤ columna < 8.
 */
bool Tauler::esDinsTauler(const Posicio& pos) const
{
    int f = pos.getFila();
    int c = pos.getColumna();
    return f >= 0 && f < 8 && c >= 0 && c < 8;
}

/**
 * @brief Verifica si una casilla está vacía.
 * @param pos Posición a verificar.
 * @return true si la casilla es de tipo BUIT.
 */
bool Tauler::esCasellaBuida(const Posicio& pos) const
{
    return tauler[pos.getFila()][pos.getColumna()].getTipus() == BUIT;
}

/**
 * @brief Devuelve el color contrario al especificado.
 * @param color Color actual (BLANCA/NEGRA).
 * @return BLANCA si el color es NEGRA, y viceversa.
 */
ColorFitxa Tauler::getColorContrari(ColorFitxa color) const
{
    return (color == BLANCA) ? NEGRA : BLANCA;
    // OPERADOR TERNARIO
    // variable = (condición) ? valor_si_verdadero : valor_si_falso;
}

// --- Movimientos Normales ---
/**
 * @brief Calcula los movimientos válidos para una ficha normal.
 * Para fichas normales:
 * - Movimientos simples: 1 casilla diagonal adelante (dirección según color).
 * - Capturas: Saltar sobre una ficha contraria a una casilla vacía.
 * - Saltos múltiples: Encadenar capturas si es posible.
 * @param fitxa Referencia a la ficha actual.
 * @param pos Posición actual de la ficha.
 */
void Tauler::calculaMovimentsNormals(Fitxa& fitxa, const Posicio& pos)
{
    int direccio = (fitxa.getColor() == BLANCA) ? -1 : 1; // Blancas suben, negras bajan
    Posicio desti;

    // Movimientos simples (sin captura)
    for (int dc : {-1, 1})
    { // Diagonal izquierda y derecha
        desti = Posicio(pos.getFila() + direccio, pos.getColumna() + dc);
        if (esDinsTauler(desti) && esCasellaBuida(desti))
        {
            Moviment m;
            m.afegeixPas(desti);
            fitxa.afegeixMovimentValid(m);
        }
    }

    // Capturas
    for (int dc : {-1, 1})
    {
        Posicio salt(pos.getFila() + direccio, pos.getColumna() + dc);
        desti = Posicio(pos.getFila() + 2*direccio, pos.getColumna() + 2*dc);
        
        if (esDinsTauler(salt) && esDinsTauler(desti))
        {
            Fitxa fSalt = tauler[salt.getFila()][salt.getColumna()];
            if (fSalt.getColor() == getColorContrari(fitxa.getColor()) && esCasellaBuida(desti))
            {
                Moviment m;
                m.afegeixPas(desti);
                m.afegeixCaptura(salt);
                fitxa.afegeixMovimentValid(m);
                
                // Saltos múltiples (recursivo)
                exploraSaltMultiples(fitxa, m, desti);
            }
        }
    }
}

// --- Movimientos Dama ---
/**
 * @brief Calcula los movimientos válidos para una dama.
 * 
 * Para damas:
 * - Movimientos libres en cualquier dirección diagonal.
 * - Capturas a distancia: Saltar sobre fichas contrarias con casilla vacía detrás.
 * - Capturas múltiples en todas las direcciones posibles.
 * 
 * @param fitxa Referencia a la dama.
 * @param pos Posición actual de la dama.
 */
void Tauler::calculaMovimentsDama(Fitxa& fitxa, const Posicio& pos) {
    // Explorar las 4 direcciones diagonales
    for (int df : {-1, 1})
    {    // Dirección vertical (delta fila)
        for (int dc : {-1, 1})
        { // Dirección horizontal (delta columna)

          // Esto serían 4 iteraciones:
          // 1. Abajo e izquierda
          // 2. Abajo y derecha
          // 3. Arriba e izquierda
          // 4. Abajo y derecha

            bool trobatContrari = false;
            Posicio actual = pos;
            bool movimentValid = true;

            // Moverse en la dirección mientras sea válido
            while (movimentValid)
            {
                actual = Posicio(actual.getFila() + df, actual.getColumna() + dc);
                movimentValid = esDinsTauler(actual);

                if (!movimentValid) continue; // Salir si está fuera (rompe la iteración)

                if (esCasellaBuida(actual))
                {
                    if (!trobatContrari)
                    { // Movimiento libre sin captura
                        Moviment m;
                        m.afegeixPas(actual);
                        fitxa.afegeixMovimentValid(m);
                    }
                }
                else
                {
                    // Verificar si es aliada
                    if (tauler[actual.getFila()][actual.getColumna()].getColor() == fitxa.getColor())
                    {
                        movimentValid = false; // Bloquear dirección
                        continue; // Rompe la iteración, pasa a la siguiente
                    }

                    if (!trobatContrari)
                    { // Primera ficha contraria encontrada
                        trobatContrari = true;
                        Posicio salt = actual;
                        Posicio destiPotencial(salt.getFila() + df, salt.getColumna() + dc);

                        // Verificar captura válida
                        if (esDinsTauler(destiPotencial) && esCasellaBuida(destiPotencial))
                        {
                            Moviment m;
                            m.afegeixPas(destiPotencial);
                            m.afegeixCaptura(salt);
                            fitxa.afegeixMovimentValid(m);
                            exploraSaltMultiples(fitxa, m, destiPotencial);
                        }
                        movimentValid = false; // Solo una captura por dirección
                    }
                }
            } // Fin del while
        } // Fin del for dc
    } // Fin del for df
}

// --- Función Principal ---
/**
 * @brief Actualiza todos los movimientos válidos para todas las fichas del tablero.
 * Recorre cada casilla del tablero:
 * - Si está vacía, la ignora.
 * - Si contiene una ficha, calcula sus movimientos según su tipo (normal/dama).
 */
void Tauler::actualitzaMovimentsValids()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Fitxa& fitxa = tauler[i][j];
            fitxa.netejaMoviments();
            
            if (fitxa.getTipus() == BUIT) continue; // Rompe la iteración, pasa a la siguiente
            
            Posicio pos(i, j);
            if (fitxa.getTipus() == NORMAL)
            {
                calculaMovimentsNormals(fitxa, pos);
            }
            else
            {
                calculaMovimentsDama(fitxa, pos);
            }
        }
    }
}

// --- Mover Ficha ---
/**
 * @brief Mueve una ficha desde una posición origen a una destino.
 * 
 * Pasos:
 * 1. Verifica si el destino está en los movimientos válidos de la ficha.
 * 2. Si es válido:
 *    - Mueve la ficha al destino.
 *    - Elimina las fichas capturadas.
 *    - Promociona a dama si llega a la última fila.
 * 
 * @param origen Posición inicial de la ficha.
 * @param desti Posición destino.
 * @return true si el movimiento se realizó con éxito.
 */
bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    Fitxa& fitxa = tauler[origen.getFila()][origen.getColumna()];
    bool movimentValid = false;
    Moviment movimentSeleccionat;
    bool trobat = false; // Variable de control para el bucle

    // Buscar el movimiento válido
    for (const Moviment& m : fitxa.getMovimentsValids())
    {
        if (!trobat && m.getCami().back() == desti)
        {
            movimentSeleccionat = m;
            movimentValid = true;
            trobat = true; // Detener la búsqueda sin break
        }
    }

    if (movimentValid)
    {
        // Aplicar movimiento
        tauler[desti.getFila()][desti.getColumna()] = fitxa;
        tauler[origen.getFila()][origen.getColumna()] = Fitxa();

        // Eliminar capturas
        for (const Posicio& captura : movimentSeleccionat.getCaptures())
        {
            tauler[captura.getFila()][captura.getColumna()] = Fitxa();
        }

        // Promoción a dama
        bool esBlanca = (fitxa.getColor() == BLANCA && desti.getFila() == 0);
        bool esNegra = (fitxa.getColor() == NEGRA && desti.getFila() == 7);

        if (esBlanca || esNegra)
        {
            fitxa.promouADama();
        }
    }

    return movimentValid; // Único return
}