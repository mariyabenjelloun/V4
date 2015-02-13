#ifndef FIRE_H_INCLUDED
#define FIRE_H_INCLUDED
//classe repr�sentant le feu

class Fire
{
public:
    Fire(int x, int y) ; //Constructeur surcharg�

    bool disappear() ; //renvoie vrai s'il doit disparaitre et faux s'il doit rester
    int get_x() ; //renvoie la position x
    int get_y() ; //renvoie la position y

private:
    int _startTicks ; //nombre de millisecondes depuis le d�but du jeu � la cr�ation du feu
    int _x ; //position
    int _y ; //position
};


#endif // FIRE_H_INCLUDED
