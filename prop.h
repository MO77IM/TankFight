#ifndef PROP_H
#define PROP_H

#include "thing.h"
#include "tank.h"

enum PropType{timeStop=0,unBeatable,barrier};

class Tank;

class Prop:public Thing
{
private:
    PropType propType;
    int existTime;
public:
    Prop(PropType propType,QPoint pos);
    void beUsed(Tank* t);
    PropType getPropType();
    void exist();
};

#endif // PROP_H
