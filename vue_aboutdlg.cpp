#include "vue_aboutdlg.h"
#include "ui_aboutdlg.h"

AboutDlg::AboutDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDlg)
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    ui->setupUi(this);
}

AboutDlg::~AboutDlg()
{
    delete ui;
}
