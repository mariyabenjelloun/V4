#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include <vector>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

using namespace std ;

//Forward declaration
class Case;
class Bomby;
class Bomb;
class Fire;

//Créons une classe dont le but sera de contenir les différentes cases. cette classe fait les tours de jeux, elle organise le jeu
class Map
{
public:
    Map(SDL_Surface* screen, bool isSound); //constructeur surchargé

    void game_on(); //fonction qu'on appelle quand on lance le jeu

private:
//Fonction qui font marcher un joueur
    void walkLeft(Bomby* player) ;
    void walkRight(Bomby* player) ;
    void walkUp(Bomby* player) ;
    void walkDown(Bomby* player) ;
//Fonction qui arrete le jeu si un des joueurs est mort
    void testDead(bool* goOn) ;
//Affiche tout en appelant toutes les autres fonctions render
    void render() ;
//Gestion de l'explosion des bombes
    void bombExplod() ;
//Gestion de l'explosion qui se trouve aux coordonnées (i,j)
    void explodeCase(int i, int j) ;
//Gestion de la disparition des feux
    void disappearFire() ;
//Gestion des déplacements et de la pause de bombe des deux joueurs
    void handleEventPlayer1(SDL_Event event) ;
    void handleEventPlayer2(SDL_Event event) ;

//Pointeur vers les deux joueurs
    Bomby* _player1;
    Bomby* _player2;
//Liste des pointeurs vers toutes les cases
    vector<Case*> _vectCase;
//Liste des pointeurs vers toutes les bombes
    vector<Bomb*> _vectBomb;
//Liste des pointeurs vers tous les feus
    vector<Fire*> _vectFire;
//Pointeur vers l'écran
    SDL_Surface* _screen ;
//Pointeur vers le son de l'explosion
    Mix_Chunk* _sound;
//Pointeur vers la musique
    Mix_Music* _music;
//Pointeur vers chacune des images chargées
    SDL_Surface* _imageEmpty ;
    SDL_Surface* _imageBonusBomb ;
    SDL_Surface* _imageBonusSpeed ;
    SDL_Surface* _imageBonusPower ;
    SDL_Surface* _imageBonusIll ;
};







#endif // MAP_H_INCLUDED
