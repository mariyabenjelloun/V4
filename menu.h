#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL/SDL.h>
#include "Map.h"

//Classe qui g�re le menu
class Menu
{
public:
    Menu(); //Constructeur

private:
    void menuRules() ; //Fonction qui affiche les r�gles du jeu
    void menuOptions() ; //Fonction qui affiche les options
    //Pointeur vers l'�cran
    SDL_Surface* _screen ;
    //Position o� l'on met l'�cran
    SDL_Rect _positionMenu;
    //Bool�en qui indique la pr�sence de son
    bool _isSound ;
};






#endif // MENU_H_INCLUDED
