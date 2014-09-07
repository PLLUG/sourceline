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
    revisionnode.cpp \
    createtree.cpp \
    view/revisionnodeitem.cpp \
    view/revisiongrid.cpp \
    view/graphicsview.cpp \
    revisiontablemodel.cpp \
    view/simpleline.cpp \
    view/modelindex.cpp \
    view/abstractgraphicsview.cpp \
    view/abstractrevisiondelegate.cpp \
    view/bubble.cpp \
    revisionwidget.cpp \
    revisiontree.cpp \
    graphfield.cpp \
    node.cpp \
    revisionitem.cpp \
    branch.cpp \
    creator.cpp

HEADERS  += mainwindow.h \
    revisionnode.h \
    createtree.h \
    view/revisionnodeitem.h \
    view/revisiongrid.h \
    view/graphicsview.h \
    revisiontablemodel.h \
    view/simpleline.h \
    view/modelindex.h \
    view/abstractgraphicsview.h \
    view/abstractrevisiondelegate.h \
    view/bubble.h \
    revisionwidget.h \
    revisiontree.h \
    graphfield.h \
    node.h \
    revisionitem.h \
    branch.h \
    creator.h

FORMS    += mainwindow.ui \
    revisionwidget.ui

#INCLUDEPATH += "../../../boost_1_55_0/"
