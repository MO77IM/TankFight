#ifndef WINJUMP_H
#define WINJUMP_H

#include <QWidget>

namespace Ui {
class WinJump;
}

class WinJump : public QWidget
{
    Q_OBJECT

public:
    explicit WinJump(QWidget *parent = 0);
    ~WinJump();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void nextLevel();
    void backToMenu();

private:
    Ui::WinJump *ui;
};

#endif // WINJUMP_H
