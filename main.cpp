#include "widget.h"
#include "start.h"
#include "menu.h"
#include <QApplication>
#include <QTime>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    Menu menu;
    menu.show();
    return a.exec();
}
