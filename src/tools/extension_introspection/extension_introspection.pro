#-------------------------------------------------
#
# Project created by QtCreator 2015-08-24T15:37:45
#
#-------------------------------------------------

TEMPLATE = app
TARGET = extension_introspection

include(./../../general.pri)
DESTDIR = $$SL_BIN_DIRECTORY

QT      += core gui
QT      += widgets

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
    file_view/fileview.cpp \
    clonecommand.cpp \
    clientprocess.cpp

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
    file_view/fileview.h \
    clonecommand.h \
    clientprocess.h

FORMS    += mainwindow.ui \
    file_view/ui/fileview.ui

# Extension support library
include(./../../extensionlib/extensionlib.pri)

# Plugin management support library
include(./../../pluginmanager/pluginmanager.pri)
