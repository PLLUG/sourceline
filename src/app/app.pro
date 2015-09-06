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
DESTDIR = $$SL_LIB_DIRECTORY

QT += widgets

include($$PWD/apibase/apibase.pri)
include($$PWD/components/console/console.pri)
include($$PWD/components/example_component/example_component.pri)
include($$PWD/components/file_view/FileView.pri)

INCLUDEPATH += $$_PRO_FILE_PWD_

# Main
HEADERS += \
    applicationbuilder.h \
    progresshandler.h \
    ui/revisionview.h \
    ui/revisionView/branch.h \
    ui/revisionView/createtree.h \
    ui/revisionView/creator.h \
    ui/revisionView/graphfield.h \
    ui/revisionView/node.h \
    ui/revisionView/parameters.h \
    ui/revisionView/revisionitem.h \
    ui/revisionView/revisionnode.h \
    ui/revisionView/revisiontablemodel.h \
    ui/revisionView/view/abstractgraphicsview.h \
    ui/revisionView/view/abstractrevisiondelegate.h \
    ui/revisionView/view/bubble.h \
    ui/revisionView/view/graphicsview.h \
    ui/revisionView/view/modelindex.h \
    ui/revisionView/view/revisiongrid.h \
    ui/revisionView/view/revisionnodeitem.h \
    ui/revisionView/view/simpleline.h \
    ui/clonedialog.h \
    ui/tabsapi.h \
    ui/genericcomponent.h \
    workplace.h \
    transitionsignals.h \
    ui/errordialog.h \
    ui/contentfortab.h \
    slapi_global.h

SOURCES += \
    main.cpp \
    applicationbuilder.cpp \
    progresshandler.cpp \
    ui/revisionview.cpp \
    ui/revisionView/branch.cpp \
    ui/revisionView/createtree.cpp \
    ui/revisionView/creator.cpp \
    ui/revisionView/graphfield.cpp \
    ui/revisionView/node.cpp \
    ui/revisionView/revisionitem.cpp \
    ui/revisionView/revisionnode.cpp \
    ui/revisionView/revisiontablemodel.cpp \
    ui/revisionView/view/abstractgraphicsview.cpp \
    ui/revisionView/view/abstractrevisiondelegate.cpp \
    ui/revisionView/view/bubble.cpp \
    ui/revisionView/view/graphicsview.cpp \
    ui/revisionView/view/modelindex.cpp \
    ui/revisionView/view/revisiongrid.cpp \
    ui/revisionView/view/revisionnodeitem.cpp \
    ui/revisionView/view/simpleline.cpp \
    ui/clonedialog.cpp \
    ui/tabsapi.cpp \
    ui/genericcomponent.cpp \
    workplace.cpp \
    ui/errordialog.cpp \
    ui/contentfortab.cpp

# Application UI
HEADERS += \
    ui/splashscreen.h \
    ui/customtabbar.h \
    ui/docktitlebar.h \
    ui/editorview.h \
    ui/genericdockwidget.h \
    ui/guidefs.h \
    ui/historytree.h \
    ui/mainwindow.h \
    ui/revisiontable.h \
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
    ui/historytree.cpp \
    ui/mainwindow.cpp \
    ui/revisiontable.cpp \
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
    ui/historytree.ui \
    ui/mainwindow.ui \
    ui/revisiontable.ui \
    ui/appsettingsdialog.ui \
    ui/viewsettingpage.ui \
    ui/dialogplugins.ui \
    ui/dockconsole.ui \
    ui/dockfileview.ui \
    ui/about.ui \
    ui/plugininfodialog.ui \
    ui/revisionview.ui \
    ui/clonedialog.ui \
    ui/errordialog.ui \
    ui/contentfortab.ui

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

SOURCES +=
HEADERS +=

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

SUBDIRS += \
    ui/revisionView/revTree.pro


