#ifndef TANK_H
#define TANK_H

#include "bullet.h"
#include "prop.h"
#include "thing.h"


class Tank:public Thing
{
public:
    static int destroyEne;
public:
    int unbeatbleTime;//重生后的无敌时间
    int freezeTime;
    int speed;
    QPoint direct;
    TankType tankType;
    bool isView;
    int loadTime;
    int health;
    QPoint initPoint;

public:
    Tank(int,QPoint,TankType,QString,int,int);
    ~Tank();
    void paint(QPainter *painter);
    void Move();
    void Shoot();
    void SetIsView(bool);
    bool GetIsView();
    void Hide();
    TankType getTankType();
    void Loading();
    int getLoadTime();
    void beShot();
    QPoint getInitPoint();
    void setUnbeatableTime(int);
    void setFreezeTime(int);
};

#endif // TANK_H
