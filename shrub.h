#ifndef SHRUB_H
#define SHRUB_H
#include "thing.h"
#include "tank.h"

class Shrub:public Thing
{
public:
    Shrub(QPoint,int);
    ~Shrub(){}
};

#endif // SHRUB_H
