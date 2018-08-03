#ifndef PCTANK_H
#define PCTANK_H

#include "tank.h"
#include <QtGlobal>
#include <QTime>

class PcTank:public Tank
{
private:
    int shootTime;
    int turnTime;
public:
    PcTank(QPoint,int);
    void autoAct();
};

#endif // PCTANK_H
