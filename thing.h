#ifndef THING_H
#define THING_H

#include <QObject>
#include <QPoint>
#include <QLinkedList>
#include <QList>
#include <QPainter>

enum Type{
    tank=0,bullet,stone,metal,water,shrub,base,prop
};

enum TankType{player,enemy};

class Thing
{
protected:
    QPoint position;
    enum Type type;
    QPixmap image;
    int size;
    bool isDel;
public:
    static QLinkedList<Thing*> thingList;
    int changeTime;//物体改变时用的计时器
public:
    explicit Thing(QPoint,int,Type,QString);
    virtual ~Thing();
    QList<Thing*> findColl();
    void paint();
    void setImage(QString);
    QPoint getPosition();
    Type getType();
    int getSize();
    virtual void paint(QPainter*);
    bool getIsDel();
    void setType(Type t);

signals:

public slots:
};

#endif // THING_H
