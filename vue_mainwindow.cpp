#include "vue_mainwindow.h"
#include "ui_mainwindowdlg.h"
#include "controleur_patient.h"
#include "controleur_ressource.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
    QStatusBar *statusBar = this->statusBar();
    QLabel *mode = new QLabel( tr("  Time  ") );
    mode->setMinimumSize( mode->sizeHint() );
    mode->setAlignment( Qt::AlignCenter );
    mode->setText( tr("Ready") );
    mode->setToolTip( tr("The current working mode.") );
    statusBar->addPermanentWidget( mode );

    connect(ui->tableWidget_resultat,SIGNAL(clicked(QModelIndex)),this,SLOT(modifierPatient(QModelIndex)));
    connect(ui->lineEdit_search,SIGNAL(editingFinished()),this,SLOT(on_btn_search_clicked()));

    this->setWidget();
    this->afficherRess();
    this->on_btn_search_clicked();

    statusBar->showMessage( tr("Ready!!"));
}

void MainWindow::afficherRess(){
    ui->treeWidget_ress->clear();
    QList<QTreeWidgetItem *> rootList;

    QSqlQuery query,query2;
    QString sql="select * from TType";
    query.exec(sql);
    while(query.next()){
         QTreeWidgetItem *root = new QTreeWidgetItem;   //添加第一个父节点
         root->setText(0,query.value(1).toString());
         rootList.append(root);
         query2.exec("select * from TRessource where IdType ="+query.value(0).toString());
         while(query2.next()){
             root->addChild(new QTreeWidgetItem(root,QStringList(query2.value(1).toString())));
         }
    }
    ui->treeWidget_ress->insertTopLevelItems(0,rootList);
    ui->treeWidget_ress->expandAll();
}

void MainWindow::setWidget()
{

    ui->treeWidget_ress->setHeaderLabel("RESSOURCE");
    ui->lineEdit_search->setFocus();
    ui->tableWidget_resultat->setColumnCount(7);//设置列数
//    ui->tableWidget_resultat->setColumnWidth(0,90);
//    ui->tableWidget_resultat->setColumnWidth(1,200);
//    ui->tableWidget_resultat->setColumnWidth(2,200);
//    ui->tableWidget_resultat->setColumnWidth(3,200);
//    ui->tableWidget_resultat->setColumnWidth(4,100);
//    ui->tableWidget_resultat->setColumnWidth(5,70);
//    ui->tableWidget_resultat->setColumnWidth(6,70);

//    ui->tableWidget_resultat->setRowCount(5);//设置行数
    ui->tableWidget_resultat->setShowGrid(true);//显示表格线
    ui->tableWidget_resultat->setAlternatingRowColors(true);//设置隔行颜色，即一灰一白
    ui->tableWidget_resultat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置平分每列
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPatient_triggered()
{
    PatientDlg d;
    d.setWindowTitle("Ajouter");
    if(d.exec()==QDialog::Accepted)
    {
        this->on_btn_search_clicked();
    }
}

void MainWindow::on_actionPersonnelSoin_triggered()
{
    RessourceDlg d;
    d.setWindowTitle("Ajouter");
    if(d.exec()==QDialog::Accepted)
    {
        this->afficherRess();
    }
}

void MainWindow::on_actionQuitter_triggered()
{
    this->close();
}

void MainWindow::on_actionA_propos_triggered()
{
    AboutDlg dlg;
    dlg.exec();
}

void MainWindow::on_btn_search_clicked()
{
    QSqlQuery query;
    ui->statusBar->showMessage( tr("Search Button clicked"),2000);
    int numC=ui->tableWidget_resultat->rowCount();
    for(;numC>=0;numC--){
        ui->tableWidget_resultat->removeRow(numC);
    }

    QString str=ui->lineEdit_search->text();
    bool boo;
    if(str.compare("")==0)
    {
        boo=query.exec("select * from TPatient");
        if(!boo)
        {
            qDebug() << query.lastError().text();
            qDebug() << "can't find !\n";
        }
     }
    else
    {
        QString sql="select * from TPatient where Nom='"+str+"' or Id='"+str+"' or Prenom='"+str+"' or DateConsultation='"+str+"'";
        boo=query.exec(sql);
        if(!boo)
        {
            qDebug() << query.lastError().text();
        }

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
        modifier->setText("      Modifier");
        modifier->setCursor(Qt::PointingHandCursor);
        QPalette pa;
        pa.setColor(QPalette::Text,Qt::blue);
        modifier->setPalette(pa);
        ui->tableWidget_resultat->setCellWidget(i,5,modifier);


        QLabel *supprimer=new QLabel();
        supprimer->setText("     Supprimer");
        supprimer->setCursor(Qt::PointingHandCursor);
        QPalette pa2;
        pa2.setColor(QPalette::Text,Qt::red);
        supprimer->setPalette(pa2);
        ui->tableWidget_resultat->setCellWidget(i,6,supprimer);

    }
    if(i==0){
        ui->tableWidget_resultat->insertRow(0);
        ui->tableWidget_resultat->setItem(0, 0, new QTableWidgetItem("No record"));
    }
}

void MainWindow:: modifierPatient(QModelIndex index)
{
   QString id=ui->tableWidget_resultat->item(index.row(),0)->text();
   if(index.column()==5){
       PatientDlg d(0,id);
       d.setWindowTitle("Modifier");
       if(d.exec()==QDialog::Accepted)
       {
           this->on_btn_search_clicked();
       }
   }
   else if(index.column()==6)
   {
        QMessageBox::StandardButton rb=QMessageBox::warning(this,tr("Warning"),("Do you want to delete this record?"),QMessageBox::Ok|QMessageBox::Cancel);
        if (rb==QMessageBox::Ok)
        {
            if(DeletePatient(id)==true)
                this->on_btn_search_clicked();
            else
                QMessageBox::warning(this,tr("Warning"),("Con't delete"),QMessageBox::Ok);
        }
   }
}

void MainWindow::on_pushButton_ModRess_clicked()
{
    QString id=this->getRessItemId();
    if(id=="")return;
    RessourceDlg dlg(0,id);
    dlg.setWindowTitle("Modifier");
    if(dlg.exec()==QDialog::Accepted)
    {
        this->afficherRess();
    }
}

void MainWindow::on_pushButton_SuppRess_clicked()
{
    QString id=this->getRessItemId();
    if(id=="")return;
    QMessageBox::StandardButton rb=QMessageBox::warning(this,tr("Warning"),("Do you want to delete this ressource?"),QMessageBox::Ok|QMessageBox::Cancel);
    if (rb==QMessageBox::Ok)
    {
        if(DeleteRessource(id)==true)
            this->afficherRess();
        else
            QMessageBox::warning(this,tr("Warning"),("Con't delete"),QMessageBox::Ok);
    }
}

QString MainWindow::getRessItemId()//注意，此处查ID无法解决姓名重复问题
{
    QString id="";
    if(ui->treeWidget_ress->currentItem()==NULL || ui->treeWidget_ress->currentItem()->parent()==NULL){
        QMessageBox::warning(this,tr("Warning"),("Choisir une personnel de soins svp!!!"),QMessageBox::Ok);
    }else{
        QSqlQuery query;
        query.exec("select Id from TRessource where Nom='"+ui->treeWidget_ress->currentItem()->text(0)+"'");
        query.first();
        id=query.value(0).toString();
    }
    return id;
}
