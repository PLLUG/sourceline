// TASK: add GPL header

// TASK: refactor includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pagemanager.h"
#include "customtabbar.h"
#include "settings_dialog/settingstorage.h"
#include "settings_dialog/settingsmanager.h"

#include <QMessageBox>
#include <QFile>
#include <QAction>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TASK: creation of tray menu should be peformed by ApplicationBuilder
    trayMenu = new QMenu();
    trayMenu->addAction("Help");
    trayMenu->addAction("Quit",this,SLOT(CloseWindow()));
    trayMenu->activeAction();
    TrayIcon = new QSystemTrayIcon();
    TrayIcon->setIcon(QIcon(":/splash/img/sourceline.ico"));
    TrayIcon->setVisible(true);
    TrayIcon->show();
    TrayIcon->setContextMenu(trayMenu);

    // TASK: creation of PageManager should be performed by ApplicationBuilder
    mPageManager = new PageManager(this);
    mTabBar = new CustomTabBar(this);
    connect(TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    ui->uiTabToolBar->addWidget(mTabBar);

    connect(mPageManager, SIGNAL(pageAdded(int, QString)), mTabBar, SLOT(slotAddTab(int,QString)), Qt::UniqueConnection);
    connect(mTabBar, SIGNAL(tabCloseRequested(int)), mPageManager, SLOT(slotRemovePage(int)));
    connect(mTabBar, SIGNAL(currentChanged(int)), mPageManager, SLOT(slotChangeCurrentPage(int)));
    // TASK: fixme - connetion
//    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiFileView, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiRevisionTable, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiConsole, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiHistoryTree, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiEditorView, SLOT(slotSetPage(int)));
    connect(mTabBar, SIGNAL(tabMoved(int,int)), mPageManager, SLOT(slotTabMoved(int,int)));

    this->splitDockWidget( ui->uiRevisionTable, ui->uiEditorView, Qt::Horizontal);
    this->splitDockWidget(ui->uiEditorView, ui->uiConsole, Qt::Vertical);
    this->tabifyDockWidget(ui->uiEditorView, ui->uiFileView);
    this->tabifyDockWidget(ui->uiRevisionTable, ui->uiHistoryTree);
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

void MainWindow::slotAddPage()
{
    static int a = 0;
    QString lTabName = "Name" + QString::number(a++);
    // TASK: page should be added in TabBuilder class
    mPageManager->slotAddPage(lTabName);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    // ui->uiFileView->setMinimumHeight(this->height());
}
