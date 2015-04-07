#include "vue_patientdlg.h"
#include "ui_patientdlg.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QModelIndex>
#include "controleur_patient.h"

PatientDlg::PatientDlg(QWidget *parent, QString id) :
    QDialog(parent),
    ui(new Ui::PatientDlg)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowCloseButtonHint);
    QRegExp regExp_Nom("^[A-Z][a-z]+");//chaîne de caractères dont la première lettre est en majuscule, le reste en minuscule
    ui->lineEdit_nom->setValidator(new QRegExpValidator(regExp_Nom, this));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(regExp_Nom, this));
    ui->lineEdit_ville->setValidator(new QRegExpValidator(regExp_Nom, this));

    QRegExp regExp_Code("^[1-9][0-9]+");//uniquement des chiffres pour simplifier
    ui->lineEdit_cp->setValidator(new QRegExpValidator(regExp_Code, this));
    ui->lineEdit_tel->setValidator(new QRegExpValidator(regExp_Code, this));
    ui->lineEdit_duree->setValidator(new QRegExpValidator(regExp_Code, this));

    QRegExp regExp_Priorite("[1-5]{1}");//de 5 à 1 avec 5 comme plus prioritaire et 1 valeur par défaut
    ui->lineEdit_priorite->setValidator(new QRegExpValidator(regExp_Priorite, this));

    ui->tableWidget_ress->setColumnCount(2);//设置列数
    ui->tableWidget_ress->setShowGrid(true);//显示表格线
    ui->tableWidget_ress->setAlternatingRowColors(true);//设置隔行颜色，即一灰一白
    ui->tableWidget_ress->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置平分每列
    ui->tableWidget_ress->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选择
    ui->tableWidget_ress->verticalHeader()->setHidden(true); //去掉每行的行号
    ui->tableWidget_ress->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    QStringList header;
    header<<"Id"<<"Prénom";
    ui->tableWidget_ress->setHorizontalHeaderLabels(header);

    this->modID=id;
    this->setInfo(id);
}

void PatientDlg::setInfo(QString id){
    QString sql="select * from TRessource";
    Patient *p=SearchPatient(id);
    QSqlQuery query;
    query.exec(sql);
    for(int i=0;query.next();i++){
        ui->tableWidget_ress->insertRow(i);
        QTableWidgetItem *checkBox = new QTableWidgetItem(query.value(0).toString());
        checkBox->setCheckState(Qt::Unchecked);
        if(p!=NULL)
            for(int i=0;i<p->vIdRessource.size();i++)
            {
                if(query.value(0).toInt()==p->vIdRessource.at(i))
                {
                    checkBox->setCheckState(Qt::Checked);
                    break;
                }
            }
        ui->tableWidget_ress->setItem(i, 0, checkBox);
        ui->tableWidget_ress->setItem( i, 1, new QTableWidgetItem(query.value(1).toString()));
    }
    if(p!=NULL){
        ui->lineEdit_nom->setText(p->getNom());
        ui->lineEdit_prenom->setText(p->getPrenom());
        ui->lineEdit_adresse->setText(p->getAdresse());
        ui->lineEdit_ville->setText(p->getVille());
        ui->lineEdit_cp->setText(QString::number(p->getCP()));
        ui->textEdit_commentaire->append(p->getCommentaire());
        ui->lineEdit_tel->setText(p->getTelephone());
        ui->dateEdit_debut->setDate(p->getDateDebut());
        ui->lineEdit_duree->setText(QString::number(p->getDuree()));
        ui->lineEdit_priorite->setText(QString::number(p->getPriorite()));

    }else
    {
        ui->lineEdit_priorite->setText("1");
        ui->dateEdit_debut->setDate(QDate::currentDate());
    }
}

PatientDlg::~PatientDlg()
{
    delete ui;
}

bool PatientDlg::checkInput(){

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

void PatientDlg::on_pushButton_submit_clicked()
{
    if(checkInput()==false)
        return;
    Patient p;
    p.vIdRessource.clear();
    p.setNom(ui->lineEdit_nom->text());
    p.setPrenom(ui->lineEdit_prenom->text());
    p.setAdresse(ui->lineEdit_adresse->text());
    p.setVille(ui->lineEdit_ville->text());
    p.setCP(ui->lineEdit_cp->text().toInt());
    p.setCommentaire(ui->textEdit_commentaire->toPlainText());
    p.setTelephone(ui->lineEdit_tel->text());
    p.setDateDebut(ui->dateEdit_debut->date());
    p.setDuree(ui->lineEdit_duree->text().toInt());
    p.setPriorite(ui->lineEdit_priorite->text().toInt());
    for(int i=0;i<ui->tableWidget_ress->rowCount();i++)
    {
        if(ui->tableWidget_ress->item(i,0)->checkState()==Qt::Checked)
            p.vIdRessource.push_back(ui->tableWidget_ress->item(i,0)->text().toInt());
    }
    if(this->windowTitle()=="Ajouter")
    {
        if(AddPatient(p)==true){
            accept();
        }
    }
    else if(this->windowTitle()=="Modifier")
    {
        if(ModifierPatient(p,this->modID)==true){
            accept();
        }
    }
}

void PatientDlg::on_pushButton_cencel_clicked()
{
    this->close();
}
