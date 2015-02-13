#include "Bomb.h"

#include "SDL/SDL_timer.h"

#include "Bomby.h"


//Constructeur surchargé
Bomb::Bomb(Bomby* bomby,int x, int y)
{
    _startTicks = SDL_GetTicks() ;
    _x = x ;
    _y = y ;
    _bomby = bomby ;
}

//Renvoie vrai si le temps ecoulé est superieur à 3 sec et que donc la bombe doit exploser
bool Bomb::explode()
{
    int deltaT = SDL_GetTicks() - _startTicks ;
    bool ok = (deltaT > 3000) ;
    return ok ;
}
//Getters
int Bomb::get_x()
{
    return _x ;
}

int Bomb::get_y()
{
    return _y ;
}


Bomby* Bomb::getBomby()
{
    return _bomby ;
}
