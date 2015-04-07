#include "vue_logindlg.h"
#include "ui_logindlg.h"
#include "controleur_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    ui->pwdLineEdit->setEchoMode(QLineEdit::Password);
    ui->pwdLineEdit->setFocus();
    QSqlQuery query;
    query.exec("select Login from TCompte");
    while(query.next()){
        ui->comboBox_login->addItem(query.value(0).toString());
    }
}


Login::~Login()
{
    delete ui;
}

void Login::on_OKPushButton_clicked()
{

    if(isCorrectCompte(ui->comboBox_login->currentText(),ui->pwdLineEdit->text())){
        accept();
    }else{
        QMessageBox::warning(this,tr("Warning"),("Login ou Mot de passe incorrecte !"),QMessageBox::Yes);
        ui->pwdLineEdit->clear();
    }
}

void Login::on_NOPushButton_clicked()
{
    this->close();
}
