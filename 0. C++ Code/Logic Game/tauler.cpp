/**
 * FITXER tauler.cpp
 * AUTOR Hugo Aguilar
 * DATA 01/05/2025
 * Aquest fitxer implementa els mètodes de la classe Tauler.
 */

#include "tauler.h"
#include <fstream>
#include <sstream>

// Constructor: inicialitza totes les caselles com a BUIT
Tauler::Tauler()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            tauler[i][j] = new Fitxa();
}

// Destructor: allibera la memòria de les fitxes
Tauler::~Tauler()
{
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            delete tauler[i][j];
}



// Carrega la configuració del tauler des d'un fitxer
void Tauler::inicialitza(const string &nomFitxer)
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete tauler[i][j];
            tauler[i][j] = new Fitxa();
        }
    }

    ifstream fitxer(nomFitxer);
    if (!fitxer.is_open())
    {
        return;
    }

    string linia;
    while (getline(fitxer, linia)) // Llegeix una línia sencera del fitxer
    {
        size_t espai = linia.find(' '); // Busca la primera aparició d'un espai (' ')
        if (espai == string::npos)  // Si no es troba un espai, la línia es considera invàlida
                                    // (ja totes les línies són de l'estil O a3, X h7, etc.)
        {
            continue;
        }

        string tipusStr = linia.substr(0, espai);
        string posStr = linia.substr(espai + 1);
        Posicio pos(posStr);

        if (pos.getFila() < 0 || pos.getFila() >= 8 || pos.getColumna() < 0 || pos.getColumna() >= 8)
        {
            continue;
        }

        TipusFitxa tipus;
        ColorFitxa color;
        if (tipusStr == "O")
        {
            tipus = NORMAL;
            color = BLANCA;
        }
        else if (tipusStr == "X")
        {
            tipus = NORMAL;
            color = NEGRA;
        }
        else if (tipusStr == "D")
        {
            tipus = DAMA;
            color = BLANCA;
        }
        else if (tipusStr == "R")
        {
            tipus = DAMA;
            color = NEGRA;
        }
        else
        {
            continue;
        }

        tauler[pos.getFila()][pos.getColumna()]->setTipus(tipus);
        tauler[pos.getFila()][pos.getColumna()]->setColor(color);
    }
    fitxer.close();
}

// Actualitza els moviments vàlids per a totes les fitxes del tauler
void Tauler::visualitza() const
{
    for (int i = 0; i < NUM_FILES_TAULER; ++i)
    {
        for (int j = 0; j < NUM_COLS_TAULER; ++j)
        {
            Fitxa* f = tauler[i][j];
            if (f != nullptr && f->getTipus() != BUIT)
            {
                // i,j son 0-based; Fitxa::visualitza quiere 1-based:
                f->visualitza(i + 1, j + 1);
            }
        }
    }
}

// Actualitza els moviments vàlids per a totes les fitxes del tauler
Fitxa& Tauler::getFitxa(const Posicio& pos)
{
    return *tauler[pos.getFila()][pos.getColumna()];
}

// Verifica si una posició està dins del tauler
bool Tauler::esDinsTauler(const Posicio &pos) const
{
    int f = pos.getFila();
    int c = pos.getColumna();
    return (f >= 0 && f < 8 && c >= 0 && c < 8);
}

// Comprova si una casella està buida
bool Tauler::esCasellaBuida(const Posicio &pos) const
{
    return (tauler[pos.getFila()][pos.getColumna()]->getTipus() == BUIT);
}

// Retorna el color contrari al especificat
ColorFitxa Tauler::getColorContrari(ColorFitxa color) const
{
    return (color == BLANCA) ? NEGRA : BLANCA;
}

// Calcula els moviments vàlids per a una fitxa normal (no dama).
void Tauler::calculaMovimentsNormals(Fitxa &fitxa, const Posicio &pos)
{
    // Determina la direcció de moviment segons el color:
    // - Fitxes blanques: es mouen cap amunt (fila -1).
    // - Fitxes negres: es mouen cap avall (fila +1).
    int direccio = (fitxa.getColor() == BLANCA) ? -1 : 1;
    Posicio desti;

    // --- Moviments simples (sense captura) ---
    // Explora les dues direccions diagonals possibles (esquerra i dreta)
    for (int dc : {-1, 1})
    { // dc = diferència de columna (-1: esquerra, +1: dreta)
        desti = Posicio(pos.getFila() + direccio, pos.getColumna() + dc);

        // Verifica si el destí és vàlid:
        if (esDinsTauler(desti) && esCasellaBuida(desti))
        {
            Moviment m;
            m.afegeixPas(desti);           // Afegeix el destí al camí
            fitxa.afegeixMovimentValid(m); // Registra el moviment com a vàlid
        }
    }

    // --- Captures (salt sobre fitxa contrària) ---
    for (int dc : {-1, 1})
    {   // Explora diagonals esquerra i dreta
        // Posició de la fitxa contrària a saltar
        Posicio salt(pos.getFila() + direccio, pos.getColumna() + dc);
        // Destí després del salt (2 posicions en diagonal)
        desti = Posicio(pos.getFila() + 2 * direccio, pos.getColumna() + 2 * dc);

        // Verifica:
        // 1. El salt i el destí estan dins del tauler.
        // 2. La casella de salt conté una fitxa contrària.
        // 3. El destí està buit.
        if (esDinsTauler(salt) && esDinsTauler(desti))
        {
            const Fitxa& fSalt = *tauler[salt.getFila()][salt.getColumna()];
            if (fSalt.getColor() != SENSE_COLOR && fSalt.getColor() == getColorContrari(fitxa.getColor()) && esCasellaBuida(desti))
            {
                Moviment m;
                m.afegeixPas(desti);    // Destí final del salt
                m.afegeixCaptura(salt); // Fitxa contrària capturada
                fitxa.afegeixMovimentValid(m);

                // Explora possibles salts múltiples des del nou destí
                exploraSaltMultiples(fitxa, m, desti, direccio);
            }
        }
    }
}

// Explora salts múltiples després d'una captura
void Tauler::exploraSaltMultiples(Fitxa &fitxa, Moviment &movimentActual, const Posicio &posActual, int direccio)
{
    static int recursionDepth = 0; // Evita recursió infinita (màxim 10 nivells)
    if (recursionDepth > 10) return;
    recursionDepth++;

    ColorFitxa colorContrari = getColorContrari(fitxa.getColor());
    vector<pair<int, int>> direccions;

    // Determina direccions de moviment:
    // - Si és una fitxa normal (direccio != 0), només es mou endavant.
    // - Si és una dama (direccio = 0), es mou en totes 4 diagonals.
    if (direccio != 0)
    {
        direccions = {{direccio, -1}, {direccio, 1}};
    }
    else
    {
        direccions = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}}; // Direccions diagonals completes
    }

    // Explora cada direcció possible
    for (const pair<int, int> &dir : direccions)
    {
        int df = dir.first;  // Diferència de fila (ex: -1, +1)
        int dc = dir.second; // Diferència de columna (ex: -1, +1)

        Posicio salt(posActual.getFila() + df, posActual.getColumna() + dc);
        Posicio desti(salt.getFila() + df, salt.getColumna() + dc);

        // Verifica si el salt i el destí són vàlids:
        if (esDinsTauler(salt) && esDinsTauler(desti) && esCasellaBuida(desti))
        {
            const Fitxa &fitxaSalt = *tauler[salt.getFila()][salt.getColumna()];

            // Si la fitxa al salt és del color contrari, es pot capturar
            if (fitxaSalt.getTipus() != BUIT && fitxaSalt.getColor() == colorContrari)
            {
                Moviment nouMoviment = movimentActual;   // Còpia el moviment actual
                nouMoviment.afegeixPas(desti);           // Afegeix el nou destí
                nouMoviment.afegeixCaptura(salt);        // Registra la captura
                fitxa.afegeixMovimentValid(nouMoviment); // Afegeix el moviment a la fitxa

                // Explora recursivament nous salts des del destí
                exploraSaltMultiples(fitxa, nouMoviment, desti, direccio);
            }
        }
    }
    recursionDepth--; // Redueix la profunditat de recursió
}

void Tauler::calculaMovimentsDama(Fitxa &fitxa, const Posicio &pos)
{
    // Explora les 4 direccions diagonals possibles
    for (int df : {-1, 1})
    { // Diferència de fila: -1 (amunt) o +1 (avall)
        for (int dc : {-1, 1})
        {                                // Diferència de columna: -1 (esquerra) o +1 (dreta)
            bool trobatContrari = false; // Indica si s'ha trobat una fitxa contrària
            Posicio actual = pos;        // Posició actual durant l'exploració
            bool movimentValid = true;   // Controla si es pot continuar movent

            while (movimentValid)
            {
                actual = Posicio(actual.getFila() + df, actual.getColumna() + dc);
                movimentValid = esDinsTauler(actual);

                if (!movimentValid)
                    continue;

                // Casella buida: es pot moure si no s'ha trobat una fitxa contrària
                if (esCasellaBuida(actual))
                {
                    if (!trobatContrari)
                    {
                        Moviment m;
                        m.afegeixPas(actual);
                        fitxa.afegeixMovimentValid(m); // Moviment simple
                    }
                }
                // Casella ocupada: verifica si és capturable
                else
                {
                    // Si és una fitxa aliada, atura el moviment
                    if (tauler[actual.getFila()][actual.getColumna()]->getTipus() != BUIT && tauler[actual.getFila()][actual.getColumna()]->getColor() == fitxa.getColor())
                    {
                        movimentValid = false;
                        continue;
                    }

                    // Si és una fitxa contrària i no s'ha trobat cap abans
                    if (!trobatContrari)
                    {
                        trobatContrari = true;
                        Posicio salt = actual; // Posició de la fitxa a capturar
                        Posicio destiPotencial(salt.getFila() + df, salt.getColumna() + dc);

                        // Verifica si es pot saltar sobre la fitxa contrària
                        if (esDinsTauler(destiPotencial) && esCasellaBuida(destiPotencial))
                        {
                            Moviment m;
                            m.afegeixPas(destiPotencial); // Destí després del salt
                            m.afegeixCaptura(salt);       // Fitxa capturada
                            fitxa.afegeixMovimentValid(m);

                            // Explora salts múltiples des del nou destí
                            exploraSaltMultiples(fitxa, m, destiPotencial, 0); // 0 = dama
                        }
                        movimentValid = false; // Atura el moviment després de la captura
                    }
                }
            }
        }
    }
}

// Actualitza tots els moviments vàlids del tauler
void Tauler::actualitzaMovimentsValids()
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Fitxa &fitxa = *tauler[i][j];
            fitxa.netejaMoviments();

            if (fitxa.getTipus() == BUIT)
            {
                continue;
            }

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

// Realitza un moviment si és vàlid
bool Tauler::mouFitxa(const Posicio &origen, const Posicio &desti)
{
    Fitxa* fitxaAMoure = tauler[origen.getFila()][origen.getColumna()];

    bool movimentValid = false;
    Moviment movimentSeleccionat;
    bool trobatMovimentEnConcret = false;

    ColorFitxa colorJugador = fitxaAMoure->getColor();
    bool hiHaCapturesGlobals = false;
    vector<Posicio> fitxesAmbCapturesObligatories;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            Fitxa &f = *tauler[i][j];
            if (f.getColor() == colorJugador && f.getTipus() != BUIT)
            {
                for (const Moviment &m : f.getMovimentsValids())
                {
                    if (!m.getCaptures().empty())
                    {
                        // Utilitzem emplace_back per evitar crear una objecte de la classe Posició innecessari
                        // És el mateix que fer fitxesAmbCaptures.push_back(Posicio(i, j));
                        fitxesAmbCapturesObligatories.emplace_back(i, j);
                        hiHaCapturesGlobals = true;
                        break;
                    }
                }
            }
        }
    }

    // Buscar el moviment vàlid seleccionat
    for (const Moviment &m : fitxaAMoure->getMovimentsValids())
    {
        if (!trobatMovimentEnConcret && m.getCami().back() == desti)
        {
            movimentSeleccionat = m;
            movimentValid = true;
            trobatMovimentEnConcret = true;
        }
    }

    if (movimentValid)
    {
        // Aplicar el moviment
        delete tauler[desti.getFila()][desti.getColumna()]; // Eliminar la ficha (vacía) en destino
        tauler[desti.getFila()][desti.getColumna()] = fitxaAMoure;
        tauler[origen.getFila()][origen.getColumna()] = new Fitxa(); // Origen queda vacío

        // Eliminar fitxes capturades
        for (const Posicio &captura : movimentSeleccionat.getCaptures())
        {
            delete tauler[captura.getFila()][captura.getColumna()];
            tauler[captura.getFila()][captura.getColumna()] = new Fitxa();
        }

        // Promoció a dama si és necessari
        // fitxaAMoure (ahora en tauler[desti]) es la que se ha movido.
        // Solo promover si la ficha aún existe (no ha sido soplada inmediatamente).
        Fitxa* pFitxaDesti = tauler[desti.getFila()][desti.getColumna()];
        if (pFitxaDesti->getTipus() != BUIT) { // Comprobar si la ficha en destino no es ya vacía (por si acaso)
            bool esBlanca = (pFitxaDesti->getColor() == BLANCA && desti.getFila() == 0);
            bool esNegra = (pFitxaDesti->getColor() == NEGRA && desti.getFila() == 7);
            if (esBlanca || esNegra)
            {
                pFitxaDesti->promouADama();
            }
        }

        // Regla de "soplar" por incumplimiento de captura obligatoria
        bool fichaEnDestinoFueSoplada = false;
        if (hiHaCapturesGlobals && movimentSeleccionat.getCaptures().empty())
        {
            bool laFichaMovidaTeniaObligacion = false;
            for (const Posicio& posObligatoria : fitxesAmbCapturesObligatories) {
                if (posObligatoria == origen) { // La ficha que se movió (originalmente en 'origen') tenía obligación
                    laFichaMovidaTeniaObligacion = true;
                    break;
                }
            }

            if (laFichaMovidaTeniaObligacion) {
                // La ficha que se movió (ahora en 'desti') incumplió la obligación. Se sopla.
                delete tauler[desti.getFila()][desti.getColumna()]; // Elimina fitxaAMoure
                tauler[desti.getFila()][desti.getColumna()] = new Fitxa();
                fichaEnDestinoFueSoplada = true;
            } else {
                // La ficha movida no incumplió (o no tenía obligación directa),
                // pero otras fichas del jugador sí tenían obligación y no se movieron para capturar.
                // Se soplan esas otras fichas.
                for (const Posicio &posASoplar : fitxesAmbCapturesObligatories) {
                    // Asegurarse de no intentar soplar la posición de origen de la ficha que se movió,
                    // ya que está vacía y no es la infractora en este caso.
                    if (posASoplar != origen) {
                        delete tauler[posASoplar.getFila()][posASoplar.getColumna()];
                        tauler[posASoplar.getFila()][posASoplar.getColumna()] = new Fitxa();
                    }
                }
            }
        }

        // Eliminar la lógica confusa de "fitxesASoplar" que estaba aquí,
        // ya que su implementación era incorrecta o se basaba en una regla no estándar/clara.
        // Si se necesita una regla de "soplar por no encadenar captura múltiple",
        // debe diseñarse e implementarse cuidadosamente.

        // Actualizar todos los movimientos válidos DESPUÉS de todos los cambios en el tablero.
        actualitzaMovimentsValids();
    }
    return movimentValid;
}

// Obté posicions possibles per a una fitxa
void Tauler::getPosicionsPossibles(const Posicio &origen, int &nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;
    // Obté la fitxa situada a la posició d'origen
    Fitxa &fitxa = *tauler[origen.getFila()][origen.getColumna()];
    // Recupera tots els moviments vàlids precalculats per a aquesta fitxa
    vector<Moviment> moviments = fitxa.getMovimentsValids();

    // Recorre tots els elements de moviments
    for (const Moviment &mov : moviments)
    {
        // Assegura que el moviment té almenys una posició destí.
        if (!mov.getCami().empty())
        {
            // Obtenim destí de tots els moviments possibles
            Posicio desti = mov.getCami().back();
            bool duplicat = false;

            for (int i = 0; i < nPosicions; i++)
            {
                // Mirem si hi ha destins duplicats
                if (posicionsPossibles[i] == desti)
                {
                    duplicat = true;
                    break;
                }
            }

            if (!duplicat)
            {
                posicionsPossibles[nPosicions++] = desti;
            }
        }
    }
}

// Converteix el tauler a un string visual
string Tauler::toString() const
{
    string result;
    for (int i = 0; i < 8; ++i)
    {
        result += to_string(8 - i) + " | ";
        for (int j = 0; j < 8; ++j)
        {
            const Fitxa& f = *tauler[i][j];
            if (f.getTipus() == BUIT)
            {
                result += "_ ";
            }
            else
            {
                if (f.getColor() == BLANCA)
                {
                    // Si és normal, esquerra. És a dir, "O"
                    // Si és dama, dreta. És a dir "D"
                    result += (f.getTipus() == NORMAL) ? "O " : "D ";
                }
                else
                {
                    // Si és normal, esquerra. És a dir, "X"
                    // Si és dama, dreta. És a dir "R"
                    result += (f.getTipus() == NORMAL) ? "X " : "R ";
                }
            }
        }
        result += "\n";
    }
    result += "  a b c d e f g h\n";
    return result;
}