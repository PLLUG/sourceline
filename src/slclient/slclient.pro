#-------------------------------------------------
#
# Project created by QtCreator 2015-08-31T15:39:17
#
#-------------------------------------------------

# Pro file is a part of source line project structure
CONFIG += \
    sl_project \
    C++11 \

# Extension support library
include(./../extensionlib/extensionlib.pri)

# Plugin management library
include(./../pluginmanager/pluginmanager.pri)

QT       += core

QT       -= gui


DESTDIR = $$_PRO_FILE_PWD_/../../bin
TARGET = slclient
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp
