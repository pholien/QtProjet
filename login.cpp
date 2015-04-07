#include "login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->pwdLineEdit->setFocus();
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;
    query.exec("select Login from TCompte");
    while(query.next()){
        ui->comboBox_login->addItem(query.value(0).toString());
    }
    bd.Close_BD();
}


Login::~Login()
{
    delete ui;
}

void Login::on_OKPushButton_clicked()
{
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;
    query.exec("select MdP from TCompte where Login='"+ui->comboBox_login->currentText()+"'");
    query.first();
    if(ui->pwdLineEdit->text()==query.value(0).toString()){
        bd.Close_BD();
        accept();
    }else{
        QMessageBox::warning(this,tr("Warning"),("Login ou Mot de passe incorrecte !"),QMessageBox::Yes);
        ui->pwdLineEdit->clear();
        ui->pwdLineEdit->setFocus();
        bd.Close_BD();
    }
}

void Login::on_NOPushButton_clicked()
{
    this->close();
}
