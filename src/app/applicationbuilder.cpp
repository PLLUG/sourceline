#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "splashscreen.h"

// Ui
#include "mainwindow.h"

ApplicationBuilder::ApplicationBuilder(QObject *parent) :
    QObject(parent)
{
    ProgressHandler::instance()->setStageCount(2);

    QTimer::singleShot(0, this, SLOT(slotBuild()));

    /// Init splash screen
    mSplashScreen = new SplashScreen;
    mSplashScreen->setSplashScreen(QPixmap(":/splash/img/SL_Splash_load.png"));
    mSplashScreen->setLoadLayer(QPixmap(":/splash/img/barload_only.png"), 80, 410);
    connect(ProgressHandler::instance(), SIGNAL(progress(int)),
            mSplashScreen, SLOT(slotSetPercentage(int)), Qt::UniqueConnection);
    mSplashScreen->show();
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

    QTimer::singleShot(1000, mSplashScreen, SLOT(deleteLater()));
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
    ProgressHandler::instance()->finishStage();
}

