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

PLUGINAPI_PATH=$$_PRO_FILE_PWD_/../pluginapi

TARGET = extensions
DESTDIR = $$PLUGINAPI_PATH/lib
TEMPLATE = lib

CONFIG += \
    C++11

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

#TODO: add copying of pri file

## === define copy files for installation and build ===
copytarget.path    = $$_PRO_FILE_PWD_
copytarget.files  += $$HEADERS

## wildcard for filename1 filename2 filename3 ...
## === os specific dir separator ===
win32: copytarget.files ~= s,/,\\,g

## === copy compiler for makefile ===
DirSep = /
win32: DirSep = \\

# TODO: move to separate function
#for(f,copytarget.files) {
#    if ()
#    tmp += $$PWD$$DirSep$${f} ## make absolute paths
#}
#copycompiler.input        = tmp
copycompiler.input        = copytarget.files

# TODO: move to separate pri file (to make more re usable)
isEmpty(DESTDIR):DESTDIR=.
PLUGINAPI_INCLUDE_PATH = $$PLUGINAPI_PATH/include
win32 {
    PLUGINAPI_INCLUDE_PATH = $$replace(PLUGINAPI_INCLUDE_PATH, /, \\)
}
copycompiler.output       = $$PLUGINAPI_INCLUDE_PATH$$DirSep${QMAKE_FILE_BASE}${QMAKE_FILE_EXT}
copycompiler.commands     = $(COPY_FILE) ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
copycompiler.CONFIG       = no_link no_clean
## other CONFIG options are: depends explicit_dependencies target_predeps

copycompiler.variable_out = QMAKE_DISTCLEAN
QMAKE_EXTRA_COMPILERS += copycompiler

## == makefile copy target ===
copyfiles.recurse_target = compiler_copycompiler_make_all
copyfiles.depends        = $$copyfiles.recurse_target
copyfiles.CONFIG        += recursive

QMAKE_EXTRA_TARGETS += copyfiles
PRE_TARGETDEPS     += copyfiles ## copy files after source compilation

INSTALLS += copytarget

OTHER_FILES += \
    extensionlib.pri
