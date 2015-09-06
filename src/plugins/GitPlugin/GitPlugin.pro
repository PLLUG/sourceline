
TEMPLATE = lib
TARGET = GitPlugin

include($$PWD/../../general.pri)

DESTDIR = $$SL_PLUGINS_DIRECTORY

QT      += gui widgets
CONFIG  += shared

DEFINES += GITPLUGIN_LIBRARY

include(../../extensionlib/extensionlib.pri)

DISTFILES += \
    GitPlugin.json

HEADERS += \
    gitplugin_global.h \
    gitplugin.h \
    gitsettings.h \
#    clonecommand.h \
    commandapi.h

SOURCES += \
    gitplugin.cpp \
    gitsettings.cpp \
#    clonecommand.cpp \
    commandapi.cpp
