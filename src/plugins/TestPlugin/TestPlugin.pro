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

TARGET = TestPlugin
TEMPLATE = lib

include($$PWD/../../general.pri)
DESTDIR = $$SL_PLUGINS_DIRECTORY

QT       += gui widgets
CONFIG += shared

DEFINES += TESTPLUGIN_LIBRARY

SOURCES += testplugin.cpp \
    customsettingpage.cpp \
    fakecommand.cpp

HEADERS += testplugin.h \
    testplugin_global.h \
    customsettingpage.h \
    fakecommand.h

include(../../extensionlib/extensionlib.pri)
LIBS += -lslapi

OTHER_FILES += \
    TestPlugin.json
