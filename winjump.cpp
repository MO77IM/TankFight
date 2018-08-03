#include "winjump.h"
#include "ui_winjump.h"

WinJump::WinJump(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WinJump)
{
    ui->setupUi(this);
    this->setFixedSize(1200,900);
    this->setStyleSheet("background-color:black");
}

WinJump::~WinJump()
{
    delete ui;
}

void WinJump::on_pushButton_clicked()
{
    emit nextLevel();
    this->close();
}

void WinJump::on_pushButton_2_clicked()
{
    emit backToMenu();
    this->close();
}
