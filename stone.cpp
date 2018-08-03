#include "stone.h"

Stone::Stone(QPoint position,int size):Thing(position,size,stone,QString(":/image/stone.bmp"))
{
    health=2;
}

void Stone::beShot(){
    --health;
    if(health==1)
        setImage(":/image/broken_stone.png");
    if(health==0)
        delete this;
}
\
int Stone::getHealth(){return health;}
