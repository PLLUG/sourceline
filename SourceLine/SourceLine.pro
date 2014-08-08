#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T18:08:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SourceLine
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    console.cpp \
    fileview.cpp \
    viewsettings.cpp \
    editorview.cpp \
    historytree.cpp \
    revisiontable.cpp \
    genericdockwidget.cpp \
    pagemanager.cpp \
    customtabbar.cpp

HEADERS  += mainwindow.h \
    console.h \
    genericdockwidget.h \
    guidefs.h \
    fileview.h \
    viewsettings.h \
    editorview.h \
    historytree.h \
    revisiontable.h \
    docktitlebar.h \
    pagemanager.h \
    customtabbar.h

FORMS    += mainwindow.ui \
    console.ui \
    fileview.ui \
    viewsettings.ui \
    editorview.ui \
    historytree.ui \
    revisiontable.ui \
    customtabbar.ui
RESOURCES += \
    Icon.qrc

OTHER_FILES +=

ICON = Icons/SourceLine.icns
