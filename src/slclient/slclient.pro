
TEMPLATE = app
TARGET = slclient
DESTDIR = $$_PRO_FILE_PWD_/../../bin

QT       += core

CONFIG   -= app_bundle
CONFIG += sl_project # Pro file is a part of source line project structure
CONFIG += c++11

CONFIG (debug, debug|release) {
    DEFINES += DEBUG # Define that indicates - we are in debug mode

    QT       += gui      # During debug we might need to show helper window (for debugging convenience)
    QT       += widgets
    HEADERS += clientdebugwindow.h
    SOURCES += clientdebugwindow.cpp
} else {
    DEFINES += QT_NO_DEBUG_OUTPUT  # No debug output in release
}

HEADERS += \
    sourcelineclient.h \
    texteditinterface.h

SOURCES += \
    main.cpp \
    sourcelineclient.cpp \
    texteditinterface.cpp

# Extension support library
include(./../extensionlib/extensionlib.pri)

# Plugin management library
include(./../pluginmanager/pluginmanager.pri)

