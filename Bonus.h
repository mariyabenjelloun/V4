#ifndef BONUS_H_INCLUDED
#define BONUS_H_INCLUDED

#include "BonusType.h"
// Class repr�sentant un Bonus
class Bonus
{
public:
    Bonus(BonusType type, int x, int y) ; //Constructeur surcharg�

    BonusType getType() ; //renvoie le type du bonus

private:
    BonusType _type ; //type de bonus
    int _x ; //position
    int _y ; //position
};



#endif // BONUS_H_INCLUDED
