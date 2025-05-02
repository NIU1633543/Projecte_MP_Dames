/**
* FITXER posicio.h
* AUTOR Hugo Aguilar
* DATA 01/05/2025
* Aquest fitxer defineix la classe Posició.
*/

#ifndef POSICIO_H
#define POSICIO_H

#include <string>
#include <iostream>

using namespace std;

/**
 * @brief Classe que representa una posició en el tauler de dames.
 * Les coordenades s'emmagatzemen en format intern (fila 0 és la part superior).
 */
class Posicio
{
private:
    int fila;    ///< Fila al tauler (0-7).
    int columna; ///< Columna al tauler (0-7, on 0='a').

public:
    /**
     * @brief Constructor per defecte. Inicialitza a posició no vàlida.
     */
    Posicio() : fila(-1), columna(-1) {}
    
    /**
     * @brief Constructor des de string (ex: "a3").
     * @param pos String en format lletra+nombre (ex: "b5").
     */
    Posicio(const string& pos);
    
    /**
     * @brief Constructor des de coordenades numèriques.
     * @param f Fila (0-7).
     * @param c Columna (0-7).
     */
    Posicio(int f, int c);
    
    /**
     * @brief Obté la fila en format intern.
     * @return Enter entre 0 (superior) i 7 (inferior).
     */
    int getFila() const;
    
    /**
     * @brief Obté la columna en format intern.
     * @return Enter entre 0 ('a') i 7 ('h').
     */
    int getColumna() const;
    
    /**
     * @brief Compara dues posicions.
     * @param other Altra posició a comparar.
     * @return true si són iguals.
     */
    bool operator==(const Posicio& other) const;
    
    /**
     * @brief Converteix la posició a un string llegible (ex: "a1").
     * @return String en format lletra+nombre.
     */
    string toString() const;

    // Sobrecàrrega de l'operador de sortida
    // L'operador << és una funció externa (no és un mètode de la classe Posició).
    // Però necessita accedir a dades internes de Posició (com els valors de fila i columna, que són privats).
    // Al declarar-la com a friend dins de la classe,
    // s’autoritza aquesta funció externa a accedir als membres privats.
    friend ostream& operator<<(ostream& os, const Posicio& pos);
};

#endif