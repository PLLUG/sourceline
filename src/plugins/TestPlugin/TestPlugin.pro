################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2014                                                    ###
###                   Priyma Yuriy (priymayuriy@gmail.com)                   ###
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
QT       -= gui

TARGET = TestPlugin

TEMPLATE = lib

DESTDIR = $$_PRO_FILE_PWD_/../../../bin/plugins

CONFIG += shared

DEFINES += TESTPLUGIN_LIBRARY

SOURCES += testplugin.cpp \
    gitfakecomponent.cpp

HEADERS += testplugin.h \
    gitfakecomponent.h \
    testplugin_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix|win32: LIBS += -L$$PWD/../../pluginapi/lib/ -lextensions

INCLUDEPATH += $$PWD/../../pluginapi/include
DEPENDPATH += $$PWD/../../pluginapi/include

OTHER_FILES += \
    TestPlugin.json
