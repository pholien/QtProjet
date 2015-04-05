#ifndef PROPRE_H
#define PROPRE_H

#include <QDialog>

namespace Ui {
class Propre;
}

class Propre : public QDialog
{
    Q_OBJECT

public:
    explicit Propre(QWidget *parent = 0);
    ~Propre();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Propre *ui;
};

#endif // PROPRE_H
