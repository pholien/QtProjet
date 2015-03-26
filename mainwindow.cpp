#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addpatient.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
