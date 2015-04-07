#include "vue_ressourcedlg.h"
#include "ui_ressourcedlg.h"
#include "controleur_ressource.h"
RessourceDlg::RessourceDlg(QWidget *parent,QString id) :
    QDialog(parent),
    ui(new Ui::RessourceDlg)
{
    ui->setupUi(this);
    connect(ui->comboBox_type,SIGNAL(currentTextChanged(QString)),this,SLOT(EnableWidgt(QString)));
    setWindowFlags(Qt::WindowCloseButtonHint);
    QRegExp regExp_Nom("^[A-Z][a-z]+");//chaîne de caractères dont la première lettre est en majuscule, le reste en minuscule
    ui->lineEdit_nom->setValidator(new QRegExpValidator(regExp_Nom, this));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(regExp_Nom, this));

    ui->lineEdit_login->setEnabled(false);
    ui->lineEdit_mdp->setEnabled(false);
    this->setInfo(id);
}

void RessourceDlg::setInfo(QString id)
{
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
}

RessourceDlg::~RessourceDlg()
{
    delete ui;
}

void RessourceDlg::EnableWidgt(QString str){
    if(str=="Informaticien"){
        ui->lineEdit_login->setEnabled(true);
        ui->lineEdit_mdp->setEnabled(true);
    }else{
        ui->lineEdit_login->setEnabled(false);
        ui->lineEdit_mdp->setEnabled(false);
    }
}

void RessourceDlg::on_pushButton_submit_clicked()
{
    QSqlQuery query;
    query.exec("select * from TType where Label='"+ui->comboBox_type->currentText()+"'");
    query.first();
    int idType=query.value(0).toInt();
    Ressource r;
    r.setNom(ui->lineEdit_nom->text());
    r.setPrenom(ui->lineEdit_prenom->text());
    r.setType(idType);
    if(idType==7)
    {
        r.setLogin(ui->lineEdit_login->text());
        r.setMdP(ui->lineEdit_mdp->text());
    }
    if(this->windowTitle()=="Ajouter")
    {
        if(AddRessource(r)==true)
            accept();
    }
    else if(this->windowTitle()=="Modifier")
    {
        if(ModifierRessource(r,this->modifierID)==true)
            accept();
    }
}

void RessourceDlg::on_pushButton_cancel_clicked()
{
    this->close();
}
