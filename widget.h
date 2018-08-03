#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "tank.h"
#include "bullet.h"
#include <QLabel>
#include "stone.h"
#include "metal.h"
#include "shrub.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void paintEvent(QPaintEvent*);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    ~Widget();

private slots:
    void timeout();
    void receivestart();

signals:
    void gameend();

private:
    Ui::Widget *ui;
    bool isMoving;
    Tank* player1;
    QTimer* timer;
    Tank* thing;
    Tank* thing2;
    Stone* stone;
    Metal* metal;
    Shrub* shrub1;
    Shrub* shrub2;
    Thing* wt;
};

#endif // WIDGET_H
