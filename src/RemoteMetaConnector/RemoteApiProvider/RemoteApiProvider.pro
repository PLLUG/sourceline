#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T21:31:01
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteApiProvider
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    remoteapiprovider.cpp

HEADERS  += mainwindow.h \
    remoteapiprovider.h

FORMS    += mainwindow.ui

include(../metaconnector/metaconnector.pri)
