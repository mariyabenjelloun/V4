#include "Fire.h"

#include "SDL/SDL_timer.h"
//Constructeur
Fire::Fire(int x, int y)
{
    _x = x ;
    _y = y ;
    _startTicks = SDL_GetTicks() ;
}
//Fonction qui renvoie si le temps passé est plus d'une seconde et si c'est le cas, le feu doit disparaitre
bool Fire::disappear()
{
    int deltaT = SDL_GetTicks() - _startTicks ;
    return (deltaT > 1000) ;
}

// Getters
int Fire::get_x()
{
    return _x ;
}


int Fire::get_y()
{
    return _y ;
}
