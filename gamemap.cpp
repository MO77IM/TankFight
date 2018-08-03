#include "gamemap.h"
#include "ui_gamemap.h"
#include <QPainter>
#include <synchapi.h>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>
#include <widget.h>
#include <QFile>
#include <QLabel>

GameMap::GameMap(int level,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMap)
{
    ui->setupUi(this);

    GameMap* pWidget=this;
    pWidget->setStyleSheet("background-color:black");
    Thing::thingList.clear();


    Tank::destroyEne=0;
    rebornTime=0;
    propTime=3000;

    setFixedSize(1200,900);

    QString fileName(":/map/map");
    fileName+=QString::number(level)+QString(".txt");
    eneNum=4;
    isMoving=false;
    //处理地图文件
    QFile mapFile(fileName);
    if(!mapFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            exit(0);
        }
    QTextStream in(&mapFile);
    QString line;
    QStringList stringList;
    while(!in.atEnd()){
        line=in.readLine();
        stringList=line.split(",");
        if(stringList.at(0)=="stone"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            Stone* st=new Stone(pos,size);
            stones.append(st);
        }
        else if(stringList.at(0)=="shrub"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            Thing* st=new Thing(pos,size,shrub,":/image/shrub.png");
            things.append(st);
        }
        else if(stringList.at(0)=="water"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            Thing* wt=new Thing(pos,size,water,":/image/water.bmp");
            things.append(wt);
        }
        else if(stringList.at(0)=="metal"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            Thing* mt=new Thing(pos,size,metal,":/image/metal.bmp");
            things.append(mt);
        }
        else if(stringList.at(0)=="enemy"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            PcTank* pt=new PcTank(pos,size);
            enes.append(pt);
        }
        else if(stringList.at(0)=="player"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            player1=new Tank(2,pos,player,":/image/tank.png",size,3);
        }
        else if(stringList.at(0)=="base"){
            QPoint pos;
            pos.setX(stringList.at(1).toInt());
            pos.setY(stringList.at(2).toInt());
            QString s=stringList.at(3);
            int size=s.toInt();
            base1=new Thing(pos,size,base,":/image/base.gif");
        }
    }
    mapFile.close();

    new Prop(barrier,QPoint(550,820));

    for(int i=0;i<enes.count();i++){
        eneInitPos.append(enes[i]->getInitPoint());
    }
    //实现定时更新画面功能
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
    timer->start(10);
}

GameMap::~GameMap()
{
    delete ui;
}

void GameMap::paintEvent(QPaintEvent *){
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

void GameMap::keyPressEvent(QKeyEvent *event){
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

void GameMap::keyReleaseEvent(QKeyEvent *event){
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

void GameMap::timeout(){
    //每个物体执行动作，并且计算物体数量
    int eneCount=0,playCount=0,baseCount=0;
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
            if(tk->unbeatbleTime>0)
                tk->unbeatbleTime--;
            if(tk->getTankType()==enemy){
                PcTank* ptk=dynamic_cast<PcTank*>(tk);
                if(ptk==NULL)
                    exit(0);
                if(ptk->getIsDel()){
                    delete ptk;
                    continue;
                }
                ptk->autoAct();
                eneCount++;
            }
            if(tk->getTankType()==player){
                if(tk->getIsDel()){
                    delete tk;
                    continue;
                }
                playCount++;
            }
            tk->Loading();
        }
        else if(thing->getType()==base){
            baseCount++;
        }
        else if(thing->getType()==prop){
            Prop* prop=dynamic_cast<Prop*>(thing);
            if(prop==NULL)
                exit(0);
            prop->exist();
        }
        else if(thing->getType()==metal){
            if(thing->changeTime>0){
                thing->changeTime--;
                if(thing->changeTime==0){
                    thing->setType(stone);
                    Stone* s=dynamic_cast<Stone*>(thing);
                    if(s->getHealth()==2)
                        s->setImage(":/image/stone.bmp");
                    else if(s->getHealth()==1)
                        s->setImage(":/image/broken_stone.png");
                }
            }
        }
    }

    //随机刷道具
    if(--propTime==0){
        int isGenerate=qrand()%2;
        if(isGenerate){
            bool isFind=false;
            Thing* thing;
            QPoint pos(qrand()%1180,qrand()%880);
            while(true){
                bool isUsed=false;
                QMutableLinkedListIterator<Thing*> p(Thing::thingList);
                while(p.hasNext()){
                    thing=p.next();
                    QRect other(thing->getPosition().x(),thing->getPosition().y(),thing->getPosition().x()+thing->getSize(),thing->getPosition().y()+thing->getSize());
                    QRect propRect(pos.x(),pos.y(),pos.x()+20,pos.y()+20);
                    if(other.intersects(propRect))
                        isUsed=true;
                }
                if(!isUsed){
                    isFind=true;
                    break;
                }
                pos.setX(qrand()%1180);
                pos.setY(qrand()%880);
            }
            if(isFind){
                int type=qrand()%3;
                if(type==0)
                    new Prop(timeStop,pos);
                else if(type==1)
                    new Prop(unBeatable,pos);
            }
        }
        propTime=3000;
    }
    //敌人重生
    if(eneCount<4&&PcTank::destroyEne+eneCount<10&&rebornTime==0){
        for(int i=0;i<4;i++){
            QPoint iPoint=eneInitPos[i];
            QRect iRect(iPoint,iPoint+QPoint(player1->getSize(),player1->getSize()));
            bool unused=true;
            for(int j=0;j<enes.count();j++){
                QRect nRect(enes[j]->getPosition(),enes[i]->getPosition()+QPoint(enes[i]->getSize(),enes[i]->getSize()));
                if(nRect.intersects(iRect))
                    unused=false;
                QRect pRect(player1->getPosition(),player1->getPosition()+QPoint(player1->getSize(),player1->getSize()));
                if(pRect.intersects(iRect))
                    unused=false;
                if(unused){
                    enes.append(new PcTank(eneInitPos[i],player1->getSize()));
                    break;
                }
            }
            if(unused)
                break;
        }
        rebornTime=400;
    }
    if(rebornTime>0)
        rebornTime--;

    //判断输赢条件
    if(playCount==0||baseCount==0||Tank::destroyEne==10){
        delete timer;
        stones.clear();
        things.clear();
        enes.clear();
        eneInitPos.clear();
        QMutableLinkedListIterator<Thing*> p(Thing::thingList);
        Thing* thing;
        while(p.hasNext()){
            thing=p.next();
            if(thing->getType()==bullet){
                Bullet* blt=dynamic_cast<Bullet*>(thing);
                if(blt==NULL)
                    exit(0);
                delete blt;
            }
            else if(thing->getType()==tank){
                Tank* tk=dynamic_cast<Tank*>(thing);
                if(tk==NULL)
                    exit(0);
                if(tk->getTankType()==enemy){
                    PcTank* ptk=dynamic_cast<PcTank*>(tk);
                    if(ptk==NULL)
                        exit(0);
                    delete ptk;
                }
                else
                    delete tk;
            }
            else if(thing->getType()==stone){
                Stone* st=dynamic_cast<Stone*>(thing);
                if(st==NULL)
                    exit(0);
                delete st;
            }
            else{
                delete thing;
            }
        }
        if(playCount==0||baseCount==0)
            emit lose();
        if(Tank::destroyEne==10)
            emit win();
        this->close();
    }

    //玩家移动
    if(isMoving){
        player1->Move();
    }

    repaint();
}
