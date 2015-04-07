#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <QStatusBar>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidgetItem>
#include <QPushButton>
#include <QMessageBox>
#include <QList>

#include "c_init_bd.h"
#include "vue_patientdlg.h"
#include "vue_ressourcedlg.h"
#include "vue_aboutdlg.h"

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

    void modifierPatient(QModelIndex);

    void on_pushButton_ModRess_clicked();

    void on_pushButton_SuppRess_clicked();

private:
    Ui::MainWindow *ui;
    void setWidget();
    void afficherRess();
    QString getRessItemId();
};

#endif // MAINWINDOW_H
