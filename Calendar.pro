#-------------------------------------------------
#
# Project created by QtCreator 2015-03-23T17:28:13
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
TRANSLATIONS += calendar_ru.ts
TRANSLATIONS += calendar_eng.ts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



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
    notificationdialog.cpp \
    smtp.cpp \
    emailsenddialog.cpp

HEADERS  += mainwindow.h \
    adddatadialog.h \
    helpdialog.h \
    settingdialog.h \
    textconfiguratulatiodialog.h \
    dbmanager.h \
    notificationdialog.h \
    smtp.h \
    emailsenddialog.h

FORMS    += mainwindow.ui \
    adddatadialog.ui \
    helpdialog.ui \
    settingdialog.ui \
    textconfiguratulatiodialog.ui \
    notificationdialog.ui \
    emailsenddialog.ui
