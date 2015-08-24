# Plugin management library

INCLUDEPATH += $$PWD
unix|win32: LIBS += -L$$PWD/../../bin

LIBS += -lpluginmanager
