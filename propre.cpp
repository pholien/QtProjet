#include "propre.h"
#include "ui_propre.h"

Propre::Propre(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Propre)
{
    ui->setupUi(this);
}

Propre::~Propre()
{
    delete ui;
}

void Propre::on_pushButton_clicked()
{
    this->close();
}
