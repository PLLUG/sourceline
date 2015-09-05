
TEMPLATE = app
TARGET = slclient
DESTDIR = $$_PRO_FILE_PWD_/../../bin

QT       += core
QT       -= gui

CONFIG   -= app_bundle
CONFIG += sl_project # Pro file is a part of source line project structure
CONFIG += c++11

SOURCES += \
    main.cpp

# Extension support library
include(./../extensionlib/extensionlib.pri)

# Plugin management library
include(./../pluginmanager/pluginmanager.pri)
