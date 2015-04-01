#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T17:28:13
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TRANSLATIONS += calendar_ru.ts
TRANSLATIONS += calendar_eng.ts
TARGET = Calendar
TEMPLATE = app
CONFIG += console
CONFIG += debug

SOURCES += main.cpp\
        mainwindow.cpp \
    adddatadialog.cpp \
    helpdialog.cpp \
    settingdialog.cpp \
    textconfiguratulatiodialog.cpp \
    dbmanager.cpp \
    notificationdialog.cpp

HEADERS  += mainwindow.h \
    adddatadialog.h \
    helpdialog.h \
    settingdialog.h \
    textconfiguratulatiodialog.h \
    dbmanager.h \
    notificationdialog.h

FORMS    += mainwindow.ui \
    adddatadialog.ui \
    helpdialog.ui \
    settingdialog.ui \
    textconfiguratulatiodialog.ui \
    notificationdialog.ui
