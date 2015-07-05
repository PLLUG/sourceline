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

#include "applicationbuilder.h"
#include "progresshandler.h"

#include <QTimer>
#include <QApplication>

// Plugin Support
#include <plugin.h>
#include "pluginsupport/componentsorter.h"
#include "pluginsupport/supliers/fakecomponentsupplier.h"
#include "pluginsupport/supliers/settingspagesupplier.h"
#include "pluginsupport/supliers/commandcomponentsupplier.h"
#include "pluginsupport/pluginloader.h"
#include "pluginsupport/pluginmanager.h"
#include "pluginsupport/pluginsettingsmediator.h"

// Settings
#include <settings.h>
#include "settings_dialog/settingstorage.h"
#include "settings_dialog/settingsmanager.h"

// Main Application Classes
#include "ui/actionmanager.h"
#include "ui/mainmenubuilder.h"
#include "ui/useraction.h"
#include "ui/strategies/directordersortingstrategy.h"

// Application UI
#include "ui/splashscreen.h"
#include "ui/dialogplugins.h"
#include "ui/plugininfodialog.h"
#include "ui/mainwindow.h"
#include "ui/about.h"
#include "ui/viewsettingpage.h"
#include "ui/appsettingsdialog.h"
#include "progresshandler.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent)
{
    // Plugin Support
    mPluginManager = 0;

    // Settings
    mStorage = 0;
    mSettingsManager = 0;

    // Main Application Classes
    mActionManager = 0;
    mMainMenuBuilder = 0;
    mPluginSettingsMediator = 0;
    mGlobalAppSettings = 0;

    // Application UI
    mSplashScreen = 0;
    mMainWindow = 0;
    mAppSettingsDialog = 0;
    mAboutDialog = 0;

    // Init splash screen
    mSplashScreen = new SplashScreen; // removed in slotBuild()
    mSplashScreen->setSplashScreen(QPixmap(":/splash/img/SL_Splash_load.png"));
    mSplashScreen->setLoadLayer(QPixmap(":/splash/img/barload_only.png"), 80, 410);
    connect(ProgressHandler::instance(), SIGNAL(progress(int)),
            mSplashScreen, SLOT(slotSetPercentage(int)), Qt::UniqueConnection);
    ProgressHandler::instance()->resetProgress();
    mSplashScreen->show();

    // Schedule application loading
    QTimer::singleShot(1000, this, SLOT(slotBuild()));
}

ApplicationBuilder::~ApplicationBuilder()
{
    delete mMainWindow;
}

void ApplicationBuilder::slotBuild()
{
    qDebug("SourceLine : Building Application");
    ProgressHandler::instance()->setStageCount(5);

    /*!
     * Stage 1: Initialize UI
     */
    qDebug("    Initializing appplicaton ...");
    initApp();

    /*!
     * Stage 2: Initialize UI
     */
    qDebug("    Creating UX...");
    createUi();

    /*!
     * Stage 3: Load Plugins
     */
    qDebug("    Loading plugins...");
    initPlugins();

    /*!
     * Stage 4: Getting components
     */
    qDebug("    Registering components...");
    registerComponents();

    /*!
     * Stage 5: Load Settings
     */
    qDebug("    Loading Settings...");
    loadSettings();

    //TASK: find place for this fuction
    // I take createAppMenus from createUi ,becouse
    //at this stage of the program commands from plugins are not loaded
    // Init application menus
    createAppMenus(); // At this point actions should be created, and all UI initialized

    mMainWindow->show();

    QTimer::singleShot(1500, mSplashScreen, SLOT(deleteLater()));

    qDebug("done");
}

void ApplicationBuilder::initApp()
{
    // Manager for all menu and toolbar actions in application
    mActionManager = new ActionManager(qApp);

    // Mediator for managing plugins configuration by user
    mPluginSettingsMediator = new PluginSettingsMediator(qApp);

    // Settings storage
    mStorage = new SettingStorage(qApp);

    // Settings manager instance
    mSettingsManager = new SettingsManager(qApp);
    mSettingsManager->setStorage(mStorage);

    // Global settings not configurable from settings dialog
    // (loaded plugins, etc...)
    mGlobalAppSettings = new Settings(qApp);
    mGlobalAppSettings->setAutoCommit(true); // Settings have no settings page representation, so
                                             // settings should be commited automatically after change
    mSettingsManager->addSettings("global", "settings", mGlobalAppSettings);

    // TASK: remove setting of global app settings from mediator (fix for settings autocommit needed)
    mPluginSettingsMediator->setSettings(mGlobalAppSettings);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::createUi()
{
    // Application main window
    mMainWindow = new MainWindow;
    mMainWindow->lower();

    // Helper class for building main menu
    mMainMenuBuilder = new MainMenuBuilder(qApp);
    mMainMenuBuilder->setActionManager(mActionManager);
    mMainMenuBuilder->setMenuBar(mMainWindow->menuBar());

    // -= Dialogs
    // Plugin settings
    DialogPlugins *lDialogPlugins = new DialogPlugins(mMainWindow);
    mPluginSettingsMediator->setPluginDialog(lDialogPlugins);

    PluginInfoDialog *lPluginInfoDialog = new PluginInfoDialog(lDialogPlugins);
    mPluginSettingsMediator->setPluginInfoDialog(lPluginInfoDialog);

    // Application settings dialog
    mAppSettingsDialog = new AppSettingsDialog();

    // About dialog
    mAboutDialog = new About(mMainWindow);

    ProgressHandler::instance()->setCurrentStageProgress(33);

    // -= Create User Actions
    createUiActions(mMainWindow);
    ProgressHandler::instance()->setCurrentStageProgress(66);


    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::createUiActions(MainWindow *pMainWindow)
{
    UserAction *lActionOpen = new UserAction(tr("&Open Repository..."), mMainWindow);
    // TASK: add implementation for opening existing repository
    mActionManager->add(FileMenuGroup, lActionOpen);

    // COMMENT: temporary action - create new tab (testing)
    UserAction *lActionAddPage = new UserAction(tr("&Add Page"), this);
    connect(lActionAddPage, SIGNAL(triggered()), pMainWindow, SLOT(slotAddPage()));
    mActionManager->add(FileMenuGroup, lActionAddPage);

    UserAction *lActionQuit = new UserAction(tr("&Quit"), this);
    connect(lActionQuit, SIGNAL(triggered()), pMainWindow, SLOT(slotQuit()));
    mActionManager->add(FileMenuGroup, lActionQuit);

    UserAction *lActionAboutSL = new UserAction(tr("&About SourseLine..."), this);
    connect(lActionAboutSL, SIGNAL(triggered()), mAboutDialog, SLOT(show()), Qt::UniqueConnection);
    mActionManager->add(HelpMenuGroup, lActionAboutSL);

    UserAction *lActionPlugins = new UserAction(tr("&Plugins Settings"), this);
    connect(lActionPlugins, SIGNAL(triggered()), mPluginSettingsMediator, SLOT(slotExecPluginSettings()));
    mActionManager->add(HelpMenuGroup, lActionPlugins);

    UserAction *lActionSettings = new UserAction(tr("&Settings"), this);
    connect(lActionSettings, SIGNAL(triggered()), mAppSettingsDialog, SLOT(show()));
    mActionManager->add(ViewMenuGroup, lActionSettings);
}

void ApplicationBuilder::createAppMenus()
{
    DirectOrderSortingStrategy* lDirectOrderSortingStrategy = new DirectOrderSortingStrategy;

    mActionManager->setMenuCreationStategy(FileMenuGroup, lDirectOrderSortingStrategy);
    mActionManager->setMenuCreationStategy(ViewMenuGroup, lDirectOrderSortingStrategy);
    mActionManager->setMenuCreationStategy(EditMenuGroup, lDirectOrderSortingStrategy);
    mActionManager->setMenuCreationStategy(HelpMenuGroup, lDirectOrderSortingStrategy);
    mMainMenuBuilder->initMenu();
}

void ApplicationBuilder::initPlugins()
{
    // Plugin loading managing classes
    PluginLoader *lPluginLoader = new PluginLoader(qApp);

    mPluginManager = new PluginManager(qApp);
    mPluginManager->setPluginLoader(lPluginLoader);
    mPluginSettingsMediator->setPluginManager(mPluginManager);

    mGlobalAppSettings->add("plugins", mPluginManager, "activePlugins");
    mStorage->slotLoadSettings(mSettingsManager->pathBySettings(mGlobalAppSettings));

    // Load plugins
    loadPlugins();

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadPlugins()
{
    int lLoadedCount = 0;
    QStringList lActivePluginsList = mPluginManager->activePlugins();

    if (lActivePluginsList.isEmpty())
    {
        qDebug("        No plugin settings present: loading all available pluggins");
        lActivePluginsList = mPluginManager->availablePlugins();
    }

    foreach (const QString &lPluginId, lActivePluginsList)
    {
        qDebug("        Loading %s...", qPrintable(lPluginId));
        mPluginManager->loadPlugin(lPluginId);
        ++lLoadedCount;
        ProgressHandler::instance()->setCurrentStageProgress(lLoadedCount * 100 / lActivePluginsList.size());
        QApplication::processEvents();
    }
}

void ApplicationBuilder::registerComponents()
{
    // Sorter object - sort components by categories and register them
    // within suppliers
    ComponentSorter lComponentSorter;

    FakeComponentSupplier lFakeComponentSupplier;
    lComponentSorter.addSupplier(&lFakeComponentSupplier);

    SettingsPageSuplier lSettingsManagerSupliers;
    lSettingsManagerSupliers.setSettingsManager(mSettingsManager);
    lSettingsManagerSupliers.setAppSettingsDialog(mAppSettingsDialog);
    lComponentSorter.addSupplier(&lSettingsManagerSupliers);

    CommandComponentSupplier lCommandComponentSupplier;
    lCommandComponentSupplier.setActionManager(mActionManager);
    lComponentSorter.addSupplier(&lCommandComponentSupplier);

    // Supplying components...
    supplyComponents(&lComponentSorter);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadSettings()
{
    // View settings
    Settings *lViewSettings = new Settings(this);

    ViewSettingPage *lViewSettingPage = new ViewSettingPage(lViewSettings);
    lViewSettingPage->setMainUi(mMainWindow->ui);
    mAppSettingsDialog->addSettingsItem(lViewSettingPage);

    mSettingsManager->addSettings("main_window", lViewSettingPage->name(), lViewSettings);
    mStorage->slotLoadSettings(mSettingsManager->pathBySettings(lViewSettings));

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::supplyComponents(ComponentSorter *pComponentSorter)
{
    int lSuppliedCount = 0;
    QStringList lLoadedPluginsList = mPluginManager->loadedPlugins();
    foreach (const QString &lPluginId, lLoadedPluginsList)
    {
        // Supply componenets to application
        PluginInfo lPluginInfo = mPluginManager->pluginInfo(lPluginId);
        qDebug("        Registering %s %s...", qPrintable(lPluginInfo.pluginId()), qPrintable(lPluginInfo.ver()));
        Plugin *lPlugin = mPluginManager->loadedPluginInstance(lPluginId);
        pComponentSorter->setComponents(lPlugin->components(), lPluginInfo);

        // Update progress
        ++lSuppliedCount;
        ProgressHandler::instance()->setCurrentStageProgress(lSuppliedCount * 100 / lLoadedPluginsList.size());
        QApplication::processEvents();
    }
}


