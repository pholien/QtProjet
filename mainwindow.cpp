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

    connect(ui->tableWidget_resultat,SIGNAL(clicked(QModelIndex)),this,SLOT(modifierPatient(QModelIndex)));

    ui->tableWidget_resultat->setColumnCount(7);//设置列数
    ui->tableWidget_resultat->setColumnWidth(0,90);
    ui->tableWidget_resultat->setColumnWidth(1,200);
    ui->tableWidget_resultat->setColumnWidth(2,200);
    ui->tableWidget_resultat->setColumnWidth(3,200);
    ui->tableWidget_resultat->setColumnWidth(4,100);
    ui->tableWidget_resultat->setColumnWidth(5,70);
    ui->tableWidget_resultat->setColumnWidth(6,70);

//    ui->tableWidget_resultat->setRowCount(5);//设置行数
    ui->tableWidget_resultat->setShowGrid(true);//显示表格线
    ui->tableWidget_resultat->setAlternatingRowColors(true);//设置隔行颜色，即一灰一白
//    ui->tableWidget_resultat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置平分每列
//    ui->tableWidget_resultat->horizontalHeader()->setStretchLastSection(QHeaderView::Stretch);//设置最后一列补齐表格
    ui->tableWidget_resultat->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选择
    ui->tableWidget_resultat->horizontalHeader()->setSectionsMovable(true);//设置列可移动
    ui->tableWidget_resultat->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能选中一行
    ui->tableWidget_resultat->setEditTriggers(QAbstractItemView::NoEditTriggers);   //设置每行内容不可更改
    ui->tableWidget_resultat->verticalHeader()->setHidden(true); //去掉每行的行号
    /*设置表头*/
    QStringList header;
    header<<"Identification"<<"Nom"<<"Prénom"<<"Date Début"<<"Durée"<<"Modifier"<<"Supprimer";
    ui->tableWidget_resultat->setHorizontalHeaderLabels(header);
//    ui->tableWidget_resultat->

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
    Propre  d;
    d.exec();
}

void MainWindow::on_btn_search_clicked()
{
    C_INIT_BD bd;
    bd.Join_BD();
    QSqlQuery query;

    int numC=ui->tableWidget_resultat->rowCount();
    for(;numC>=0;numC--){
        ui->tableWidget_resultat->removeRow(numC);
    }

    QString str=ui->lineEdit_search->text();
    if(str.compare("")==0)
    {
        query.exec("select * from TPatient");
     }
    else
    {
        QString sql="select * from TPatient where Nom='"+str+"' or id='"+str+"' or Prenom='"+str+"' or DateConsultation='"+str+"'";
        query.exec(sql);
//        qDebug()<<sql<<" "<<query.value(0).toString();
    }
    int i=0;
    for(; query.next(); i++)
    {
        ui->tableWidget_resultat->insertRow(i);
        ui->tableWidget_resultat->setItem( i, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tableWidget_resultat->setItem( i, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tableWidget_resultat->setItem( i, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tableWidget_resultat->setItem( i, 3, new QTableWidgetItem(query.value(8).toString()));
        ui->tableWidget_resultat->setItem( i, 4, new QTableWidgetItem(query.value(9).toString()+" mn"));

        QLabel *modifier = new QLabel();
        modifier->setText("Modifier");
        modifier->setCursor(Qt::PointingHandCursor);
        ui->tableWidget_resultat->setCellWidget(i,5,modifier);


        QLabel *supprimer=new QLabel();
        supprimer->setText("supprimer");
        supprimer->setCursor(Qt::PointingHandCursor);
        ui->tableWidget_resultat->setCellWidget(i,6,supprimer);

//        QPushButton *modifier=new QPushButton();
//        modifier->setText("Modifier");
//        ui->tableWidget_resultat->setCellWidget(i,5,modifier);

//        QPushButton *supprimer=new QPushButton();
//        supprimer->setText("Supprimer");
//        ui->tableWidget_resultat->setCellWidget(i,6,supprimer);
    }
    if(i==0){
        ui->tableWidget_resultat->insertRow(0);
        ui->tableWidget_resultat->setItem(0, 0, new QTableWidgetItem("No record"));
    }
    bd.Close_BD();
}

void MainWindow:: modifierPatient(QModelIndex index){
   if(index.column()>=5)
    qDebug()<<index.row();
}
