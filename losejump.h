#ifndef LOSEJUMP_H
#define LOSEJUMP_H

#include <QWidget>

namespace Ui {
class LoseJump;
}

class LoseJump : public QWidget
{
    Q_OBJECT

public:
    explicit LoseJump(QWidget *parent = 0);
    ~LoseJump();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void restart();
    void backToMenu();

private:
    Ui::LoseJump *ui;
};

#endif // LOSEJUMP_H
