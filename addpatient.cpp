#include "addpatient.h"
#include "ui_addpatient.h"

AddPatient::AddPatient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
    QRegExp regExp("[A-Z0-9\-]{0,2}");
    //QRegExpValidator *pRevalidotor = new QRegExpValidator(regExp, this);
    ui->lineEdit_priorite->setValidator(new QRegExpValidator(regExp, this));
}

AddPatient::~AddPatient()
{
    delete ui;
}

void AddPatient::on_pushButton_submit_clicked()
{
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;
    query.exec("select * from TPatient");
    query.last();
    int id=query.value(0).toInt();
    id=id+1;
    QString sql="insert into TPatient values("
            +QString::number(id)+","+"'"
            +ui->lineEdit_nom->text() +"'"+","+"'"
            +ui->lineEdit_prenom->text() +"'"+","+"'"
            +ui->lineEdit_adresse->text() +"'"+","+"'"
            +ui->lineEdit_ville->text() +"'"+","+"'"
            +ui->lineEdit_cp->text() +"'"+","+"'"
            +ui->textEdit_commentaire->toPlainText()+"'"+","+"'"
            +ui->lineEdit_tel->text()+"'"+","+"'"
            +ui->dateTimeEdit_date->text()+"'" +","
            +ui->lineEdit_duree->text()+","
            +ui->lineEdit_priorite->text()+")";
    bool b_test= query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Insertion de données dans TPatient impossible !\n";
    }else{
        this->close();
    }
    bd.Close_BD();
}

void AddPatient::on_pushButton_cencel_clicked()
{
    this->close();
}
