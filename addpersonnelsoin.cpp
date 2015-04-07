#include "addpersonnelsoin.h"
#include "ui_addpersonnelsoin.h"

AddPersonnelSoin::AddPersonnelSoin(QWidget *parent,QString id) :
    QDialog(parent),
    ui(new Ui::AddPersonnelSoin)
{
    ui->setupUi(this);
    connect(ui->comboBox_type,SIGNAL(currentTextChanged(QString)),this,SLOT(EnableWidgt(QString)));
    ui->lineEdit_login->setEnabled(false);
    ui->lineEdit_mdp->setEnabled(false);
    this->setInfo(id);
}

void AddPersonnelSoin::setInfo(QString id)
{
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query,query2;
    query.exec("select * from TType");
    while(query.next()){
        ui->comboBox_type->addItem(query.value(1).toString());
    }
    if(id!="")
    {
        this->modifierID=id;
        query.exec("select * from TRessource where id='"+id+"'");
        query.first();
        ui->lineEdit_nom->setText(query.value(1).toString());
        ui->lineEdit_prenom->setText(query.value(2).toString());
        query2.exec("select Label from TType where Id ='"+query.value(3).toString()+"'");
        query2.first();
        ui->comboBox_type->setCurrentText(query2.value(0).toString());
        if(query2.value(0).toString()=="Informaticien"){
            this->EnableWidgt("Informaticien");
            query2.exec("select * from TCompte where IdRessource='"+id+"'");
            query2.first();
            ui->lineEdit_login->setText(query2.value(2).toString());
            ui->lineEdit_mdp->setText(query2.value(3).toString());
        }
    }
    bd.Close_BD();
}

AddPersonnelSoin::~AddPersonnelSoin()
{
    delete ui;
}
void AddPersonnelSoin::EnableWidgt(QString str){
    if(str=="Informaticien"){
        ui->lineEdit_login->setEnabled(true);
        ui->lineEdit_mdp->setEnabled(true);
    }else{
        ui->lineEdit_login->setEnabled(false);
        ui->lineEdit_mdp->setEnabled(false);
    }
}

void AddPersonnelSoin::on_pushButton_submit_clicked()
{
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;
    QString sql;
    if(this->windowTitle()=="Ajouter")
    {
        query.exec("select * from TRessource");
        query.last();
        int id=query.value(0).toInt();
        id=id+1;
        query.exec("select * from TType where Label='"+ui->comboBox_type->currentText()+"'");
        query.first();
        QString idType=query.value(0).toString();
        sql="insert into TRessource values("
                +QString::number(id)+","+"'"
                +ui->lineEdit_nom->text() +"' , '"
                +ui->lineEdit_prenom->text() +"' , '"
                +idType+"')";
        if(ui->comboBox_type->currentText()=="Informaticien")
        {
            query.exec("select * from TCompte");
            query.last();
            int id2=query.value(0).toInt();
            id2=id2+1;
            QString sql2="insert into TCompte values("
                    +QString::number(id2)+","+QString::number(id)+","+"'"
                    +ui->lineEdit_login->text() +"' , '"
                    +ui->lineEdit_mdp->text() +"')";
            query.exec(sql2);
        }
    }
    else if(this->windowTitle()=="Modifier")
    {
        query.exec("select * from TRessource");
        query.last();
        int id=query.value(0).toInt();
        id=id+1;
        query.exec("select * from TType where Label='"+ui->comboBox_type->currentText()+"'");
        query.first();
        QString idType=query.value(0).toString();
        sql="update TRessource set Nom='"+ui->lineEdit_nom->text()
                +"', Prenom='"+ui->lineEdit_prenom->text()
                +"', IdType='"+idType
                +"' where id="+this->modifierID;
        if(ui->comboBox_type->currentText()=="Informaticien")
        {
            QString sql2="update TCompte set Login='"+ui->lineEdit_login->text()+"',  MdP='"+ui->lineEdit_mdp->text()
                    +"' where IdRessource='"+this->modifierID+"'";
            query.exec(sql2);
        }
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

void AddPersonnelSoin::on_pushButton_cancel_clicked()
{
    this->close();
}
