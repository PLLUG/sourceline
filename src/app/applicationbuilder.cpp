#include "applicationbuilder.h"

#include <QTimer>

// Loading
#include "progresshandler.h"
#include "splashscreen.h"
#include "pluginsupport/componentsorter.h"
#include "pluginsupport/supliers/fakecomponentsupplier.h"
#include "pluginsupport/pluginloader.h"
#include "pluginsupport/pluginmanager.h"
#include "pluginsupport/pluginsettingsmediator.h"
#include "../ui/dialogplugins.h"

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
    PluginLoader *lPluginLoader = new PluginLoader();

    PluginManager *lPluginManager =new PluginManager();
    lPluginManager->setPluginLoader(lPluginLoader);

    DialogPlugins *lDialogPlugins = new DialogPlugins();

    PluginSettingsMediator *lPluginSettingsMediator = new PluginSettingsMediator();
    lPluginSettingsMediator->setPluginDialog(lDialogPlugins);
    lPluginSettingsMediator->setPluginManager(lPluginManager);
    ProgressHandler::instance()->finishStage();
}

void ApplicationBuilder::supplyComponents()
{
    FakeComponentSupplier *pFakeComponentSupplier = new FakeComponentSupplier();
    ComponentSorter *pComponentSorter = new ComponentSorter();
    pComponentSorter->addSupplier("FakeComponent", pFakeComponentSupplier);
}

