#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include "tank.h"

class EnemyTank:public Tank
{
public:
    EnemyTank(int speed,QPoint position,TankType camp,QString imgName);
    ~EnemyTank();
};

#endif // ENEMYTANK_H
