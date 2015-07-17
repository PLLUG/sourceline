QT       += gui widgets

TARGET = GitPlugin

TEMPLATE = lib

DESTDIR = $$_PRO_FILE_PWD_/../../../bin/plugins

CONFIG += shared

# Pro file is a part of source line project structure
CONFIG += sl_project

DEFINES += GITPLUGIN_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}

include(../../extensionlib/extensionlib.pri)

unix|win32: LIBS += -L$$PWD/../../pluginapi/lib/ -lextensions

INCLUDEPATH += $$PWD/../../pluginapi/include
DEPENDPATH += $$PWD/../../pluginapi/include

DISTFILES += \
    GitPlugin.json

HEADERS += \
    gitplugin_global.h \
    gitplugin.h \
    gitsettings.h

SOURCES += \
    gitplugin.cpp \
    gitsettings.cpp
