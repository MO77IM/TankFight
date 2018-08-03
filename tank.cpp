#include "tank.h"
#include <QDebug>

int Tank::destroyEne=0;

Tank::Tank(int speed,QPoint position,TankType camp,QString imgName,int size,int health):Thing(position,size,tank,imgName)
{
    this->speed=speed;
    direct.setX(0);
    direct.setY(-1);
    isView=true;
    tankType=camp;
    loadTime=0;
    this->health=health;
    initPoint=position;
    this->unbeatbleTime=0;
}

Tank::~Tank(){
}

void Tank::Move(){
    QList<Thing*> collList;
    Thing* other;
    collList=findColl();
    for(int i=0;i<collList.count();i++){
        other=collList[i];
        if(other->getType()==shrub){
                if(abs(other->getPosition().x()-position.x())<=10&&abs(other->getPosition().y()-position.y())<=10)
                    isView=false;
                else
                    isView=true;
                continue;
            }
        if(other->getType()==prop&&tankType==player){
            Prop* prop=dynamic_cast<Prop*>(other);
            if(prop==NULL)
                exit(0);
            prop->beUsed(this);
        }
        if(other->getPosition().x()-position.x()+other->getSize()==0&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)&&direct.x()==-1||
                other->getPosition().x()-(position.x()+size)==0&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)&&direct.x()==1||
                other->getPosition().y()-position.y()+other->getSize()==0&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)&&direct.y()==-1||
                other->getPosition().y()-position.y()-size==0&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)&&direct.y()==1)
           return;
    }
    if(position.x()<=0&&direct.x()==-1||
            position.x()+size>=1200&&direct.x()==1||
            position.y()<=0&&direct.y()==-1||
            position.y()+size>=900&&direct.y()==1)
        return;

    QPoint trans;
    trans.setX(direct.x()*speed);
    trans.setY(direct.y()*speed);
    Thing::position+=trans;
}

void Tank::paint(QPainter *painter){
    int rot;
    if(direct.x()==0&&direct.y()==-1)
        rot=180;
    else if(direct.x()==0&&direct.y()==1)
        rot=0;
    else if(direct.x()==1&&direct.y()==0)
        rot=-90;
    else
        rot=90;
    painter->translate(Thing::position.x()+Thing::size/2,Thing::position.y()+Thing::size/2);
    painter->rotate(rot);
    painter->translate(-Thing::position.x()-Thing::size/2,-Thing::position.y()-Thing::size/2);
    QRect p(Thing::position,QPoint(Thing::position.x()+Thing::size,Thing::position.y()+Thing::size));
    painter->drawPixmap(p,image);
}

void Tank::Shoot(){
    if(loadTime>0)
        return;
    QPoint bulletPos;
    if(direct.x()==1&&direct.y()==0){
        bulletPos.setX(position.x()+size+3);
        bulletPos.setY(position.y()+size/2-2);
    }
    else if(direct.x()==-1&&direct.y()==0){
        bulletPos.setX(position.x()-3);
        bulletPos.setY(position.y()+size/2-2);
    }
    else if(direct.x()==0&&direct.y()==1){
        bulletPos.setX(position.x()+size/2-3);
        bulletPos.setY(position.y()+size+3);
    }
    else{
        bulletPos.setX((position.x()+size/2-3));
        bulletPos.setY(position.y()-3);
    }
    new Bullet(4,bulletPos,direct,":/image/bullet.png",tankType);
    loadTime=25;
}

void Tank::SetIsView(bool _isView){
    isView=_isView;
}

bool Tank::GetIsView(){return isView;}

void Tank::Loading(){
    if(loadTime>0)
        loadTime--;
}

TankType Tank::getTankType(){return tankType;}

int Tank::getLoadTime(){return loadTime;}

void Tank::beShot(){
    if(unbeatbleTime)
        return;
    health--;
    if(health==0){
        if(this->getTankType()==enemy){
            destroyEne++;
        }
        isDel=true;
    }
    else{
        unbeatbleTime=200;
        position=initPoint;
    }
}

QPoint Tank::getInitPoint(){return initPoint;}

void Tank::setUnbeatableTime(int t){
    unbeatbleTime=t;
}

void Tank::setFreezeTime(int t){
    freezeTime=t;
}
