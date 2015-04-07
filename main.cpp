#include <QApplication>
#include "vue_logindlg.h"
#include "vue_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    C_INIT_BD bd;
    bd.Creation_BD();

    Login dlg;
    MainWindow w;

    if( dlg.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else{
        bd.Close_BD();
        return 0;
    }
}
