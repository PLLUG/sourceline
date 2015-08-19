// TASK: add GPL header

// TASK: refactor includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tabsapi.h"
#include "customtabbar.h"
#include "settings_dialog/settingstorage.h"
#include "settings_dialog/settingsmanager.h"

#include <QMessageBox>
#include <QFile>
#include <QAction>
#include <QSettings>
#include <QDebug>
#include <QTabWidget>
#include <QHBoxLayout>

MainWindow::MainWindow(SettingsManager *pSettingsManager, SettingStorage *mStorage, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    mSettingsManager = pSettingsManager;
    ui->setupUi(this);    
    // TASK: creation of tray menu should be peformed by ApplicationBuilder
    trayMenu = new QMenu(this);
    trayMenu->addAction("Help");
    trayMenu->addAction("Quit",this,SLOT(CloseWindow()));
    trayMenu->activeAction();
    TrayIcon = new QSystemTrayIcon(this);
    TrayIcon->setIcon(QIcon(":/splash/img/sourceline.ico"));
    TrayIcon->setVisible(true);
    TrayIcon->show();
    TrayIcon->setContextMenu(trayMenu);

    setMinimumSize(800,600);

    // TASK: creation of PageManager should be performed by ApplicationBuilder
    mTabsAPI = new TabsAPI(this);
    mTabBar = new CustomTabBar(pSettingsManager, mStorage, this);
    connect(TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    this->setCentralWidget(mTabBar);

    //connect(mTabBar, &CustomTabBar::tabCloseRequested, mTabBar, &CustomTabBar::removeTab);

    mAmountOpenedTabs = 0;

    slotAddNewWorkplace();
}

MainWindow::~MainWindow()
{
    TrayIcon->hide();
    delete ui;
    delete trayMenu;
    delete TrayIcon;
}

void MainWindow::CloseWindow()
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
         this->show();
         this->showNormal();
         this->activateWindow();
         this->raise();
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
    QString lTabName = "Name" + QString::number(mAmountOpenedTabs++);
    mTabsAPI->slotAddNewWorkplace(mTabBar, lTabName);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
}
