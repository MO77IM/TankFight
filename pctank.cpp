#include "pctank.h"

PcTank::PcTank(QPoint pos,int size):Tank(2,pos,enemy,":/image/enemy.png",size,1)
{
    shootTime=100;
    turnTime=200;
    unbeatbleTime=200;
    freezeTime=0;
}

void PcTank::autoAct(){
    if(freezeTime){
        freezeTime--;
        return;
    }
    QPoint prePos=position;
    this->Move();
    if(position==prePos){
        Type collType;
        QList<Thing*> collList=findColl();
        if(!collList.empty())
            collType=collList[0]->getType();
        else
            collType=metal;
        if(collType==stone||collType==water){
            int isShoot=qrand()%2;
            if(isShoot==0&&shootTime<=20){
                Shoot();
                shootTime=100;
            }
        }
        else if(collType==tank){
            Tank* tk=dynamic_cast<Tank*>(collList[0]);
            if(tk==NULL)
                exit(0);
            if(tk->getTankType()==player){
                Shoot();
                shootTime=100;
            }
            else{
                int d=qrand()%4+1;
                switch (d) {
                case 1:
                    direct.setX(1);
                    direct.setY(0);
                    break;
                case 2:
                    direct.setX(-1);
                    direct.setY(0);
                    break;
                case 3:
                    direct.setX(0);
                    direct.setY(1);
                    break;
                case 4:
                    direct.setX(0);
                    direct.setY(-1);
                    break;
                default:
                    break;
                }
                turnTime=200;
            }
        }
        else{
            int d=qrand()%4+1;
            switch (d) {
            case 1:
                direct.setX(1);
                direct.setY(0);
                break;
            case 2:
                direct.setX(-1);
                direct.setY(0);
                break;
            case 3:
                direct.setX(0);
                direct.setY(1);
                break;
            case 4:
                direct.setX(0);
                direct.setY(-1);
                break;
            default:
                break;
            }
            turnTime=200;
        }
    }
    if(turnTime<=0){
        int d=qrand()%4+1;
        switch (d) {
        case 1:
            direct.setX(1);
            direct.setY(0);
            break;
        case 2:
            direct.setX(-1);
            direct.setY(0);
            break;
        case 3:
            direct.setX(0);
            direct.setY(1);
            break;
        case 4:
            direct.setX(0);
            direct.setY(-1);
            break;
        default:
            break;
        }
        turnTime=200;
    }
    if(shootTime<=0){
        Shoot();
        shootTime=100;
    }
    shootTime--;
    turnTime--;
}


