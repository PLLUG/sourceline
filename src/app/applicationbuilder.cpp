#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "splashscreen.h"
#include "settings.h"
#include "pluginsupport/componentsorter.h"
#include "pluginsupport/supliers/fakecomponentsupplier.h"
#include "pluginsupport/pluginloader.h"
#include "pluginsupport/pluginmanager.h"
#include "pluginsupport/pluginsettingsmediator.h"
#include "../ui/dialogplugins.h"

// Ui
#include "mainwindow.h"
#include "actionmanager.h"
#include "mainmenubuilder.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent),
    mActionManager(new ActionManager(this)),
    mMainMenuBuilder(new MainMenuBuilder(this))
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

    QTimer::singleShot(1500, mSplashScreen, SLOT(deleteLater()));
}

void ApplicationBuilder::initUi()
{
    // ....

    mMainWindow = new MainWindow;
    mMainWindow->lower();
    mMainWindow->show();
    mMainMenuBuilder->setMenuBar(mMainWindow->menuBar());
    createUiActions(mMainWindow);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadPlugins()
{
    PluginLoader *lPluginLoader = new PluginLoader();

    PluginManager *lPluginManager =new PluginManager();
    lPluginManager->setPluginLoader(lPluginLoader);

    DialogPlugins *lDialogPlugins = new DialogPlugins();

    PluginSettingsMediator *lPluginSettingsMediator = new PluginSettingsMediator();
    lPluginSettingsMediator->setPluginDialog(lDialogPlugins);
    lPluginSettingsMediator->setPluginManager(lPluginManager);

    QAction *lActionPlugins = new QAction(tr("&Plugins"), this);
    connect(lActionPlugins, SIGNAL(triggered()), lPluginSettingsMediator, SLOT(slotExecPluginSettings()));
    mActionManager->addBack(ViewMenuGroup, "", lActionPlugins);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadSettings()
{
    SettingsManager *lSettingsManager = new SettingsManager(this);
    AppSettingsDialog *lSettingsDialog = new AppSettingsDialog();
    Settings *lSettings = new Settings(this);
    ViewSettingPage *lVSettingPage = new ViewSettingPage(lSettings);
    lVSettingPage->setMainUi(mMainWindow->ui);
    lSettingsDialog->addSettingsItem(lVSettingPage);
    lSettingsManager->addSettings("main_window", lVSettingPage->name(), lSettings);

    SettingStorage *lStorage = new SettingStorage();
    lSettingsManager->setStorage(lStorage);

    connect(lVSettingPage->settings(), SIGNAL(settingsChanged(QMap<QString,QVariant>)),
            lSettingsManager, SLOT(slotWriteSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);
    connect(lStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
                             lVSettingPage->settings(), SLOT(slotSetSettings(QMap<QString,QVariant>)));
    lStorage->slotLoadSettings(lSettingsManager->pathBySettings(lVSettingPage->settings()));

    QAction *lActionSettings = new QAction(tr("&Settings"), this);
    connect(lActionSettings, SIGNAL(triggered()), lSettingsDialog, SLOT(show()));
    mActionManager->addBack(ViewMenuGroup, "", lActionSettings);
}

void ApplicationBuilder::supplyComponents()
{
    FakeComponentSupplier *pFakeComponentSupplier = new FakeComponentSupplier();
    ComponentSorter *pComponentSorter = new ComponentSorter();
    pComponentSorter->addSupplier("FakeComponent", pFakeComponentSupplier);
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


