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
    dbexception.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    dbfacade.h \
    dbexception.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui
