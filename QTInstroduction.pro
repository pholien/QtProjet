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
    mainwindow.cpp \
    login.cpp \
    addpatient.cpp \
    c_init_bd.cpp \
    addpersonnelsoin.cpp

HEADERS  += mainwindow.h \
    login.h \
    addpatient.h \
    c_init_bd.h \
    addpersonnelsoin.h

FORMS    += mainwindow.ui \
    login.ui \
    addpatient.ui \
    addpersonnelsoin.ui

RESOURCES += \
    resource.qrc
