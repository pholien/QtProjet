#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <QStatusBar>
#include <QLabel>
#include <QProgressBar>
#include "c_init_bd.h"
#include "addpatient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionPatient_triggered();

    void on_actionPersonnelSoin_triggered();

    void on_actionQuitter_triggered();

    void on_actionA_propos_triggered();

    void on_btn_search_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
