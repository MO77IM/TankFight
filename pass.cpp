#include "pass.h"
#include "ui_pass.h"

Pass::Pass(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pass)
{
    this->setFixedSize(1200,900);
    this->setStyleSheet("background-color:black");
    ui->setupUi(this);
}

Pass::~Pass()
{
    delete ui;
}

void Pass::on_pushButton_clicked()
{
    emit end();
    this->close();
}
