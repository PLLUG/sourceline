# Extension support library

CONFIG(sl_project) {
    INCLUDEPATH += $$PWD/../pluginapi/include/
    unix|win32: LIBS += -L$$PWD/../pluginapi/lib/
} else {
    INCLUDEPATH += $$PWD/include/
    unix|win32: LIBS += -L$$PWD/lib/
}

LIBS += -lextensions

