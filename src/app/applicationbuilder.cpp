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
#include "pluginsupport/pluginloader.h"
#include "pluginsupport/pluginmanager.h"
#include "pluginsupport/pluginsettingsmediator.h"

// Settings
#include "settings.h"

// Main Application Classes
#include "ui/actionmanager.h"
#include "ui/mainmenubuilder.h"

// Application UI
#include "ui/splashscreen.h"
#include "ui/dialogplugins.h"
#include "ui/mainwindow.h"


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

    // Application UI
    mSplashScreen = 0;
    mMainWindow = 0;
    mAppSettingsDialog = 0;

    ProgressHandler::instance()->setStageCount(3);

    /// Init splash screen
    mSplashScreen = new SplashScreen;
    mSplashScreen->setSplashScreen(QPixmap(":/splash/img/SL_Splash_load.png"));
    mSplashScreen->setLoadLayer(QPixmap(":/splash/img/barload_only.png"), 80, 410);
    connect(ProgressHandler::instance(), SIGNAL(progress(int)),
            mSplashScreen, SLOT(slotSetPercentage(int)), Qt::UniqueConnection);
    mSplashScreen->show();

    QTimer::singleShot(0, this, SLOT(slotBuild()));

    mActionManager = new ActionManager(qApp);

    mMainMenuBuilder = new MainMenuBuilder(qApp);
    mMainMenuBuilder->setActionManager(mActionManager);

    mStorage = new SettingStorage;

    mSettingsManager = new SettingsManager(qApp);
    mSettingsManager->setStorage(mStorage);
}

void ApplicationBuilder::slotBuild()
{
    /*!
     * Stage 1: Initialize UI
     */
    initUi();

    /*!
     * Stage 2: Load Plugins
     */
    loadPlugins();

    /*!
     * Stage 3: Load Settings
     */
    loadSettings();

    /*!
     * Stage 4: Getting components
     */
    supplyComponents();

    //initMenu
    mMainMenuBuilder->initMenu();

    mMainWindow->show();

    QTimer::singleShot(1500, mSplashScreen, SLOT(deleteLater()));
}

void ApplicationBuilder::initUi()
{
    // ....

    mMainWindow = new MainWindow;
    mMainWindow->lower();
    mMainMenuBuilder->setMenuBar(mMainWindow->menuBar());
    createUiActions(mMainWindow);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadPlugins()
{
    PluginLoader *lPluginLoader = new PluginLoader();

    mPluginManager = new PluginManager();
    mPluginManager->setPluginLoader(lPluginLoader);
    //temp filling Active Plugins
    mPluginManager->slotSetActivePlugins(lPluginLoader->pluginIds());



    DialogPlugins *lDialogPlugins = new DialogPlugins();

    PluginSettingsMediator *lPluginSettingsMediator = new PluginSettingsMediator();
    lPluginSettingsMediator->setPluginDialog(lDialogPlugins);
    lPluginSettingsMediator->setPluginManager(mPluginManager);

    Settings *lSettings = new Settings(this);
    lPluginSettingsMediator->setSettings(lSettings);
    lSettings->add("plugins", mPluginManager, "activePlugins");
    lSettings->setSettingsPath("active_plugins");
    mSettingsManager->addSettings("main_window", "Plugins", lSettings);
    connect(lSettings, SIGNAL(settingsChanged(QMap<QString,QVariant>)),
            mSettingsManager, SLOT(slotWriteSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);

    connect(mStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
                             lSettings, SLOT(slotSetSettings(QMap<QString,QVariant>)));

    mStorage->slotLoadSettings(mSettingsManager->pathBySettings(lSettings));

    QAction *lActionPlugins = new QAction(tr("&Plugins"), this);
    connect(lActionPlugins, SIGNAL(triggered()), lPluginSettingsMediator, SLOT(slotExecPluginSettings()));
    mActionManager->addBack(ViewMenuGroup, "", lActionPlugins);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadSettings()
{
    SettingStorage *lStorage = new SettingStorage();

    mSettingsManager = new SettingsManager(this);
    mSettingsManager->setStorage(lStorage);

    mAppSettingsDialog = new AppSettingsDialog();

    Settings *lSettings = new Settings(this);
    ViewSettingPage *lVSettingPage = new ViewSettingPage(lSettings);
    lVSettingPage->setMainUi(mMainWindow->ui);
    mAppSettingsDialog->addSettingsItem(lVSettingPage);
    mSettingsManager->addSettings("main_window", lVSettingPage->name(), lSettings);

    QAction *lActionSettings = new QAction(tr("&Settings"), this);
    connect(lActionSettings, SIGNAL(triggered()), mAppSettingsDialog, SLOT(show()));
    AppSettingsDialog *lSettingsDialog = new AppSettingsDialog();
    lVSettingPage->setMainUi(mMainWindow->ui);
    lSettingsDialog->addSettingsItem(lVSettingPage);

    mActionManager->addBack(ViewMenuGroup, "", lActionSettings);
}

void ApplicationBuilder::supplyComponents()
{
    FakeComponentSupplier *lFakeComponentSupplier = new FakeComponentSupplier();

    SettingsPageSuplier *lSettingsManagerSupliers = new SettingsPageSuplier();
    lSettingsManagerSupliers->setSettingsManager(mSettingsManager);
    lSettingsManagerSupliers->setAppSettingsDialog(mAppSettingsDialog);

    ComponentSorter *lComponentSorter = new ComponentSorter();
    lComponentSorter->addSupplier(lFakeComponentSupplier);
    lComponentSorter->addSupplier(lSettingsManagerSupliers);


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

void ApplicationBuilder::createUiActions(MainWindow *pMainWindow)
{
    QAction *lActionOpen = new QAction(tr("&Open"), this);
    //connect(lActionOpen, SIGNAL(triggered()), this, SLOT(newFile()));
    mActionManager->addBack(FileMenuGroup, "", lActionOpen);

    QAction *lActionAddPage = new QAction(tr("&Add Page"), this);
    connect(lActionAddPage, SIGNAL(triggered()), pMainWindow, SLOT(slotAddPage()));
    mActionManager->addBack(FileMenuGroup, "", lActionAddPage);

    QAction *lActionQuit = new QAction(tr("&Quit"), this);
    connect(lActionQuit, SIGNAL(triggered()), pMainWindow, SLOT(slotQuit()));
    mActionManager->addBack(FileMenuGroup, "", lActionQuit);

//    QAction *lActionSettings = new QAction(tr("&Settings"), this);
//    connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
//    mActionManager->addBack(ViewMenuGroup, "", lActionSettings);

    QAction *lActionAboutSL = new QAction(tr("&About SourseLine"), this);
    //(lActionQuit, SIGNAL(triggered()), pMainWindow, SLOT(slotQuit()));
    mActionManager->addBack(HelpMenuGroup, "", lActionAboutSL);

    QAction *lActionPluginSettings = new QAction(tr("&Plugins Settings"), this);
    //connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
    mActionManager->addBack(HelpMenuGroup, "", lActionPluginSettings);
}


