#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    C_INIT_BD bd;
//    bd.Creation_BD();

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
    this->close();
}

void MainWindow::on_actionA_propos_triggered()
{

}

void MainWindow::on_btn_search_clicked()
{
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;
    if(ui->lineEdit_search->text()==""){
        ui->textEdit_resultat->clear();
        query.exec("select * from TPatient");
        while (query.next()) {
            QString name = query.value(0).toString()+" "+ query.value(1).toString()+" "+ query.value(2).toString()
                        +" "+ query.value(3).toString()
                        +" "+ query.value(4).toString()
                        +" "+ query.value(5).toString()
                        +" "+ query.value(6).toString()
                        +" "+ query.value(7).toString()
                        +" "+ query.value(8).toString();
            ui->textEdit_resultat->append(name);
        }
     }else{
        ui->textEdit_resultat->clear();
        ui->textEdit_resultat->append("Resultat:\n");

    }
    bd.Close_BD();
}
