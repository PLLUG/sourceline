#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "settings.h"
#include "pluginsupport/componentsorter.h"
#include "pluginsupport/supliers/fakecomponentsupplier.h"
#include "pluginsupport/supliers/settingspagesupplier.h"
#include "pluginsupport/pluginloader.h"
#include "pluginsupport/pluginmanager.h"
#include "pluginsupport/pluginsettingsmediator.h"
#include "plugin.h"

// Ui
#include "ui/splashscreen.h"
#include "ui/dialogplugins.h"
#include "ui/mainwindow.h"
#include "ui/actionmanager.h"
#include "ui/mainmenubuilder.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent),
    mMainWindow(0),
    mActionManager(new ActionManager(this)),
    mMainMenuBuilder(new MainMenuBuilder(this)),
    mPluginManager(0),
    mAppSettingsDialog(0),
    mSettingsManager(new SettingsManager(this)),
    mStorage(new SettingStorage)
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


