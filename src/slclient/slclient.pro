
TEMPLATE = app
TARGET = slclient

include($$PWD/../general.pri)
DESTDIR = $$SL_BIN_DIRECTORY

QT       += core
CONFIG   -= app_bundle

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

LIBS  += -lslapi

