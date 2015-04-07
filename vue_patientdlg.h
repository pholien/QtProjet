#ifndef PATIENTDLG_H
#define PATIENTDLG_H

#include <QDialog>
#include "c_init_bd.h"


namespace Ui {
class PatientDlg;
}

class PatientDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PatientDlg(QWidget *parent = 0, QString info="");
    ~PatientDlg();

private slots:
    void on_pushButton_submit_clicked();

    void on_pushButton_cencel_clicked();

private:
    Ui::PatientDlg *ui;
    bool checkInput();
    void setInfo(QString info);
    QString modID;
};

#endif // PATIENTDLG_H
