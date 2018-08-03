#include "menu.h"
#include "ui_menu.h"


Menu::Menu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    this->setStyleSheet("background-color:black");

    level=1;

    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_pushButton_clicked()
{
    level=1;
    gamemap=new GameMap(1);
    gamemap->show();
    connect(gamemap,SIGNAL(win()),this,SLOT(receiveWin()));
    connect(gamemap,SIGNAL(lose()),this,SLOT(receiveLose()));
    this->hide();
}

void Menu::receiveWin(){
    level++;
    if(level>8){
        level=1;
        pass=new Pass();
        connect(pass,SIGNAL(end()),this,SLOT(back()));
        pass->show();
        return;
    }
    winjump=new WinJump();
    connect(winjump,SIGNAL(nextLevel()),this,SLOT(startNextLevel()));
    connect(winjump,SIGNAL(backToMenu()),this,SLOT(back()));
    winjump->show();
}

void Menu::receiveLose(){
    losejump=new LoseJump();
    connect(losejump,SIGNAL(restart()),this,SLOT(startNextLevel()));
    connect(losejump,SIGNAL(backToMenu()),this,SLOT(back()));
    losejump->show();
}

void Menu::startNextLevel(){
    gamemap=new GameMap(level);
    gamemap->show();
    connect(gamemap,SIGNAL(win()),this,SLOT(receiveWin()));
    connect(gamemap,SIGNAL(lose()),this,SLOT(receiveLose()));
}

void Menu::back(){
    this->show();
}

void Menu::on_pushButton_2_clicked()
{
    exit(0);
}

void Menu::on_pushButton_3_clicked()
{
    startNextLevel();
    this->hide();
}
