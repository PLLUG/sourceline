#include <QMessageBox>
#include <QFile>
#include <QAction>
#include <QSettings>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewsettings.h"
#include "customtabbar.h"
#include "pagemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), mViewSettings(new ViewSettings(this))
{
    ui->setupUi(this);
    QSettings settings;

     restoreGeometry(settings.value("mainWindowGeometry").toByteArray());
    this->setWindowIcon(QIcon(":/Icons/Icons/Icon3.png"));
    mTrayMenu = new QMenu();
    mTrayMenu->addAction("Help");
    mTrayMenu->addAction("Quit",this,SLOT(CloseWindow()));
    mTrayMenu->activeAction();
    mTrayIcon = new QSystemTrayIcon();
    mTrayIcon->setIcon(QIcon(":/Icons/Icons/Icon3.png"));
    mTrayIcon->setVisible(true);
    mTrayIcon->show();
    mTrayIcon->setContextMenu(mTrayMenu);

    mPageManager = new PageManager(this);
    mTabBar = new CustomTabBar;
    mTabBar->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    ui->uiTabToolBar->addWidget(mTabBar);

    connect(mTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                 this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    ui->uiHistoryTree->setVisible(false);
    ui->uiEditorView->setVisible(false);

    connect(ui->actionSettings, SIGNAL(triggered()),
     this, SLOT(showSettings()), Qt::UniqueConnection);
    connect(mViewSettings, SIGNAL(accepted()),
     this, SLOT(slotPreferencesAccepted()), Qt::UniqueConnection);

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
    restoreState(settings.value("mainWindowState").toByteArray());
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mTrayMenu;
    delete mTrayIcon;
}

void MainWindow::CloseWindow()
{
    mTrayIcon->hide();
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
    QSettings settings;
       settings.setValue("mainWindowGeometry", saveGeometry());
       settings.setValue("mainWindowState", saveState());
    mTrayIcon->hide();
    qApp->quit();
}

void MainWindow::showSettings()
{
   readSettings();
   mViewSettings->show();
}

void MainWindow::readSettings()
{

 QSettings lSettings(QSettings::NativeFormat, QSettings::UserScope,
 "", qApp->applicationName());
 lSettings.beginGroup("SETTINGS_GROUP_VIEW");
 bool lShowFileView = lSettings.value("SETTING_SHOW_FileView", ui->uiFileView->isVisible()).toBool();
 mViewSettings->setFileViewVisible(lShowFileView);

 bool lShowRevisionTable = lSettings.value("SETTING_SHOW_RevisionTable", ui->uiRevisionTable->isVisible()).toBool();
 mViewSettings->setRevisionTableVisible(lShowRevisionTable);

 bool lShowConsole = lSettings.value("SETTING_SHOW_Console", ui->uiConsole->isVisible()).toBool();
 mViewSettings->setConsoleVisible(lShowConsole);

 bool lShowHistoryTree = lSettings.value("SETTING_SHOW_HistoryTree", ui->uiHistoryTree->isVisible()).toBool();
 mViewSettings->setHistoryTreeVisible(lShowHistoryTree);

 bool lShowEditorView = lSettings.value("SETTING_SHOW_EditorView", ui->uiEditorView->isVisible()).toBool();
 mViewSettings->setEditorViewVisible(lShowEditorView);

}

void MainWindow::writeSettings()
{

 QSettings lSettings(QSettings::NativeFormat, QSettings::UserScope,
 "", qApp->applicationName());
 lSettings.beginGroup("SETTINGS_GROUP_VIEW");
 lSettings.setValue("SETTING_SHOW_FileView", mViewSettings->isFileViewVisible());
 lSettings.setValue("SETTING_SHOW_RevisionTable", mViewSettings->isRevisionTableVisible());
 lSettings.setValue("SETTING_SHOW_Console", mViewSettings->isConsoleVisible());
 lSettings.setValue("SETTING_SHOW_HistoryTree", mViewSettings->isHistoryTreeVisible());
 lSettings.setValue("SETTING_SHOW_EditorView", mViewSettings->isEditorViewVisible());

}

void MainWindow::applySettings()
{
 ui->uiFileView->setVisible(mViewSettings->isFileViewVisible());
 ui->uiRevisionTable->setVisible(mViewSettings->isRevisionTableVisible());
 ui->uiConsole->setVisible(mViewSettings->isConsoleVisible());
 ui->uiHistoryTree->setVisible(mViewSettings->isHistoryTreeVisible());
 ui->uiEditorView->setVisible(mViewSettings->isEditorViewVisible());
}

void MainWindow::slotPreferencesAccepted()
{
 writeSettings();
 applySettings();
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