#include "addpatient.h"
#include "ui_addpatient.h"

AddPatient::AddPatient(QWidget *parent, QString info) :
    QDialog(parent),
    ui(new Ui::AddPatient)
{
    ui->setupUi(this);
    QRegExp regExp_Nom("^[A-Z][a-z]+");//chaîne de caractères dont la première lettre est en majuscule, le reste en minuscule
    ui->lineEdit_nom->setValidator(new QRegExpValidator(regExp_Nom, this));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(regExp_Nom, this));
    ui->lineEdit_ville->setValidator(new QRegExpValidator(regExp_Nom, this));

    QRegExp regExp_Code("^[1-9][0-9]+");//uniquement des chiffres pour simplifier
    ui->lineEdit_cp->setValidator(new QRegExpValidator(regExp_Code, this));
    ui->lineEdit_tel->setValidator(new QRegExpValidator(regExp_Code, this));

    QRegExp regExp_Priorite("[1-5]{1}");//de 5 à 1 avec 5 comme plus prioritaire et 1 valeur par défaut
    ui->lineEdit_priorite->setValidator(new QRegExpValidator(regExp_Priorite, this));

    this->modID=info;
    this->setInfo(info);
}

void AddPatient::setInfo(QString info){
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;
    QString sql;
    if(info != ""){
        sql="select * from TPatient where Id='"+info+"'";
        query.exec(sql);
        query.first();
        ui->lineEdit_nom->setText(query.value(1).toString());
        ui->lineEdit_prenom->setText(query.value(2).toString());
        ui->lineEdit_adresse->setText(query.value(3).toString());
        ui->lineEdit_ville->setText(query.value(4).toString());
        ui->lineEdit_cp->setText(query.value(5).toString());
        ui->textEdit_commentaire->append(query.value(6).toString());
        ui->lineEdit_tel->setText(query.value(7).toString());
        ui->dateEdit_debut->setDate(query.value(8).toDate());
        ui->lineEdit_duree->setText(query.value(9).toString());
        ui->lineEdit_priorite->setText(query.value(10).toString());
    }else{
        sql="select * from TRessource";
        query.exec(sql);
        ui->lineEdit_priorite->setText("1");
        ui->dateEdit_debut->setDate(QDate::currentDate());
        while(query.next()){
            ui->comboBox_res->addItem(query.value(1).toString());
        }
    }
    bd.Close_BD();
}

AddPatient::~AddPatient()
{
    delete ui;
}

bool AddPatient::checkInput(){

    if( ui->lineEdit_nom->text()=="")
    {
        ui->lineEdit_nom->setFocus();
        return false;
    }
    else if(ui->lineEdit_prenom->text()=="")
    {
        ui->lineEdit_prenom->setFocus();
        return false;
    }
    else if(ui->lineEdit_ville->text()=="")
    {
        ui->lineEdit_ville->setFocus();
        return false;
    }
    else if( ui->lineEdit_cp->text()=="")
    {
        ui->lineEdit_cp->setFocus();
        return false;
    }
    else if(ui->lineEdit_adresse->text()=="")
    {
        ui->lineEdit_adresse->setFocus();
        return false;
    }
    else if(ui->lineEdit_duree->text()=="")
    {
        ui->lineEdit_duree->setFocus();
        return false;
    }
    else if(ui->lineEdit_priorite->text()=="")
    {
        ui->lineEdit_priorite->setFocus();
        return false;
    }
    else if(ui->dateEdit_debut->date() > QDate::currentDate())
    {
        ui->dateEdit_debut->setDate(QDate::currentDate());
        ui->dateEdit_debut->setFocus();
        return false;
    }
    else
        return true;
}

void AddPatient::on_pushButton_submit_clicked()
{
    if(checkInput()==false)
        return;
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
                +ui->lineEdit_nom->text() +"' , '"
                +ui->lineEdit_prenom->text() +"' , '"
                +ui->lineEdit_adresse->text() +"' , '"
                +ui->lineEdit_ville->text() +"' , '"
                +ui->lineEdit_cp->text() +"' , '"
                +ui->textEdit_commentaire->toPlainText()+"' , '"
                +ui->lineEdit_tel->text()+"' , '"
                +ui->dateEdit_debut->text()+"'" +","
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
                +"DateConsultation='"+ui->dateEdit_debut->text()+"'"
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
