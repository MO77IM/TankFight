#ifndef START_H
#define START_H

#include <QDialog>
#include <gamemap.h>

namespace Ui {
class Start;
}

class Start : public QDialog
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    ~Start();

signals:
    void startgame();

private slots:
    void on_pushButton_clicked();
    void receiveend();

private:
    Ui::Start *ui;
    GameMap* gamemap;
};

#endif // START_H
