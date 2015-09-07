################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2015  by                                                ###
###                   Alex Chmykhalo (alexchmykhalo@users.sourceforge.net)   ###
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

TEMPLATE = lib
TARGET = slapi

include($$PWD/../general.pri)
DESTDIR += $$SL_LIB_DIRECTORY
DEFINES += SLAPI_LIBRARY

CONFIG += staticlib

SOURCES += slapifactory.cpp
HEADERS += slapifactory.h

include($$PWD/../app/slapi_includes.pri)
INCLUDEPATH += $$SL_INCLUDE_DIRECTORY/pluginapi/private/extensions
LIBS += -lextensionlib

# Copy headers and pri file
COPYFILES_PATH = $$_PRO_FILE_PWD_
COPYFILES_FILELIST = $$HEADERS
COPYFILES_TARGET_DIR = $$SL_INCLUDE_PLUGINAPI_DIRECTORY
include($$_PRO_FILE_PWD_/../copyfiles.pri)

