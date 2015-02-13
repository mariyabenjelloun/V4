#ifndef BOMBY_H_INCLUDED
#define BOMBY_H_INCLUDED

#include "SDL/SDL_video.h"

#include "Direction.h"

//Forward d�claration de la classe Map
class Map ;

//La classe qui repr�sente un joueur
class Bomby
{
public:
    Bomby(SDL_Surface* screen, int x, int y) ; //constructeur surchag�

    int get_x() ;
    int get_y() ;
    void set_x(int x) ;
    void set_y(int y) ;
    bool getAlive() ;
    void kill() ; //fonction qui tue le joueur

    bool ableToPutBomb() ; //renvoie s'il lui reste des bombes � poser et faux s'il en a plus

    void render() ; //affichage sur l'�cran du joueur
    void setNbBomb(int nbBomb) ;
    int getNbBomb() ;

    void setImageD(SDL_Surface* imagePlayerD) ;
    void setImageU(SDL_Surface* imagePlayerU) ;
    void setImageR(SDL_Surface* imagePlayerR) ;
    void setImageL(SDL_Surface* imagePlayerL) ;
    void setDirection(Direction direction) ;

    bool movePlayer() ; //renvoie vrai s'il le joueur peut se d�placer et faux sinon
    void increaseSpeed() ; //augmente la vitesse
    void increasePower() ; //Augmente la puissance des bombes
    void setIll(bool isIll) ; //change son �tat malade en is ill
    int getPower() ;
    bool getIll() ;

private:
    bool _alive ; //vrai si en vie et faux sinon
    bool _ill ; //Vrai si malade faux sinon
    int _nbBomb ;
    int _deltaTMin ; //temps minimum entre deux d�placements autoris�s
    int _lastMove ; //temps qui s'est �coul� entre le d�but du jeu et le d�placement du joueur
    int _power ; //puissance des bombes
    int _x ;
    int _y ;

    SDL_Surface* _screen ; //pointeur vers l'�cran
    SDL_Surface* _imagePlayerD ;
    SDL_Surface* _imagePlayerU ;
    SDL_Surface* _imagePlayerR ;
    SDL_Surface* _imagePlayerL ;
    Direction _direction ; //directeur vers laquelle il va
};




#endif // BOMBY_H_INCLUDED
