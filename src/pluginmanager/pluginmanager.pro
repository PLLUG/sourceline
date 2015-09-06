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

include($$PWD/../general.pri)
DESTDIR = $$SL_LIB_DIRECTORY
TARGET = pluginmanager

TEMPLATE = lib

DEFINES += PLUGINMANAGER_LIBRARY

SOURCES += pluginmodel.cpp \
    plugininfo.cpp \
    pluginloader.cpp \
    pluginmanager.cpp

HEADERS += pluginmodel.h\
        pluginmanager_global.h \
    plugininfo.h \
    pluginloader.h \
    pluginmanager.h

include(./../extensionlib/extensionlib.pri)

# Copy headers and pri file
COPYFILES_PATH = $$_PRO_FILE_PWD_
COPYFILES_FILELIST = $$HEADERS
COPYFILES_TARGET_DIR = $$SL_INCLUDE_PLUGINAPI_DIRECTORY/private/$$TARGET
include($$_PRO_FILE_PWD_/../copyfiles.pri)

# TODO: make separate pri file for including this library into project
OTHER_FILES += \
    pluginmanager.pri
