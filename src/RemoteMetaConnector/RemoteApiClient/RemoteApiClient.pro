#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T21:31:42
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteApiClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    texteditinterface.cpp \
    remoteapiclient.cpp

HEADERS  += mainwindow.h \
    texteditinterface.h \
    remoteapiclient.h

FORMS    += mainwindow.ui

include(../metaconnector/metaconnector.pri)
