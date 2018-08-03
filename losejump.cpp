#include "losejump.h"
#include "ui_losejump.h"

LoseJump::LoseJump(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoseJump)
{
    this->setFixedSize(1200,900);
    this->setStyleSheet("background-color:black");
    ui->setupUi(this);
}

LoseJump::~LoseJump()
{
    delete ui;
}

void LoseJump::on_pushButton_clicked()
{
    emit restart();
    this->close();
}

void LoseJump::on_pushButton_2_clicked()
{
    emit backToMenu();
    this->close();
}
