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
    QMainWindow(parent)
  ,mTrayIcon{new QSystemTrayIcon(this)}
  ,mTrayMenu{new QMenu(this)}
  ,mTabBar{new CustomTabBar(this)}
  ,mTabsAPI{new TabsAPI(this)}
  ,ui(new Ui::MainWindow)
  ,mAmountOpenedTabs{0}
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

    // TASK: creation of PageManager should be performed by ApplicationBuilder
    connect(mTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);

    setCentralWidget(mTabBar);

    slotAddNewWorkplace();
}

MainWindow::~MainWindow()
{
    mTrayIcon->hide();
    delete ui;
    delete mTrayMenu;
    delete mTrayIcon;
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
    QString lTabName = tr("Name") + QString::number(mAmountOpenedTabs++);
    mTabsAPI->slotAddNewWorkplace(mTabBar, lTabName);
}

Ui::MainWindow *MainWindow::getUi() const
{
    return ui;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
}
