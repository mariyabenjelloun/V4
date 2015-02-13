#include "Bonus.h"
//constructeur surchargé
Bonus::Bonus(BonusType type, int x, int y)
{
    _type = type ;
    _x = x ;
    _y = y ;
}
//fonction qui renvoie le type de bonus
BonusType Bonus::getType()
{
    return _type ;
}
