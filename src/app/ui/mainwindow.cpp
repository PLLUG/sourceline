// TASK: add GPL header

// TASK: refactor includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabsapi.h"
#include "customtabbar.h"
#include "settings_dialog/settingstorage.h"
#include "settings_dialog/settingsmanager.h"
#include "settings.h"

#include <QMessageBox>
#include <QFile>
#include <QAction>
#include <QSettings>
#include <QDebug>
#include <QTabWidget>
#include <QStringList>
#include <QCloseEvent>
#include <QString>

MainWindow::MainWindow(SettingsManager *pSettingsManager, SettingStorage *pStorage, QWidget *parent) :
    QMainWindow(parent)
  ,mTrayIcon{new QSystemTrayIcon(this)}
  ,mTrayMenu{new QMenu(this)}
  ,mTabBar{nullptr}
  ,mTabsAPI{new TabsAPI(this)}
  ,ui(new Ui::MainWindow)
  ,mAmountOpenedTabs{0}
  ,mStorage(pStorage)
  ,mSettingsManager(pSettingsManager)
  ,mSettings{new Settings(this)}
{
    ui->setupUi(this);
    // TASK: creation of tray menu should be peformed by ApplicationBuilder
    mTrayMenu->addAction(tr("Help"));
    mTrayMenu->addAction(tr("Quit"),this,SLOT(slotCloseWindow()));
    mTrayMenu->activeAction();
    mTrayIcon->setIcon(QIcon(":/splash/img/sourceline.ico"));
    mTrayIcon->setVisible(true);
    mTrayIcon->show();
    mTrayIcon->setContextMenu(mTrayMenu);

    setMinimumSize(800,600);

    // TASK: creation of PageManager should be performed by ApplicationBuilder
    mTabBar = new CustomTabBar(pSettingsManager, mStorage, this);
    setCentralWidget(mTabBar);
    //connect(mTabBar, &CustomTabBar::tabCloseRequested, mTabBar, &CustomTabBar::removeTab);

    mSettings->setAutoCommit(true);
    mSettingsManager->addSettings("listTabsForOpening", "listTabs", mSettings);

    mSettings->add("tabs", this, "openedTabs");
    mSettings->subscribe("tabs", this, SLOT(setOpenedTabs(QVariant)));

    mStorage->slotLoadSettings(mSettingsManager->pathBySettings(mSettings));

    connect(mTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);

    if(!mListOpenedTabs.count())
    {
        slotAddNewWorkplace();
    }
}

MainWindow::~MainWindow()
{
    mTrayIcon->hide();
    delete ui;
    delete mTrayMenu;
    delete mTrayIcon;
}

QStringList MainWindow::openedTabs() const
{
    mListOpenedTabs.clear();

    for(int i = 0; i < mTabsAPI->getCountTabs(mTabBar); i++)
    {
        QString nameTab = mTabsAPI->getNameOfTabById(mTabBar, i);
        mListOpenedTabs << nameTab;
    }

    return mListOpenedTabs;
}

void MainWindow::setOpenedTabs(QVariant pOpenedTabs)
{
    QStringList lListOpenedTabs = pOpenedTabs.toStringList();
    if (lListOpenedTabs == mListOpenedTabs)
        return;

    foreach(const QString &lTabName, lListOpenedTabs)
    {
        mTabsAPI->slotAddNewWorkplace(mTabBar, lTabName);
        mAmountOpenedTabs++;
    }

    mTabsAPI->loadSettingsForTabs(mTabBar);

    mListOpenedTabs = lListOpenedTabs;
}

void MainWindow::slotCloseWindow()
{
    // TASK: use close action from ActionManager
    // TASK: ActionManager should create menu for tray icon
    // TASK: create appropriate menu creation strategy subclass for create menu
    qApp->quit();
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::DoubleClick:
    {
        show();
        showNormal();
        activateWindow();
        raise();
    }
    default:
        ;
    }
}

void MainWindow::slotQuit()
{
    // TASK: create Quit action instead and register it in ActionManager
    qApp->quit();
}

void MainWindow::slotAddNewWorkplace()
{
    mTabsAPI->slotAddNewWorkplace(mTabBar, tr("Name") + QString::number(mAmountOpenedTabs++));
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::closeEvent(QCloseEvent *pEvent)
{
    emit openedTabsChanged(mListOpenedTabs);
    pEvent->accept();
    QMainWindow::closeEvent(pEvent);
}
