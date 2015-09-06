################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2014  by                                                ###
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
QT       += gui
QT       += widgets
QT       += network

include($$PWD/../general.pri)

PLUGINAPI_PATH=$$SL_INCLUDE_PLUGINAPI_DIRECTORY

TARGET = extensions
DESTDIR = $$SL_LIB_DIRECTORY
TEMPLATE = lib

#CONFIG += \
#    c++11

DEFINES += EXTENSIONS_LIBRARY

include($$_PRO_FILE_PWD_/metaconnector/metaconnector.pri)

SOURCES += \
    $$PWD/fakecomponent.cpp \
    $$PWD/plugin.cpp \
    $$PWD/settingspage.cpp \
    $$PWD/command.cpp \
    $$PWD/settings.cpp

HEADERS +=\
    $$PWD/extensions_global.h\
    $$PWD/fakecomponent.h\
    $$PWD/plugin-interface.h\
    $$PWD/plugin.h\
    $$PWD/settingspage.h \
    $$PWD/command.h \
    $$PWD/defs.h \
    $$PWD/settings.h

# Copy headers and pri file
COPYFILES_PATH = $$_PRO_FILE_PWD_
COPYFILES_FILELIST = $$HEADERS
COPYFILES_TARGET_DIR = $$SL_INCLUDE_PLUGINAPI_DIRECTORY/private/$$TARGET
include($$_PRO_FILE_PWD_/../copyfiles.pri)

OTHER_FILES += \
    extensionlib.pri
