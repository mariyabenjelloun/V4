#ifndef CASE_H_INCLUDED
#define CASE_H_INCLUDED

#include <SDL/SDL_video.h>
#include "CaseType.h"
//Forward déclaration de la classe Bonus
class Bonus ;

//Classe représentant une case
class Case
{
public:
    Case(SDL_Surface* appearance,int x, int y, SDL_Surface* screen) ; //Constructeur surchargé

    void render() ; //Fonction qui affiche la surface graphique de la case
    void setType(CaseType type) ; //change le type
    void setAppearance(SDL_Surface* appearance) ; //change l'apparence de la case
    CaseType getType() ; //renvoie le type de la case

    void setBonus(Bonus* bonus) ; //met un bonus
    Bonus* getBonus() ; //renvoie le bonus

private:
    CaseType _type ; //type de la case
    Bonus* _bonus; //pointeur vers le bonus
    SDL_Surface* _appearance ; //pointeur vers l'image de la case
    SDL_Surface* _screen ; //pointeur vers l'écran du jeu, pour afficher l'apparence sur l'écran
    int _x ; //position de la case
    int _y ; //position de la case

};
#endif // CASE_H_INCLUDED
