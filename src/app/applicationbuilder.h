#ifndef APPLICATIONBUILDER_H
#define APPLICATIONBUILDER_H

/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Alex Chmykhalo (alexchmykhalo@users.sourceforge.net)          ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#include <QObject>

// Settings
class SettingsManager;
class SettingStorage;
class Settings;

// Plugin Support
class PluginManager;
class Plugin;
class ComponentSorter;

// Main Application Classes
class ActionManager;
class MainMenuBuilder;
class PluginSettingsMediator;

// Application UI
class SplashScreen;
class MainWindow;
class AppSettingsDialog;
class About;

#include "progresshandler.h"

/*!
 * \brief The ApplicationBuilder class resporsible for creation of all objects in application
 *  and putting all application building blocks together.
 */
class ApplicationBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationBuilder(QObject *parent = 0);
    virtual ~ApplicationBuilder();

private slots:
    /*!
     * \brief Runs all application loading stages in prefefined order.
     */
    void slotBuild();

// Loading Stages
/*!
 * Building of application is separated on few loading stages. Eveery stage is necessasy for application work.
 * Each stage performs number of actions to acomplish specific initialization tasks, calls additional initialization
 * methods and reports loading progress.
 */
private:
    /*!
     * \brief Application loading stage. Create instances for main application classes.
     */
    void initApp();

    /*!
     * \brief Application loading stage. Initialization of all main UI classes.
     */
    void createUi();

    /*!
     * \brief Application loading stage. Loading, registering and initializing plugins.
     */
    void initPlugins();

    /*!
     * \brief Application loading stage. Registering components supplied from plugins.
     */
    void registerComponents();

    /*!
     * \brief Application loading stage. Load application and plugin settings. Configuring application.
     */
    void loadSettings();

// App creation helper methods
private:
    void loadPlugins();
    void supplyComponents(ComponentSorter *pComponentSorter);
    void createUiActions(MainWindow *pMainWindow);
    void createAppMenus();

// Plugin Support
private:
    PluginManager *mPluginManager;
    QList< Plugin* > mLoadedPlugins;

// Settings
private:
    SettingStorage *mStorage;
    SettingsManager *mSettingsManager;

// Main Application Classes
private:
    ActionManager *mActionManager;
    MainMenuBuilder *mMainMenuBuilder;
    PluginSettingsMediator *mPluginSettingsMediator;
    Settings *mGlobalAppSettings;

// Application UI
private:
    SplashScreen *mSplashScreen;
    MainWindow *mMainWindow;
    AppSettingsDialog *mAppSettingsDialog;
    About *mAboutDialog;
};

#endif // APPLICATIONBUILDER_H
