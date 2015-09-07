
TEMPLATE = lib
TARGET = GitPlugin

include($$PWD/../../general.pri)

DESTDIR = $$SL_PLUGINS_DIRECTORY

QT      += gui widgets
CONFIG  += shared

DEFINES += GITPLUGIN_LIBRARY

include(../../extensionlib/extensionlib.pri)
LIBS += -lslapi

DISTFILES += \
    GitPlugin.json

HEADERS += \
    gitplugin_global.h \
    gitplugin.h \
    gitsettings.h \
    commandapi.h \
    clonecommand.h

SOURCES += \
    gitplugin.cpp \
    gitsettings.cpp \
    commandapi.cpp \
    clonecommand.cpp

OTHER_FILES += \
    GitPlugin.json
