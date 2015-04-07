#ifndef ADDPERSONNELSOIN_H
#define ADDPERSONNELSOIN_H

#include <QDialog>
#include "c_init_bd.h"
namespace Ui {
class AddPersonnelSoin;
}

class AddPersonnelSoin : public QDialog
{
    Q_OBJECT

public:
    explicit AddPersonnelSoin(QWidget *parent = 0,QString id="");
    ~AddPersonnelSoin();

private slots:
    void on_pushButton_submit_clicked();
    void EnableWidgt(QString);

    void on_pushButton_cancel_clicked();

private:
    Ui::AddPersonnelSoin *ui;
    QString modifierID;
    void setInfo(QString id);
};

#endif // ADDPERSONNELSOIN_H
