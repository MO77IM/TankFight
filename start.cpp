#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
}

Start::~Start()
{
    delete ui;
}

void Start::on_pushButton_clicked()
{
    this->hide();
    gamemap=new GameMap();
    connect(gamemap,SIGNAL(gameend()),this,SLOT(receiveend()));
    gamemap->show();
}

void Start::receiveend(){
    this->show();
}
