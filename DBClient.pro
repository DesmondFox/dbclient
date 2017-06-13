#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T09:17:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DBClient
TEMPLATE = app
CONFIG += c++11
#QMAKE_CXXFLAGS_DEBUG += -j4

SOURCES += main.cpp\
        mainwindow.cpp \
    dbfacade.cpp \
    logindialog.cpp \
    maintablewidget.cpp \
    mtablemodel.cpp \
    addnewbuilddialog.cpp

HEADERS  += mainwindow.h \
    dbfacade.h \
    logindialog.h \
    maintablewidget.h \
    mtablemodel.h \
    addnewbuilddialog.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    maintablewidget.ui \
    addnewbuilddialog.ui
