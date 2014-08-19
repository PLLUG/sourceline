# Extension support library
INCLUDEPATH += $$_PRO_FILE_PWD_/../pluginapi/include/
DEPENDPATH += $$_PRO_FILE_PWD_/../pluginapi/include/
unix|win32: LIBS += -L$$_PRO_FILE_PWD_/../pluginapi/lib/ -lextensions


DEFINES += VERSION_MAJOR=1
DEFINES += VERSION_MINOR=0
