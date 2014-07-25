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

QT       -= gui

PLUGINAPI_PATH=$$_PRO_FILE_PWD_/../app/pluginapi

TARGET = extensions
DESTDIR = $$PLUGINAPI_PATH/lib
TEMPLATE = lib

DEFINES += EXTENSIONS_LIBRARY

SOURCES += \
    fakecomponent.cpp \
    plugin.cpp

HEADERS +=\
        extensions_global.h \
    plugin-interface.h \
    fakecomponent.h \
    plugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    COMMAND = copy $$PWD/.qhcp $$DOCUMENTATION_DIR/.qhcp
    copyCollectionProject.commands = $$replace(COMMAND, /, \\)
} else {
    copyCollectionProject.commands = cp $$PWD/.qhcp $$DOCUMENTATION_DIR
}

## === define copy files for installation and build ===

copytarget.path    = $$_PRO_FILE_PWD_
copytarget.files  += \
    $$files(fakecomponent.h) \
    $$files(plugin.h) \
    $$files(plugin-interface.h) \
    $$files(extensions_global.h)
## wildcard for filename1 filename2 filename3 ...

message("found files for copytarget: "$$copytarget.files)

## === os specific dir separator ===

win32: copytarget.files ~= s,/,\\,g


## === copy compiler for makefile ===

DirSep = /
win32: DirSep = \\

for(f,copytarget.files) tmp += $$PWD$$DirSep$${f} ## make absolute paths
copycompiler.input        = tmp

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

