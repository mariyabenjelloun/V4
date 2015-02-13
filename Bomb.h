#ifndef BOMB_H_INCLUDED
#define BOMB_H_INCLUDED
//Forward declaration
class Bomby ;


//Classe de la bombe
class Bomb
{
public:
    Bomb(Bomby* bomby,int x, int y) ; //Constructeur

    bool explode() ; //Renvoie vrai si la bombe doit exploser et faux sinon
    int get_x() ; //renvoie la position en x
    int get_y() ; // renvoie la position en y
    Bomby* getBomby() ; //renvoie un pointeur vers le joueur qui a pos� la bombe

private:
    int _startTicks ; //le temps entre le d�but du jeu et le moment o� la bombe a �t� pos�
    int _x ; //position en x
    int _y ;//position en y
    Bomby* _bomby ; //stock un pointeur vers le joueur qui a pos� la bombe
};


#endif // BOMB_H_INCLUDED
