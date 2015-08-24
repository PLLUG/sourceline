################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2014  by                                                ###
###                   Alex Chmykhalo (alex18cas@gmail.com)                   ###
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

DESTDIR = $$_PRO_FILE_PWD_/../../bin
TARGET = pluginmanager

TEMPLATE = lib
CONFIG += C++11

DEFINES += PLUGINMANAGER_LIBRARY

SOURCES += pluginmodel.cpp

HEADERS += pluginmodel.h\
        pluginmanager_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

# TODO: make separate pri file for including this library into project
#OTHER_FILES += \
#    extensionlib.pri
