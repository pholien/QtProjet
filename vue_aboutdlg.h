#ifndef VUE_ABOUTDLG_H
#define VUE_ABOUTDLG_H

#include <QDialog>

namespace Ui {
class AboutDlg;
}

class AboutDlg : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDlg(QWidget *parent = 0);
    ~AboutDlg();

private:
    Ui::AboutDlg *ui;
};

#endif // VUE_ABOUTDLG_H
