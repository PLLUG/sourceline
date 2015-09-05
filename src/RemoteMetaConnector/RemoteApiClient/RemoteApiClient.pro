#-------------------------------------------------
#
# Project created by QtCreator 2015-08-29T21:31:42
#
#-------------------------------------------------

QT       += core network
QT       -= gui

CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteApiClient
TEMPLATE = app


SOURCES += main.cpp\
    texteditinterface.cpp \
    remoteapiclient.cpp

HEADERS  +=texteditinterface.h \
    remoteapiclient.h

include(../metaconnector/metaconnector.pri)
