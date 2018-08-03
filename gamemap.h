#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QWidget>
#include <QTimer>
#include "tank.h"
#include <QLabel>
#include "stone.h"
#include "pctank.h"
#include "prop.h"
#include <QtGlobal>

namespace Ui {
class GameMap;
}

class GameMap : public QWidget
{
    Q_OBJECT

public:
    explicit GameMap(int level=1,QWidget *parent = 0);
    ~GameMap();
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void timeout();//每一帧的处理函数

signals:
    void win();
    void lose();


private:
    Ui::GameMap *ui;
    bool isMoving;
    QTimer* timer;
    Tank* player1;
    int rebornTime;//刷新敌人的间隔时间
    int propTime;
    int eneNum;
    QList<QPoint> eneInitPos;
    Thing* base1;
    QList<Stone*> stones;
    QList<Thing*> things;
    QList<PcTank*> enes;
};

#endif // GAMEMAP_H
