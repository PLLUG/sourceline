#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "splashscreen.h"
#include "settings.h"
#include "pluginsupport/componentsorter.h"
#include "pluginsupport/supliers/fakecomponentsupplier.h"
#include "pluginsupport/supliers/settingspagesupplier.h"
#include "pluginsupport/pluginloader.h"
#include "pluginsupport/pluginmanager.h"
#include "pluginsupport/pluginsettingsmediator.h"
#include "../ui/dialogplugins.h"
#include "plugin.h"

// Ui
#include "mainwindow.h"
#include "actionmanager.h"
#include "mainmenubuilder.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent),
    mMainWindow(0),
    mActionManager(new ActionManager(this)),
    mMainMenuBuilder(new MainMenuBuilder(this)),
    mSettingsManager(0),
    mPluginManager(0),
    mAppSettingsDialog(0)
{
    ProgressHandler::instance()->setStageCount(3);

    /// Init splash screen
    mSplashScreen = new SplashScreen;
    mSplashScreen->setSplashScreen(QPixmap(":/splash/img/SL_Splash_load.png"));
    mSplashScreen->setLoadLayer(QPixmap(":/splash/img/barload_only.png"), 80, 410);
    connect(ProgressHandler::instance(), SIGNAL(progress(int)),
            mSplashScreen, SLOT(slotSetPercentage(int)), Qt::UniqueConnection);
    mSplashScreen->show();

    QTimer::singleShot(0, this, SLOT(slotBuild()));

    //init mActionManager for mMainMenuBuilder
    mMainMenuBuilder->setActionManager(mActionManager);
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
    mPluginManager->slotSetActivePlugins(QStringList("TestPlugin"));

    DialogPlugins *lDialogPlugins = new DialogPlugins();

    PluginSettingsMediator *lPluginSettingsMediator = new PluginSettingsMediator();
    lPluginSettingsMediator->setPluginDialog(lDialogPlugins);
    lPluginSettingsMediator->setPluginManager(mPluginManager);

    QAction *lActionPlugins = new QAction(tr("&Plugins"), this);
    connect(lActionPlugins, SIGNAL(triggered()), lPluginSettingsMediator, SLOT(slotExecPluginSettings()));
    mActionManager->addBack(ViewMenuGroup, "", lActionPlugins);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadSettings()
{
    mSettingsManager = new SettingsManager(this);
    mAppSettingsDialog = new AppSettingsDialog();
    Settings *lSettings = new Settings(this);
    ViewSettingPage *lVSettingPage = new ViewSettingPage(lSettings);
    lVSettingPage->setMainUi(mMainWindow->ui);
    mAppSettingsDialog->addSettingsItem(lVSettingPage);
    mSettingsManager->addSettings("main_window", lVSettingPage->name(), lSettings);

    SettingStorage *lStorage = new SettingStorage();
    mSettingsManager->setStorage(lStorage);

    connect(lVSettingPage->settings(), SIGNAL(settingsChanged(QMap<QString,QVariant>)),
            mSettingsManager, SLOT(slotWriteSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);
    connect(lStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
                             lVSettingPage->settings(), SLOT(slotSetSettings(QMap<QString,QVariant>)));
    lStorage->slotLoadSettings(mSettingsManager->pathBySettings(lVSettingPage->settings()));

    QAction *lActionSettings = new QAction(tr("&Settings"), this);
    connect(lActionSettings, SIGNAL(triggered()), mAppSettingsDialog, SLOT(show()));
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
    foreach (QString lPluginId, lActivePluginsList)
    {
        PluginInfo lPluginInfo = mPluginManager->pluginInfo(lPluginId);
        Plugin *lPlugin = mPluginManager->plugin(lPluginId);
        QObjectList list = lPlugin->components();
        lComponentSorter->setComponents(lPlugin->components(), lPluginInfo);
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


