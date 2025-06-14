//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./joc.hpp"
#include "./info_joc.hpp"


int main(int argc, const char* argv[])
{
    //Menú por consola
    std::cout << "Select game mode:\n";
    std::cout << "  1) Normal\n";
    std::cout << "  2) Replay\n";
    std::cout << "Option [1/2]: ";

    int opcion = 0;
    while (opcion != 1 && opcion != 2)
    {
        std::cin >> opcion;
        if (opcion != 1 && opcion != 2)
        {
            std::cout << "Please, select 1 (Normal) or 2 (Replay): ";
        }
    }

    //Instruccions necessàries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    //Mostrem la finestra grafica
    pantalla.show();

    Joc joc;

    if (opcion == 1)
    {
        std::cout << "You've selected NORMAL MODE\n";
        joc.inicialitza(MODE_JOC_NORMAL, "./data/Games/tauler_inicial.txt", ".data/Games/moviments.txt");
    }
    else
    {
        std::cout << "You've selected REPLAY MODE\n";
        joc.inicialitza(MODE_JOC_REPLAY, "./data/Games/tauler_inicial.txt", "./data/Games/moviments.txt");
    }

    do
    {
        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        bool mouseStatus = Mouse_getBtnLeft();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();
        bool final = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        // Actualitza la pantalla
        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE));
    // Sortim del bucle si pressionem ESC

    //Instrucció necessària per alliberar els recursos de la llibreria 
    SDL_Quit();
    return 0;
}

