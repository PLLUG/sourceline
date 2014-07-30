#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "splashscreen.h"

// Ui
#include "mainwindow.h"
#include "actionmanager.h"
#include "mainmenubuilder.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent),
    mActionManager(new ActionManager(this)),
    mMainMenuBuilder(new MainMenuBuilder(this))
{
    ProgressHandler::instance()->setStageCount(2);

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
     * Stage 3: Getting components
     */
    supplyComponents();

    //initMenu
    mMainMenuBuilder->initMenu();

    QTimer::singleShot(1500, mSplashScreen, SLOT(deleteLater()));
}

void ApplicationBuilder::initUi()
{
    // ....

    MainWindow *lMainWindow = new MainWindow;
    lMainWindow->lower();
    lMainWindow->show();
    mMainMenuBuilder->setMenuBar(lMainWindow->menuBar());
    createUiActions(lMainWindow);

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::loadPlugins()
{
    // ....
    // TASK: create plugin loader
    // TASK: create plugin manager
    // TASK: create settings dialog mediator

    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::supplyComponents()
{
    // ....
    // TASK : create component suppliers
    // TASK : create and initialize sorters
}

void ApplicationBuilder::createUiActions(MainWindow *pMainWindow)
{
    QAction *lActionOpen = new QAction(tr("&Open"), this);
    //connect(lActionOpen, SIGNAL(triggered()), this, SLOT(newFile()));
    mActionManager->add(FileMenuGroup, "", lActionOpen);

    QAction *lActionAddPage = new QAction(tr("&Add Page"), this);
    connect(lActionAddPage, SIGNAL(triggered()), pMainWindow, SLOT(slotAddPage()));
    mActionManager->add(FileMenuGroup, "", lActionAddPage);

    QAction *lActionQuit = new QAction(tr("&Quit"), this);
    connect(lActionQuit, SIGNAL(triggered()), pMainWindow, SLOT(slotQuit()));
    mActionManager->add(FileMenuGroup, "", lActionQuit);

    QAction *lActionSettings = new QAction(tr("&Settings"), this);
    connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
    mActionManager->add(ViewMenuGroup, "", lActionSettings);

    QAction *lActionAboutSL = new QAction(tr("&About SourseLine"), this);
    //(lActionQuit, SIGNAL(triggered()), pMainWindow, SLOT(slotQuit()));
    mActionManager->add(HelpMenuGroup, "", lActionAboutSL);

    QAction *lActionPluginSettings = new QAction(tr("&Plugins Settings"), this);
    //connect(lActionSettings, SIGNAL(triggered()), pMainWindow, SLOT(slotShowSettings()));
    mActionManager->add(HelpMenuGroup, "", lActionPluginSettings);
}


