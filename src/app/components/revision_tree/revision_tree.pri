################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2015  by                                                ###
###                   Nazarii Plebanskii (nazar796@gmail.com)                ###
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


SOURCES += \
    $$PWD/revisiontree.cpp \
    $$PWD/revisionmodel.cpp \
    $$PWD/revisiontreewidget.cpp \
    $$PWD/revisiontreeapi.cpp

HEADERS  += \
    $$PWD/revisiontree.h \
    $$PWD/revisionmodel.h \
    $$PWD/revisiontreewidget.h \
    $$PWD/revisionvertex.h \
    $$PWD/bfs_visitor.h \
    $$PWD/dfs_visitor.h \
    $$PWD/revisiontreeapiinterface.h \
    $$PWD/revisiontreeapi.h

FORMS    += \
    $$PWD/revisiontree.ui

include($$PWD/revisiontreeapi.pri)

INCLUDEPATH += $$PWD

INCLUDEPATH += $$_PRO_FILE_PWD_/3rdparty/boost \
    
