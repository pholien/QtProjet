#include "login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
}


Login::~Login()
{
    delete ui;
}

void Login::on_OKPushButton_clicked()
{
    if(ui->userLineEdit->text()==tr("")&&ui->pwdLineEdit->text()==tr(""))
        accept();
    else
    {
        QMessageBox::warning(this,tr("Warning"),("user name or password wrong!"),QMessageBox::Yes);

        ui->userLineEdit->clear();
        ui->pwdLineEdit->clear();
        ui->userLineEdit->setFocus();
    }
}

void Login::on_NOPushButton_clicked()
{
    this->close();
}
