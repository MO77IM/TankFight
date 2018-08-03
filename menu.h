#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "gamemap.h"
#include "winjump.h"
#include "losejump.h"
#include "pass.h"
#include <QPushButton>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void receiveWin();
    void receiveLose();
    void startNextLevel();
    void back();

    void on_pushButton_3_clicked();

private:
    Ui::Menu *ui;
    GameMap* gamemap;
    WinJump* winjump;
    LoseJump* losejump;
    Pass* pass;
    int level;
};

#endif // MENU_H
