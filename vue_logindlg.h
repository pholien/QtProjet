#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "c_init_bd.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_OKPushButton_clicked();
    void on_NOPushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
