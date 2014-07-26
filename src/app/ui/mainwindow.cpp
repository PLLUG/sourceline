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
    TrayIcon->setIcon(QIcon(":/Icons/Icons/IconsLand.png"));
    TrayIcon->setVisible(true);
    TrayIcon->show();
    TrayIcon->setContextMenu(trayMenu);

    mPageManager = new PageManager(this);
    mTabBar = new CustomTabBar(this);
    connect(TrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    ui->uiTabToolBar->addWidget(mTabBar);
    readVisibilitySettings();
//    ui->uiHistoryTree->setVisible(false);
//    ui->uiEditorView->setVisible(false);

    connect(ui->actionSettings, SIGNAL(triggered()),
     this, SLOT(showSettings()), Qt::UniqueConnection);

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

void MainWindow::on_actionClose_triggered()
{
    qApp->quit();
}

void MainWindow::showSettings()
{
    AppSettingsDialog *lSettingsDialog = new AppSettingsDialog;
    SettingStorage *lStorage = new SettingStorage();
    PluginSettings *lPluginSettings = new PluginSettings();
    ViewSettingPage *lVSettingPage = new ViewSettingPage(lPluginSettings);
    lVSettingPage->setMainUi(ui);
    mSettingsManager->setStorage(lStorage);
    mSettingsManager->addSettings("main_window", lVSettingPage->name(), lPluginSettings);
    connect(lVSettingPage->settings(), SIGNAL(settingsChanged(QMap<QString,QVariant>)),
            mSettingsManager, SLOT(slotWriteSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);
    connect(lStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
                             lVSettingPage->settings(), SLOT(slotSetSettings(QMap<QString,QVariant>)));
    lStorage->slotLoadSettings(mSettingsManager->pathBySettings(lPluginSettings));
    lSettingsDialog->addSettingsItem(lVSettingPage);

    lSettingsDialog->show();
}

void MainWindow::on_actionAdd_Page_triggered()
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
    PluginSettings *lPluginSettings = new PluginSettings();
    ViewSettingPage *lVSettingPage = new ViewSettingPage(lPluginSettings);
    lVSettingPage->setMainUi(ui);
    mSettingsManager->setStorage(lStorage);
    mSettingsManager->addSettings("main_window", lVSettingPage->name(), lPluginSettings);

    connect(lStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
                             lVSettingPage->settings(), SLOT(slotSetSettings(QMap<QString,QVariant>)));
    lStorage->slotLoadSettings(mSettingsManager->pathBySettings(lPluginSettings));
}
