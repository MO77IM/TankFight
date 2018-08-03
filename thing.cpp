#include "thing.h"

QLinkedList<Thing*> Thing::thingList;

Thing::Thing(QPoint position,int size,Type type,QString imgName)
{
    this->position=position;
    this->size=size;
    this->type=type;
    isDel=false;
    image.load(imgName);
    thingList.append(this);
    changeTime=0;
}

Thing::~Thing(){
    thingList.removeOne(this);
}

QList<Thing*> Thing::findColl(){//获取与物体碰撞的其他物体的列表
    QList<Thing*> collList;
    QMutableLinkedListIterator<Thing*> p(thingList);//遍历物体列表
    while(p.hasNext()){
        Thing* other=p.next();
        if(other==this)
            continue;
        //判断物体之间是否发生碰撞
        if(abs(other->getPosition().x()-this->position.x()+other->getSize())<=2&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)||
                abs(other->getPosition().x()-this->position.x()-size)<=2&&(position.y()-other->getPosition().y()<other->getSize()&&other->getPosition().y()-position.y()<size)||
                abs(other->getPosition().y()-this->position.y()+other->getSize())<=2&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)||
                abs(other->getPosition().y()-this->position.y()-size)<=2&&(position.x()-other->getPosition().x()<other->getSize()&&other->getPosition().x()-position.x()<size)||
                position.x()>other->getPosition().x()&&position.x()<other->getPosition().x()+other->getSize()&&position.y()>other->getPosition().y()&&position.y()<other->getPosition().y()+other->getSize())
            collList.append(other);
    }
    return collList;
}

void Thing::setImage(QString imgName){
    image.load(imgName);
}

QPoint Thing::getPosition(){
    return position;
}

int Thing::getSize(){
    return size;
}

Type Thing::getType(){
    return type;
}

void Thing::paint(QPainter* painter){
    QRect p(Thing::position,QPoint(Thing::position.x()+Thing::size,Thing::position.y()+Thing::size));
    painter->drawPixmap(p,image);
}

bool Thing::getIsDel(){return isDel;}

void Thing::setType(Type t){
    type=t;
}
