#-------------------------------------------------
#
# Project created by QtCreator 2014-06-16T01:21:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = revTree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    revisionview.cpp \
    revisionmodel.cpp \
    revisionnode.cpp \
    createtree.cpp \
    view/revisionnodeitem.cpp \
    view/revisiongrid.cpp \
    view/graphicsview.cpp

HEADERS  += mainwindow.h \
    revisionview.h \
    revisionmodel.h \
    revisionnode.h \
    createtree.h \
    view/revisionnodeitem.h \
    view/revisiongrid.h \
    view/graphicsview.h

FORMS    += mainwindow.ui
