#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QAction>
#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mSettingsManager(new SettingsManager(this))
{
    ui->setupUi(this);
    trayMenu = new QMenu();
    trayMenu->addAction("Help");
    trayMenu->addAction("Quit",this,SLOT(CloseWindow()));
    trayMenu->activeAction();
    TrayIcon = new QSystemTrayIcon();
    TrayIcon->setIcon(QIcon(":/splash/img/sourceline.ico"));
    TrayIcon->setVisible(true);
    TrayIcon->show();
    TrayIcon->setContextMenu(trayMenu);

    mSettingsDialog = new AppSettingsDialog(this);
    mSettings = new Settings(this);
    mVSettingPage = new ViewSettingPage(mSettings);
    mVSettingPage->setMainUi(ui);
    mSettingsDialog->addSettingsItem(mVSettingPage);
    mSettingsManager->addSettings("main_window", mVSettingPage->name(), mSettings);

    mPageManager = new PageManager(this);
    mTabBar = new CustomTabBar(this);
    connect(TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    ui->uiTabToolBar->addWidget(mTabBar);

    readVisibilitySettings();


    connect(mPageManager, SIGNAL(pageAdded(int, QString)), mTabBar, SLOT(slotAddTab(int,QString)), Qt::UniqueConnection);
    connect(mTabBar, SIGNAL(tabCloseRequested(int)), mPageManager, SLOT(slotRemovePage(int)));
    connect(mTabBar, SIGNAL(currentChanged(int)), mPageManager, SLOT(slotChangeCurrentPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiFileView, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiRevisionTable, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiConsole, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiHistoryTree, SLOT(slotSetPage(int)));
    connect(mPageManager, SIGNAL(currentPageChanged(int)), ui->uiEditorView, SLOT(slotSetPage(int)));
    connect(mTabBar, SIGNAL(tabMoved(int,int)), mPageManager, SLOT(slotTabMoved(int,int)));

    this->tabifyDockWidget(ui->uiFileView, ui->uiHistoryTree);
    this->tabifyDockWidget(ui->uiRevisionTable, ui->uiEditorView);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete trayMenu;
    delete TrayIcon;
}

void MainWindow::CloseWindow()
{
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
    qApp->quit();
}

void MainWindow::slotShowSettings()
{
    mSettingsDialog->show();
}

void MainWindow::slotAddPage()
{
    static int a = 0;
    QString lTabName = "Name" + QString::number(a++);
    mPageManager->slotAddPage(lTabName);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    // ui->uiFileView->setMinimumHeight(this->height());
}

void MainWindow::readVisibilitySettings()
{
    SettingStorage *lStorage = new SettingStorage();
    mVSettingPage->setMainUi(ui);
    mSettingsManager->setStorage(lStorage);
    mSettingsManager->addSettings("main_window", mVSettingPage->name(), mSettings);

    connect(mVSettingPage->settings(), SIGNAL(settingsChanged(QMap<QString,QVariant>)),
            mSettingsManager, SLOT(slotWriteSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);
    connect(lStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
                             mVSettingPage->settings(), SLOT(slotSetSettings(QMap<QString,QVariant>)));
    lStorage->slotLoadSettings(mSettingsManager->pathBySettings(mSettings));
}
