#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <synchapi.h>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <widget.h>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    Widget* pWidget=this;
    pWidget->setStyleSheet("background-color:black");

    setFixedSize(1200,900);

    isMoving=false;
    shrub1=new Shrub(QPoint(600,400),40);

    player1=new Tank(2,QPoint(500,500),player,QString(":/image/tank.png"),80);

    thing=new Tank(1,QPoint(0,0),enemy,QString(":/image/enemy.png"),80);
    thing2=new Tank(1,QPoint(500,100),enemy,QString(":/image/enemy.png"),80);

    stone=new Stone(QPoint(700,700),40);

    metal=new Metal(QPoint(300,300),40);

    shrub2=new Shrub(QPoint(100,600),40);

    wt=new Thing(QPoint(200,400),40,water,QString(":/image/water.bmp"));

    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(10);

    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){
    Thing* pThing;
    QList<Thing*> shrubList;
    QMutableLinkedListIterator<Thing*> p(Thing::thingList);
    while(p.hasNext()){
        pThing=p.next();
        if(pThing->getType()==shrub){
            shrubList.append(pThing);
            continue;
        }
        QPainter* painter=new QPainter(this);
        pThing->paint(painter);
        delete painter;
    }
    for(int i=0;i<shrubList.count();i++){
        pThing=shrubList[i];
        QPainter* painter=new QPainter(this);
        pThing->paint(painter);
        delete painter;
    }
}

void Widget::keyPressEvent(QKeyEvent *event){
    QMatrix matrix;
    switch(event->key()){
        case Qt::Key_Up:
            player1->direct.setY(-1);
            player1->direct.setX(0);
            isMoving=true;
            break;
        case Qt::Key_Down:
            player1->direct.setY(1);
            player1->direct.setX(0);
            isMoving=true;
            break;
        case Qt::Key_Right:
            player1->direct.setX(1);
            player1->direct.setY(0);
            isMoving=true;
            break;
        case Qt::Key_Left:
            player1->direct.setX(-1);
            player1->direct.setY(0);
            isMoving=true;
            break;
        case Qt::Key_Space:
            player1->Shoot();
        break;
        default:
            break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Up:
            isMoving=false;
        break;
        case Qt::Key_Down:
            isMoving=false;
        break;
        case Qt::Key_Right:
            isMoving=false;
        break;
        case Qt::Key_Left:
            isMoving=false;
        break;
        default:break;
    }
}

void Widget::timeout(){
    int eneCount=0,playCount=0;
    QMutableLinkedListIterator<Thing*> p(Thing::thingList);
    Thing* thing;
    while(p.hasNext()){
        thing=p.next();
        if(thing->getType()==bullet){
            Bullet* blt=dynamic_cast<Bullet*>(thing);
            if(blt==NULL){
                exit(0);
            }
            blt->Move();
        }
        else if(thing->getType()==tank){
            Tank* tk=dynamic_cast<Tank*>(thing);
            if(tk==NULL)
                exit(0);
            if(tk->getTankType()==enemy)
                eneCount++;
            if(tk->getTankType()==player)
                playCount++;
            tk->Loading();
        }
    }
    if(eneCount==0){
        this->hide();
        emit gameend();
    }
    if(isMoving){
        player1->Move();
    }
    repaint();
}

void Widget::receivestart(){
    this->show();
}
