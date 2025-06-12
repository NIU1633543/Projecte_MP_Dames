/**
* FITXER cuamoviments.hpp
* AUTOR Hugo Aguilar
* DATA 11/06/2025
* Aquest fitxer defineix la classe CuaMoviments.
*/

#ifndef CUAMOVIMENTS_H
#define CUAMOVIMENTS_H

#include "moviment.h"
#include <vector>

using namespace std;

/**
 * @brief Cua enllaçada per emmagatzemar objectes Moviment.
 * Permet afegir i extreure moviments en ordre FIFO.
 */
class CuaMoviments
{
private:
    struct Node
    {
        Moviment moviment;  ///< Moviment emmagatzemat al node
        Node *seg;          ///< Punter al node següent
        /**
         * @brief Constructor del node.
         * @param m Moviment a emmagatzemar.
         */
        Node(const Moviment &m) : moviment(m), seg(nullptr) {}
    };

    Node *primer;  ///< Punter al primer node de la cua
    Node *ultim;   ///< Punter a l'últim node de la cua

public:
    /**
     * @brief Construeix una cua buida.
     */
    CuaMoviments();

    /**
     * @brief Destrueix la cua alliberant la memòria dels nodes.
     */
    ~CuaMoviments();

    /**
     * @brief Afegeix un nou moviment al final de la cua.
     * @param moviment Moviment a afegir.
     */
    void afegeix(const Moviment &moviment);

    /**
     * @brief Extreu el primer moviment de la cua.
     * @param moviment Referència on s'emmagatzemarà el moviment extret.
     * @return true si s'ha extret un moviment, false si la cua estava buida.
     */
    bool treu(Moviment &moviment);

    /**
     * @brief Consulta si la cua està buida.
     * @return true si la cua no conté elements.
     */
    bool estaBuida() const;

    /**
     * @brief Converteix la cua en un vector de moviments.
     * @return Vector amb tots els moviments en ordre FIFO.
     */
    vector<Moviment> aVector() const;
};

#endif