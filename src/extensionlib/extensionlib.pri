# Extension support library

CONFIG(sl_project) {
    INCLUDEPATH += $$SL_INCLUDE_PLUGINAPI_DIRECTORY/private/extensions
    unix|win32: LIBS += -L$$SL_LIB_DIRECTORY
}# else {
#    INCLUDEPATH += $$PWD/include/
#    unix|win32: LIBS += -L$$PWD/lib/
#}

LIBS += -lextensions



