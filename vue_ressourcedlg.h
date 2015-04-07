#ifndef RESSOURCEDLG_H
#define RESSOURCEDLG_H

#include <QDialog>
#include "c_init_bd.h"
namespace Ui {
class RessourceDlg;
}

class RessourceDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RessourceDlg(QWidget *parent = 0,QString id="");
    ~RessourceDlg();

private slots:
    void on_pushButton_submit_clicked();
    void EnableWidgt(QString);

    void on_pushButton_cancel_clicked();

private:
    Ui::RessourceDlg *ui;
    QString modifierID;
    void setInfo(QString id);
};

#endif // RESSOURCEDLG_H
