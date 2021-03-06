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
    commandmanager.cpp \
    publiccommandapi.cpp \
    clientprocess.cpp

HEADERS  += mainwindow.h \
    testcommand.h \
    commandmanager.h \
    publiccommandapi.h \
    clientprocess.h

FORMS    += mainwindow.ui

# Extension support library
include(./../../extensionlib/extensionlib.pri)

# Plugin management support library
include(./../../pluginmanager/pluginmanager.pri)

include($$_PRO_FILE_PWD_/../../app/components/file_view/FileView.pri)

LIBS += -lslapi
