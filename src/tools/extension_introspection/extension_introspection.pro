#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T15:37:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DESTDIR = $$_PRO_FILE_PWD_/../../bin

# Extension support library
include(./../../extensionlib/extensionlib.pri)

CONFIG += C++11

TARGET = extension_introspection
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
