#include "Bomby.h"

#include "Functions.h"

#include "SDL/SDL_timer.h"

//Constructeur surchargé
Bomby::Bomby(SDL_Surface* screen, int x, int y)
{
    _screen = screen ;
    _x = x ;
    _y = y ;
    _nbBomb = 1 ;
    _alive = true ;
    _imagePlayerD = 0 ;
    _imagePlayerU = 0 ;
    _imagePlayerL = 0 ;
    _imagePlayerR = 0 ;
    _direction = DIRECTION_DOWN ;
    _lastMove = SDL_GetTicks() ;
    _deltaTMin = 200 ;
    _power = 1 ;
    _ill = false ;
}


int Bomby::get_x()
{
    return _x ;
}

int Bomby::get_y()
{
    return _y ;
}

void Bomby::set_x(int x)
{
    _x = x ;
}

void Bomby::set_y(int y)
{
    _y = y ;
}

//Affiche
void Bomby::render()
{
    SDL_Surface* imagePlayer = 0 ;
    switch (_direction)
    {
    case DIRECTION_UP:
        imagePlayer = _imagePlayerU ;
        break ;
    case DIRECTION_DOWN:
        imagePlayer = _imagePlayerD ;
        break ;
    case DIRECTION_LEFT:
        imagePlayer = _imagePlayerL ;
        break ;
    case DIRECTION_RIGHT:
        imagePlayer = _imagePlayerR ;
        break ;
    }


    int BOMBER_WIDTH = 54 ;
    int dec_pixel = 0 ;

    SDL_Rect offset;
    offset.x = _x*BOMBER_WIDTH;
    offset.y = _y*BOMBER_WIDTH - dec_pixel;

    SDL_Rect* clip = new SDL_Rect;
    clip->x = 0 ;
    clip->y = 0 ;
    clip->w = 54 ;
    clip->h = 54 ;

    SDL_BlitSurface(imagePlayer, clip, _screen, &offset );
    delete clip ;
}

bool Bomby::ableToPutBomb()
{
    return (_nbBomb > 0) ;
}

void Bomby::setNbBomb(int nbBomb)
{
    _nbBomb = nbBomb ;
}

int Bomby::getNbBomb()
{
    return _nbBomb ;
}


bool Bomby::getAlive()
{
    return _alive ;
}

//tue
void Bomby::kill()
{
    _alive = false ;
}


void Bomby::setImageD(SDL_Surface* imagePlayerD)
{
    _imagePlayerD = imagePlayerD ;
}
void Bomby::setImageU(SDL_Surface* imagePlayerU)
{
    _imagePlayerU = imagePlayerU ;
}
void Bomby::setImageR(SDL_Surface* imagePlayerR)
{
    _imagePlayerR = imagePlayerR ;
}
void Bomby::setImageL(SDL_Surface* imagePlayerL)
{
    _imagePlayerL = imagePlayerL ;
}


void Bomby::setDirection(Direction direction)
{
    _direction = direction ;
}


bool Bomby::movePlayer()
{
    int ticks = SDL_GetTicks() ;
    bool okMove = ((ticks - _lastMove) > _deltaTMin) ;
    if (okMove)
    {
        _lastMove = SDL_GetTicks() ;
        return okMove ;
    }
    return okMove ;
}


void Bomby::increaseSpeed()
{
    _deltaTMin *= 0.80 ;
}

void Bomby::increasePower()
{
    _power ++ ;
}

void Bomby::setIll(bool isIll)
{
    _ill = isIll ;
}

int Bomby::getPower()
{
    return _power ;
}

bool Bomby::getIll()
{
    return _ill ;
}
