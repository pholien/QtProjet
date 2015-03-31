#include "addpatient.h"
#include "ui_addpatient.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

AddPatient::AddPatient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
}

AddPatient::~AddPatient()
{
    delete ui;
}

void AddPatient::on_pushButton_submit_clicked()
{
    QSqlQuery query;
    query.exec("select * from TPatient");
    query.last();
    int id=query.value(0).toInt();
    id=id+1;
    QString sql="insert into TPatient values("
            +QString::number(id)+","
            +ui->lineEdit_nom->text() +","
            +ui->lineEdit_prenom->text() +","
            +ui->lineEdit_adresse->text() +","
            +ui->lineEdit_ville->text() +","
            +ui->lineEdit_cp->text() +","
            +ui->textEdit_commentaire->toPlainText()+","
            +ui->lineEdit_tel->text()+","
            +ui->dateTimeEdit_date->text() +","
            +ui->lineEdit_duree->text() +","
            +ui->lineEdit_priorite->text() +")";
   qDebug() << sql;
   bool b_test= query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Insertion de données dans TPatient impossible !\n";
    }else{
        this->close();
    }
}

void AddPatient::on_pushButton_cencel_clicked()
{
    this->close();
}
