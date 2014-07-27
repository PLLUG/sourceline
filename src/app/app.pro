################################################################################
###                                                                          ###
###    SourceLine - Crossplatform VCS Client                                 ###
###    Copyright (C) 2014  by                                                ###
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

TEMPLATE = app
DESTDIR = $$_PRO_FILE_PWD_/../../bin/
QT += widgets

SOURCES += \
    main.cpp \
    applicationbuilder.cpp \
    progresshandler.cpp \
    ui/splashscreen.cpp \
    ui/console.cpp \
    ui/customtabbar.cpp \
    ui/editorview.cpp \
    ui/FileView.cpp \
    ui/genericdockwidget.cpp \
    ui/historytree.cpp \
    ui/mainwindow.cpp \
    ui/pagemanager.cpp \
    ui/revisiontable.cpp \
    ui/appsettingsdialog.cpp \
    settings_dialog/pluginsettings.cpp \
    settings_dialog/settingspage.cpp \
    settings_dialog/settingstorage.cpp \
    ui/viewsettingpage.cpp \
    pluginsupport/componentsorter.cpp \
    settings_dialog/settingsmanager.cpp \
    pluginsupport/supliers/fakecomponentsupplier.cpp

HEADERS += \
    applicationbuilder.h \
    progresshandler.h \
    ui/splashscreen.h \
    ui/console.h \
    ui/customtabbar.h \
    ui/docktitlebar.h \
    ui/editorview.h \
    ui/FileView.h \
    ui/genericdockwidget.h \
    ui/guidefs.h \
    ui/historytree.h \
    ui/mainwindow.h \
    ui/pagemanager.h \
    ui/revisiontable.h \
    ui/appsettingsdialog.h \
    settings_dialog/pluginsettings.h \
    settings_dialog/settingspage.h \
    settings_dialog/settingstorage.h \
    ui/viewsettingpage.h \
    pluginsupport/componentsorter.h \
    pluginsupport/supliers/componentsupplier.h \
    settings_dialog/settingsmanager.h \
    pluginsupport/supliers/fakecomponentsupplier.h

INCLUDEPATH += \
    ./ui \
    ./settings_dialog

RESOURCES += \
    resources/resources.qrc \
    resources/Icon.qrc

FORMS += \
    ui/console.ui \
    ui/customtabbar.ui \
    ui/editorview.ui \
    ui/files.ui \
    ui/fileview.ui \
    ui/historytree.ui \
    ui/mainwindow.ui \
    ui/revisiontable.ui \
    ui/viewsettings.ui \
    ui/appsettingsdialog.ui \
    ui/viewsettingpage.ui
