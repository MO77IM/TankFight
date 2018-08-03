#ifndef PASS_H
#define PASS_H

#include <QWidget>

namespace Ui {
class Pass;
}

class Pass : public QWidget
{
    Q_OBJECT

public:
    explicit Pass(QWidget *parent = 0);
    ~Pass();

signals:
    void end();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Pass *ui;
};

#endif // PASS_H
