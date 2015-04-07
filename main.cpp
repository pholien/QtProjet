#include <QApplication>
#include "login.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    C_INIT_BD bd;
//    bd.Creation_BD();

    Login dlg;
    MainWindow w;

    if( dlg.exec()==QDialog::Accepted)
    {
        w.show();
        return a.exec();
    }
    else
        return 0;
}
