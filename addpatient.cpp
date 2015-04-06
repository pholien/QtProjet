#include "addpatient.h"
#include "ui_addpatient.h"

AddPatient::AddPatient(QWidget *parent, QString info) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
    QRegExp regExp("[0-6]{1}");
    ui->lineEdit_priorite->setValidator(new QRegExpValidator(regExp, this));
    this->modID=info;
    this->setInfo(info);
}

void AddPatient::setInfo(QString info){
    if(info != ""){
        C_INIT_BD bd;
        bd.Join_BD();
        QSqlQuery query;
        QString sql="select * from TPatient where Id='"+info+"'";
        query.exec(sql);
        query.first();
        ui->lineEdit_nom->setText(query.value(1).toString());
        ui->lineEdit_prenom->setText(query.value(2).toString());
        ui->lineEdit_adresse->setText(query.value(3).toString());
        ui->lineEdit_ville->setText(query.value(4).toString());
        ui->lineEdit_cp->setText(query.value(5).toString());
        ui->textEdit_commentaire->append(query.value(6).toString());
        ui->lineEdit_tel->setText(query.value(7).toString());
        //ui->dateTimeEdit_date->set
        ui->lineEdit_duree->setText(query.value(9).toString());
        ui->lineEdit_priorite->setText(query.value(10).toString());
        bd.Close_BD();
    }
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
    QString sql;
    if(this->windowTitle()=="Ajouter")
    {
        query.exec("select * from TPatient");
        query.last();
        int id=query.value(0).toInt();
        id=id+1;
        sql="insert into TPatient values("
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
    }
    else if(this->windowTitle()=="Modifier")
    {
        sql="update TPatient set Nom='"+ui->lineEdit_nom->text() +"'"+","
                +"Prenom='"+ui->lineEdit_prenom->text() +"'"+","
                +"Adresse='"+ui->lineEdit_adresse->text() +"'"+","
                +"Ville='"+ui->lineEdit_ville->text() +"'"+","
                +"CP='"+ui->lineEdit_cp->text() +"'"+","
                +"Commentaire='"+ui->textEdit_commentaire->toPlainText()+"'"+","
                +"Tel='"+ui->lineEdit_tel->text()+"'"+","
                +"DateConsultation='"+ui->dateTimeEdit_date->text()+"'"
                +", DureeConsultation="+ui->lineEdit_duree->text()
                +", Priorite="+ui->lineEdit_priorite->text()
                +" where id=" +this->modID;
    }
    bool b_test= query.exec(sql);
    if(!b_test)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Insertion de données dans TPatient impossible !\n";
        bd.Close_BD();
    }
    else
    {
        bd.Close_BD();
        accept();
    }
}

void AddPatient::on_pushButton_cencel_clicked()
{
    this->close();
}
