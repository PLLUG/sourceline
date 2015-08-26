#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T15:37:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
DESTDIR = $$_PRO_FILE_PWD_/../../../bin

CONFIG += C++11
CONFIG += sl_project

TARGET = extension_introspection
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    testcommand.cpp

HEADERS  += mainwindow.h \
    testcommand.h

FORMS    += mainwindow.ui

# Extension support library
include(./../../extensionlib/extensionlib.pri)

# Plugin management support library
include(./../../pluginmanager/pluginmanager.pri)
