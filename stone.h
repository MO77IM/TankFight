#ifndef STONE_H
#define STONE_H
#include "thing.h"

class Stone:public Thing
{
private:
    int health;
public:
    Stone(QPoint,int);
    ~Stone(){}
    void beShot();
    int getHealth();
};

#endif // STONE_H
