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
    settings_dialog/settingstorage.cpp \
    ui/viewsettingpage.cpp \
    pluginsupport/componentsorter.cpp \
    settings_dialog/settingsmanager.cpp \
    pluginsupport/supliers/fakecomponentsupplier.cpp \
    pluginsupport/plugininfo.cpp \
    pluginsupport/pluginloader.cpp \
    pluginsupport/pluginmanager.cpp \
    pluginsupport/pluginsettingsmediator.cpp \
    ui/dialogplugins.cpp \
    ui/actionmanager.cpp \
    ui/mainmenubuilder.cpp \
<<<<<<< HEAD
    ui/about.cpp \
    ui/plugininfodialog.cpp
=======
    pluginsupport/supliers/settingspagesupplier.cpp
>>>>>>> 5fc0fb66e5823402fc10bac1a8c8ea7cc56e7da5

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
    settings_dialog/settingstorage.h \
    ui/viewsettingpage.h \
    pluginsupport/componentsorter.h \
    pluginsupport/supliers/componentsupplier.h \
    settings_dialog/settingsmanager.h \
    pluginsupport/supliers/fakecomponentsupplier.h \
    pluginsupport/plugininfo.h \
    pluginsupport/pluginloader.h \
    pluginsupport/pluginmanager.h \
    pluginsupport/pluginsettingsmediator.h \
    ui/dialogplugins.h \
    ui/actionmanager.h \
    ui/mainmenubuilder.h \
<<<<<<< HEAD
    ui/about.h \
    ui/plugininfodialog.h
=======
    pluginsupport/supliers/settingspagesupplier.h
>>>>>>> 5fc0fb66e5823402fc10bac1a8c8ea7cc56e7da5

INCLUDEPATH += \
    ./ui \
    ./settings_dialog

INCLUDEPATH += $$PWD/../pluginapi/include/
DEPENDPATH += $$PWD/../pluginapi/include/

unix|win32: LIBS += -L$$PWD/../pluginapi/lib/ -lextensions


RESOURCES += \
    resources/resources.qrc

RC_FILE += \
    resources/appicon.rc

FORMS += \
    ui/console.ui \
    ui/customtabbar.ui \
    ui/editorview.ui \
    ui/files.ui \
    ui/fileview.ui \
    ui/historytree.ui \
    ui/mainwindow.ui \
    ui/revisiontable.ui \
    ui/appsettingsdialog.ui \
    ui/viewsettingpage.ui \
    ui/dialogplugins.ui \
    ui/about.ui \
    ui/plugininfodialog.ui

OTHER_FILES +=

