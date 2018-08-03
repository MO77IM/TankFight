#include "prop.h"

Prop::Prop(PropType propType,QPoint pos):Thing(pos,20,prop,"")
{
    this->propType=propType;
    existTime=2000;
    if(propType==timeStop)
        image.load(":/image/time_stop.bmp");
    else if(propType==unBeatable)
        image.load(":/image/unbeatable.bmp");
    else if(propType==barrier)
        image.load(":/image/barrier.bmp");
}
void Prop::beUsed(Tank* t){
    if(propType==timeStop){
        QMutableLinkedListIterator<Thing*> p(Thing::thingList);
        Thing* thing;
        while(p.hasNext()){
            thing=p.next();
            if(thing->getType()==tank){
                Tank* tmp=dynamic_cast<Tank*>(thing);
                if(tmp==NULL)
                    exit(0);
                if(tmp->getTankType()==enemy){
                    tmp->setFreezeTime(500);
                }
            }
        }
    }
    else if(propType==unBeatable){
        t->setUnbeatableTime(1000);
    }
    else if(propType==barrier){
        QMutableLinkedListIterator<Thing*> p(Thing::thingList);
        Thing* thing;
        while(p.hasNext()){
            thing=p.next();
            if(thing->getType()==base)
                break;
        }
        QList<Thing*> collList=thing->findColl();
        for(int i=0;i<collList.count();i++){
            Thing* coll=collList[i];
            if(coll->getType()==stone){
                coll->setImage(":/image/metal.bmp");
                coll->setType(metal);
                coll->changeTime=1000;
            }
        }
    }
    delete this;
}

PropType Prop::getPropType(){
    return propType;
}

void Prop::exist(){
    if(--existTime==0)
        delete this;
}
