#include "Case.h"

#include "Bonus.h"


Case::Case(SDL_Surface* appearance, int x, int y, SDL_Surface* screen)
{
    _bonus = 0 ;
    _appearance = appearance ;
    _x = x ;
    _y = y ;
    _screen = screen ;
    _type = EMPTY ;
}

void Case::render()
{
    int BOMBER_WIDTH = 54 ;
    int dec_pixel = 0 ;


    //Initialise le rectangle de l'image en source
    SDL_Rect offset;

    //Fixe la taille du rectangle à afficher
    offset.x = _x*BOMBER_WIDTH;
    offset.y = _y*BOMBER_WIDTH - dec_pixel;

    //Affiche le rectangle (clip) mis en argument de la source sur le screen, fixés comme argument de la classe
    SDL_BlitSurface(_appearance,0 , _screen, &offset );
}


void Case::setType(CaseType type)
{
    _type = type ;
}

void Case::setAppearance(SDL_Surface* appearance)
{
    _appearance = appearance ;
}

CaseType Case::getType()
{
    return _type ;
}

void Case::setBonus(Bonus* bonus)
{
    _bonus = bonus ;
}


Bonus* Case::getBonus()
{
    return _bonus ;
}
