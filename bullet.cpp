#include "bullet.h"
#include <qdebug.h>
#include <QtGlobal>

Bullet::Bullet(int speed,QPoint position,QPoint direct,QString imgName,TankType camp):Thing(position,7,bullet,imgName)
{
    this->speed=speed;
    this->position=position;
    this->direct=direct;
    bulletType=camp;
}

void Bullet::Move(){
    QPoint trans;
    trans.setX(direct.x()*speed);
    trans.setY(direct.y()*speed);
    position+=trans;
    if(position.x()<0||position.x()>1200||position.y()<0||position.y()>900)
        delete this;
    QList<Thing*> collList=findColl();
    bool isDel;
    Thing* other;
    for(int i=0;i<collList.count();i++){
        other = collList[i];
        /*if(other->getPosition().x()-position.x()+other->getSize()<=0&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)&&direct.x()==-1||
                other->getPosition().x()-size-position.x()>=0&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)&&direct.x()==1||
                other->getPosition().y()-position.y()+other->getSize()<=0&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)&&direct.y()==-1||
                other->getPosition().y()-position.y()-size>=0&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)&&direct.y()==1||
           (position.x()>other->getPosition().x()-2&&position.x()<other->getPosition().x()+other->getSize()+2&&position.y()>other->getPosition().y()-2&&position.y()<other->getPosition().y()+other->getSize()+2))*/

        if(other->getPosition().x()-position.x()+other->getSize()<=0&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)&&direct.x()==-1||
                other->getPosition().x()-size-position.x()>=0&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)&&direct.x()==1||
                other->getPosition().y()-position.y()+other->getSize()<=0&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)&&direct.y()==-1||
                other->getPosition().y()-position.y()-size>=0&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)&&direct.y()==1||
                 (position.x()>other->getPosition().x()-2&&position.x()<other->getPosition().x()+other->getSize()+2&&position.y()>other->getPosition().y()-2&&position.y()<other->getPosition().y()+other->getSize()+2))
        {
            if(other->getType()==tank){
                isDel=true;
                //other->setDel();
                Tank* tk=dynamic_cast<Tank*>(other);
                if(tk==NULL)
                    exit(0);
                if(bulletType!=tk->getTankType())
                    tk->beShot();
            }
            else if(other->getType()==stone){
                isDel=true;
                Stone* s=dynamic_cast<Stone*>(other);
                if(s==NULL)
                    exit(0);
                s->beShot();
            }
            else if(other->getType()==shrub||other->getType()==water){
                isDel=false;
                continue;
            }
            else if(other->getType()==metal)
                isDel=true;
            else if(other->getType()==bullet)
                isDel=true;
            else if(other->getType()==base){
                isDel=true;
                delete other;
            }
        }
    }
    if(isDel)
        delete this;
    collList.clear();
}

void Bullet::paint(QPainter *painter){
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
