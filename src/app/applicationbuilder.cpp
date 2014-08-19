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

#include <QTimer>

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

// Main Application Classes
#include "ui/actionmanager.h"
#include "ui/mainmenubuilder.h"
#include "ui/useraction.h"
#include "ui/strategies/directordersortingstrategy.h"

// Application UI
#include "ui/splashscreen.h"
#include "ui/dialogplugins.h"
#include "ui/mainwindow.h"
#include "ui/about.h"
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
    mSplashScreen = new SplashScreen;
    mSplashScreen->setSplashScreen(QPixmap(":/splash/img/SL_Splash_load.png"));
    mSplashScreen->setLoadLayer(QPixmap(":/splash/img/barload_only.png"), 80, 410);
    connect(ProgressHandler::instance(), SIGNAL(progress(int)),
            mSplashScreen, SLOT(slotSetPercentage(int)), Qt::UniqueConnection);
    mSplashScreen->show();

    // Schedule application loading
    QTimer::singleShot(0, this, SLOT(slotBuild()));
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
    supplyComponents();

    /*!
     * Stage 5: Load Settings
     */
    qDebug("    Loading Settings...");
    loadSettings();

    //initMenu
    DirectOrderSortingStrategy* lDirectOrderSortingStrategy = new DirectOrderSortingStrategy();

    mActionManager->setMenuCreationStategy(FileMenuGroup, lDirectOrderSortingStrategy);
    mActionManager->setMenuCreationStategy(ViewMenuGroup, lDirectOrderSortingStrategy);
    mActionManager->setMenuCreationStategy(EditMenuGroup, lDirectOrderSortingStrategy);
    mActionManager->setMenuCreationStategy(HelpMenuGroup, lDirectOrderSortingStrategy);
    mMainMenuBuilder->initMenu();

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

    // TODO: remove setting of global app setting to mediator (fix for settings autocommit needed)
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

    // Dialogs
    DialogPlugins *lDialogPlugins = new DialogPlugins(mMainWindow);
    mPluginSettingsMediator->setPluginDialog(lDialogPlugins);

    mAboutDialog = new About();

    createUiActions(mMainWindow);
    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::createUiActions(MainWindow *pMainWindow)
{
    UserAction *lActionOpen = new UserAction(tr("&Open"), this);
    //connect(lActionOpen, SIGNAL(triggered()), this, SLOT(newFile()));
    mActionManager->add(FileMenuGroup, "", lActionOpen);

    UserAction *lActionAddPage = new UserAction(tr("&Add Page"), this);
    connect(lActionAddPage, SIGNAL(triggered()), pMainWindow, SLOT(slotAddPage()));
    mActionManager->add(FileMenuGroup, "", lActionAddPage);

    UserAction *lActionQuit = new UserAction(tr("&Quit"), this);
    connect(lActionQuit, SIGNAL(triggered()), pMainWindow, SLOT(slotQuit()));
    mActionManager->add(FileMenuGroup, "", lActionQuit);

//    QAction *lActionSettings = new QAction(tr("&Settings"), this);
//    connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
//    mActionManager->addBack(ViewMenuGroup, "", lActionSettings);

    UserAction *lActionAboutSL = new UserAction(tr("&About SourseLine..."), this);
    connect(lActionAboutSL, SIGNAL(triggered()), mAboutDialog, SLOT(show()), Qt::UniqueConnection);
    mActionManager->add(HelpMenuGroup, "", lActionAboutSL);

    UserAction *lActionPluginSettings = new UserAction(tr("&Plugins Settings"), this);
    //connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
    mActionManager->add(HelpMenuGroup, "", lActionPluginSettings);

    UserAction *lActionPlugins = new UserAction(tr("&Plugins"), this);
    connect(lActionPlugins, SIGNAL(triggered()), mPluginSettingsMediator, SLOT(slotExecPluginSettings()));
    mActionManager->add(ViewMenuGroup, "", lActionPlugins);

    //    QAction *lActionSettings = new QAction(tr("&Settings"), this);
    //    connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
    //    mActionManager->addBack(ViewMenuGroup, "", lActionSettings);
}

void ApplicationBuilder::initPlugins()
{
    // Plugin loading managing classes
    PluginLoader *lPluginLoader = new PluginLoader(qApp);

    mPluginManager = new PluginManager(qApp);
    mPluginManager->setPluginLoader(lPluginLoader);
    mPluginSettingsMediator->setPluginManager(mPluginManager);


    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::registerComponents()
{
    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadSettings()
{
    mGlobalAppSettings->add("plugins", mPluginManager, "activePlugins");
    mGlobalAppSettings->setSettingsPath("active_plugins");
    mSettingsManager->addSettings("main_window", "Plugins", mGlobalAppSettings);
    mStorage->slotLoadSettings(mSettingsManager->pathBySettings(mGlobalAppSettings));


    mAppSettingsDialog = new AppSettingsDialog();

    Settings *lSettings = new Settings(this);
    ViewSettingPage *lVSettingPage = new ViewSettingPage(lSettings);
    lVSettingPage->setMainUi(mMainWindow->ui);
    mAppSettingsDialog->addSettingsItem(lVSettingPage);
    mSettingsManager->addSettings("main_window", lVSettingPage->name(), lSettings);

    UserAction *lActionSettings = new UserAction(tr("&Settings"), this);
    connect(lActionSettings, SIGNAL(triggered()), mAppSettingsDialog, SLOT(show()));
    AppSettingsDialog *lSettingsDialog = new AppSettingsDialog();
    lVSettingPage->setMainUi(mMainWindow->ui);
    lSettingsDialog->addSettingsItem(lVSettingPage);

    mActionManager->add(ViewMenuGroup, "", lActionSettings);
}

void ApplicationBuilder::supplyComponents()
{
    ComponentSorter *lComponentSorter = new ComponentSorter();

    FakeComponentSupplier *lFakeComponentSupplier = new FakeComponentSupplier();
    lComponentSorter->addSupplier(lFakeComponentSupplier);

    SettingsPageSuplier *lSettingsManagerSupliers = new SettingsPageSuplier();
    lSettingsManagerSupliers->setSettingsManager(mSettingsManager);
    lSettingsManagerSupliers->setAppSettingsDialog(mAppSettingsDialog);
    lComponentSorter->addSupplier(lSettingsManagerSupliers);

    CommandComponentSupplier *lCommandComponentSupplier = new CommandComponentSupplier();
    lCommandComponentSupplier->setActionManager(mActionManager);
    lComponentSorter->addSupplier(lCommandComponentSupplier);

    QStringList lActivePluginsList = mPluginManager->activePlugins();
    int i = 0;
    foreach (QString lPluginId, lActivePluginsList)
    {
        PluginInfo lPluginInfo = mPluginManager->pluginInfo(lPluginId);
        Plugin *lPlugin = mPluginManager->plugin(lPluginId);
        QObjectList list = lPlugin->components();
        lComponentSorter->setComponents(lPlugin->components(), lPluginInfo);

        ++i;
        ProgressHandler::instance()->setCurrentStageProgress(i * 100 / lActivePluginsList.size());
        QApplication::processEvents();
    }
    ProgressHandler::instance()->finishStage();
}


