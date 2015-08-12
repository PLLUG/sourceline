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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    // TASK: creation of tray menu should be peformed by ApplicationBuilder
    mTrayMenu = new QMenu(this);
    mTrayMenu->addAction(tr("Help"));
    mTrayMenu->addAction(tr("Quit"),this,SLOT(CloseWindow()));
    mTrayMenu->activeAction();
    mTrayIcon = new QSystemTrayIcon(this);
    mTrayIcon->setIcon(QIcon(":/splash/img/sourceline.ico"));
    mTrayIcon->setVisible(true);
    mTrayIcon->show();
    mTrayIcon->setContextMenu(mTrayMenu);

    // TASK: creation of PageManager should be performed by ApplicationBuilder
    mTabsAPI = new TabsAPI(this);
    mTabBar = new CustomTabBar(this);
    connect(mTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    this->setCentralWidget(mTabBar);

    mAmountOpenedTabs = 0;

    slotAddNewWorkplace();
}

MainWindow::~MainWindow()
{
    mTrayIcon->hide();
    delete ui;
    delete mTrayMenu;
    delete mTrayIcon;
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
    QString lTabName = tr("Name") + QString::number(mAmountOpenedTabs++);
    mTabsAPI->slotAddNewWorkplace(mTabBar, lTabName);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
}
