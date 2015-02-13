#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL/SDL.h>
#include "Map.h"

//Classe qui gère le menu
class Menu
{
public:
    Menu(); //Constructeur

private:
    void menuRules() ; //Fonction qui affiche les règles du jeu
    void menuOptions() ; //Fonction qui affiche les options
    //Pointeur vers l'écran
    SDL_Surface* _screen ;
    //Position où l'on met l'écran
    SDL_Rect _positionMenu;
    //Booléen qui indique la présence de son
    bool _isSound ;
};






#endif // MENU_H_INCLUDED
