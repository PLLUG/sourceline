################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2015  by                                                ###
###                   Halyna Butovych (galynabutovych@gmail.com)             ###
###                                                                          ###
###    This file is part of SourceLine Project.                              ###
###                                                                          ###
###    SourceLine is free software: you can redistribute it and/or modify    ###
###    it under the terms of the GNU General Public License as published by  ###
###    the Free Software Foundation, either version 3 of the License, or     ###
###    (at your option) any later version.                                   ###
###                                                                          ###
###    SourceLine is distributed in the hope that it will be useful,         ###
###    but WITHOUT ANY WARRANTY; without even the implied warranty of        ###
###    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ###
###    GNU General Public License for more details.                          ###
###                                                                          ###
###    You should have received a copy of the GNU General Public License     ###
###    along with this program.  If not, see <http://www.gnu.org/licenses/>. ###
###                                                                          ###
################################################################################
QT       += core gui

CONFIG += c++14
#QMAKE_CXXFLAGS += -std=c++14 -std=gnu++14
#QMAKE_CXXFLAGS_CXX11 = -std=gnu++14
QMAKE_CXXFLAGS += -std=c++14 -std=gnu++14
QMAKE_CXXFLAGS_CXX11 = -std=gnu++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = revision_tree
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    revisiontree.cpp \
    revisionmodel.cpp \
    revisiontreewidget.cpp

HEADERS  += mainwindow.h \
    revisiontree.h \
    revisionmodel.h \
    revisionnode.h \
    revisiontreewidget.h

FORMS    += mainwindow.ui \
    revisiontree.ui
