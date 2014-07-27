#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "splashscreen.h"
#include "pluginsupport/componentsorter.h"
#include "pluginsupport/supliers/fakecomponentsupplier.h"

// Ui
#include "mainwindow.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent)
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


    QTimer::singleShot(1500, mSplashScreen, SLOT(deleteLater()));
}

void ApplicationBuilder::initUi()
{
    // ....

    MainWindow * lMainWindow = new MainWindow;
    lMainWindow->lower();
    lMainWindow->show();

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
    FakeComponentSupplier *pFakeComponentSupplier = new FakeComponentSupplier();
    ComponentSorter *pComponentSorter = new ComponentSorter();
    pComponentSorter->addSupplier("FakeComponent", pFakeComponentSupplier);
}

