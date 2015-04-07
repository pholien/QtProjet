#ifndef ADDPATIENT_H
#define ADDPATIENT_H

#include <QDialog>
#include "c_init_bd.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QModelIndex>

namespace Ui {
class AddPatient;
}

class AddPatient : public QDialog
{
    Q_OBJECT

public:
    explicit AddPatient(QWidget *parent = 0, QString info="");
    ~AddPatient();

private slots:
    void on_pushButton_submit_clicked();

    void on_pushButton_cencel_clicked();

private:
    Ui::AddPatient *ui;
    bool checkInput();
    void setInfo(QString info);
    QString modID;
};

#endif // ADDPATIENT_H
