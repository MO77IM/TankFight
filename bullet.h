#ifndef BULLET_H
#define BULLET_H
#include <QPainter>
#include <QPoint>
#include <thing.h>
#include <tank.h>
#include <stone.h>
//#include <playertank.h>
//#include <pctank.h>

class Bullet:public Thing
{
private:
    int speed;
    QPoint direct;
    TankType bulletType;
public:
    Bullet(int,QPoint,QPoint,QString,TankType);
    void Move();
    void paint(QPainter*);
};

#endif // BULLET_H
