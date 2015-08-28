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
    testcommand.cpp \
    pluginapi.cpp \
    commandmanager.cpp \
    publiccommandapi.cpp \    
    aggregator.cpp \
    fileviewapi.cpp \
    publicfileviewapi.cpp \
    file_view/ui/exploreritemdelegate.cpp \
    file_view/ui/texteditforrename.cpp \
    file_view/filemodel.cpp \
    file_view/fileview.cpp

HEADERS  += mainwindow.h \
    testcommand.h \
    pluginapi.h \
    commandmanager.h \
    publiccommandapi.h \    
    aggregator.h \
    fileviewapi.h \
    publicfileviewapi.h \
    file_view/ui/exploreritemdelegate.h \
    file_view/ui/texteditforrename.h \
    file_view/filemodel.h \
    file_view/fileview.h

FORMS    += mainwindow.ui \
    file_view/ui/fileview.ui

# Extension support library
include(./../../extensionlib/extensionlib.pri)

# Plugin management support library
include(./../../pluginmanager/pluginmanager.pri)
