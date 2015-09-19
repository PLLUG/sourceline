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
TARGET = SourceLine

include($$PWD/../general.pri)
DESTDIR = $$SL_BIN_DIRECTORY

QT += widgets

include($$PWD/slbase/slbase.pri)
include($$PWD/components/console/console.pri)
include($$PWD/components/example_component/example_component.pri)
include($$PWD/components/file_view/FileView.pri)
include($$PWD/components/revision_tree/revision_tree.pri)

INCLUDEPATH += $$_PRO_FILE_PWD_

# Main
HEADERS += \
    applicationbuilder.h \
    progresshandler.h \
    ui/passworddialog.h \
    ui/clonedialog.h \
    ui/tabsapi.h \
    ui/genericcomponent.h \
    workplace.h \
    transitionsignals.h \
    ui/errordialog.h \
    ui/contentfortab.h \
    ui/revisiontreedock.h \
    slapi_global.h

SOURCES += \
    main.cpp \
    applicationbuilder.cpp \
    progresshandler.cpp \
    ui/passworddialog.cpp \
    ui/clonedialog.cpp \
    ui/tabsapi.cpp \
    ui/genericcomponent.cpp \
    workplace.cpp \
    ui/errordialog.cpp \
    ui/contentfortab.cpp \
    ui/revisiontreedock.cpp

# Application UI
HEADERS += \
    ui/splashscreen.h \
    ui/customtabbar.h \
    ui/docktitlebar.h \
    ui/editorview.h \
    ui/genericdockwidget.h \
    ui/guidefs.h \
    ui/mainwindow.h \
    ui/appsettingsdialog.h \
    ui/viewsettingpage.h \
    ui/dialogplugins.h \
    ui/actionmanager.h \
    ui/mainmenubuilder.h \
    ui/dockfileview.h \
    ui/dockconsole.h \
    ui/about.h \
    ui/plugininfodialog.h \
    ui/useraction.h \
    ui/strategies/sortingstrategy.h \
    ui/strategies/directordersortingstrategy.h

SOURCES += \
    ui/splashscreen.cpp \
    ui/customtabbar.cpp \
    ui/editorview.cpp \
    ui/genericdockwidget.cpp \
    ui/mainwindow.cpp \
    ui/appsettingsdialog.cpp \
    ui/viewsettingpage.cpp \
    ui/dialogplugins.cpp \
    ui/actionmanager.cpp \
    ui/mainmenubuilder.cpp \
    ui/about.cpp \
    ui/plugininfodialog.cpp \
    ui/useraction.cpp \
    ui/dockconsole.cpp \
    ui/dockfileview.cpp \
    ui/strategies/directordersortingstrategy.cpp \
    ui/strategies/sortingstrategy.cpp

FORMS += \
    ui/customtabbar.ui \
    ui/editorview.ui \
    ui/files.ui \
    ui/mainwindow.ui \
    ui/appsettingsdialog.ui \
    ui/viewsettingpage.ui \
    ui/dialogplugins.ui \
    ui/dockfileview.ui \
    ui/about.ui \
    ui/plugininfodialog.ui \
    ui/dockconsole.ui \
    ui/passworddialog.ui \
    ui/clonedialog.ui \
    ui/errordialog.ui \
    ui/contentfortab.ui \
    ui/revisiontreedock.ui

# Application Settings
HEADERS += \
    settings_dialog/settingstorage.h \
    settings_dialog/settingsmanager.h

SOURCES += \
    settings_dialog/settingstorage.cpp \
    settings_dialog/settingsmanager.cpp

# Plugins Support
HEADERS += \
    pluginsupport/componentsorter.h \
    pluginsupport/supliers/componentsupplier.h \
    pluginsupport/supliers/fakecomponentsupplier.h \
    pluginsupport/pluginsettingsmediator.h \
    pluginsupport/supliers/commandcomponentsupplier.h \
    pluginsupport/supliers/settingspagesupplier.h

SOURCES += \
    pluginsupport/componentsorter.cpp \
    pluginsupport/supliers/fakecomponentsupplier.cpp \
    pluginsupport/pluginsettingsmediator.cpp \
    pluginsupport/supliers/settingspagesupplier.cpp \
    pluginsupport/supliers/commandcomponentsupplier.cpp

# Extension support library
include(./../extensionlib/extensionlib.pri)

# Plugin management library
include(./../pluginmanager/pluginmanager.pri)

# Resources and additional files
RESOURCES += \
    resources/resources.qrc

RC_FILE += \
    resources/appicon.rc

OTHER_FILES +=




