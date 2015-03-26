#include <QApplication>
#include "login.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
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
