#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T10:47:53
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTInstroduction
TEMPLATE = app


SOURCES += main.cpp\
    c_init_bd.cpp \
    modele_patient.cpp \
    modele_ressource.cpp \
    controleur_ressource.cpp \
    controleur_patient.cpp \
    vue_mainwindow.cpp \
    vue_patientdlg.cpp \
    vue_logindlg.cpp \
    vue_ressourcedlg.cpp \
    controleur_login.cpp \
    vue_aboutdlg.cpp

HEADERS  += \
    c_init_bd.h \
    modele_patient.h \
    modele_ressource.h \
    controleur_ressource.h \
    controleur_patient.h \
    vue_mainwindow.h \
    vue_patientdlg.h \
    vue_logindlg.h \
    vue_ressourcedlg.h \
    controleur_login.h \
    vue_aboutdlg.h

FORMS    += \
    patientdlg.ui \
    logindlg.ui \
    mainwindowdlg.ui \
    ressourcedlg.ui \
    aboutdlg.ui

RESOURCES += \
    resource.qrc
