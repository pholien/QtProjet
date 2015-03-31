#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addpatient.h"

#include <QSqlQuery>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bd.Creation_BD();

    QStatusBar *statusBar = this->statusBar();
    QLabel *mode = new QLabel( tr("  Time  ") );
    mode->setMinimumSize( mode->sizeHint() );
    mode->setAlignment( Qt::AlignCenter );
    mode->setText( tr("Ready") );
    mode->setToolTip( tr("The current working mode.") );
    statusBar->addPermanentWidget( mode );
    statusBar->showMessage( tr("Connexion"),4000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPatient_triggered()
{
    AddPatient d;
    d.exec();
}

void MainWindow::on_actionPersonnelSoin_triggered()
{

}

void MainWindow::on_actionQuitter_triggered()
{

}

void MainWindow::on_actionA_propos_triggered()
{

}

void MainWindow::on_btn_search_clicked()
{
    if(ui->lineEdit_search->text()!=""){
        ui->textEdit_resultat->clear();
        ui->textEdit_resultat->append("add key world please!!!");
    }else{
        ui->textEdit_resultat->clear();

        QSqlQuery query;
        query.exec("select * from TPatient");
        int num=query.record().count();
       for(int i=0; i<num; i++){
            QString name = query.value(0).toString()+" "+ query.value(1).toString();
            ui->textEdit_resultat->append(name);
            query.next();
        }
    }
}
