/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "console.h"
#include "editorview.h"
#include "fileview.h"
#include "historytree.h"
#include "revisiontable.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QAction *actionOpen;
    QAction *actionAbout_SourceLine;
    QAction *actionSettings;
    QAction *actionAdd_Page;
    QAction *actionPlugin_Settings;
    QWidget *centralWidget;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    HistoryTree *uiHistoryTree;
    QWidget *dockWidgetContents_5;
    EditorView *uiEditorView;
    QWidget *dockWidgetContents;
    FileView *uiFileView;
    QWidget *dockWidgetContents_4;
    QToolBar *uiTabToolBar;
    RevisionTable *uiRevisionTable;
    QWidget *dockWidgetContents_8;
    Console *uiConsole;
    QWidget *dockWidgetContents_3;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(729, 552);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMouseTracking(false);
        MainWindow->setAutoFillBackground(false);
        MainWindow->setDockNestingEnabled(true);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/splash/img/folder_open.png"), QSize(), QIcon::Normal, QIcon::On);
        actionOpen->setIcon(icon);
        actionAbout_SourceLine = new QAction(MainWindow);
        actionAbout_SourceLine->setObjectName(QStringLiteral("actionAbout_SourceLine"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionAdd_Page = new QAction(MainWindow);
        actionAdd_Page->setObjectName(QStringLiteral("actionAdd_Page"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/splash/img/addIcon.png"), QSize(), QIcon::Normal, QIcon::On);
        actionAdd_Page->setIcon(icon1);
        actionPlugin_Settings = new QAction(MainWindow);
        actionPlugin_Settings->setObjectName(QStringLiteral("actionPlugin_Settings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        uiHistoryTree = new HistoryTree(MainWindow);
        uiHistoryTree->setObjectName(QStringLiteral("uiHistoryTree"));
        uiHistoryTree->setMinimumSize(QSize(250, 38));
        dockWidgetContents_5 = new QWidget();
        dockWidgetContents_5->setObjectName(QStringLiteral("dockWidgetContents_5"));
        uiHistoryTree->setWidget(dockWidgetContents_5);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiHistoryTree);
        uiEditorView = new EditorView(MainWindow);
        uiEditorView->setObjectName(QStringLiteral("uiEditorView"));
        uiEditorView->setMinimumSize(QSize(461, 38));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        uiEditorView->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiEditorView);
        uiFileView = new FileView(MainWindow);
        uiFileView->setObjectName(QStringLiteral("uiFileView"));
        sizePolicy.setHeightForWidth(uiFileView->sizePolicy().hasHeightForWidth());
        uiFileView->setSizePolicy(sizePolicy);
        uiFileView->setMinimumSize(QSize(250, 38));
        uiFileView->setBaseSize(QSize(280, 370));
        uiFileView->setFloating(false);
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QStringLiteral("dockWidgetContents_4"));
        uiFileView->setWidget(dockWidgetContents_4);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(1), uiFileView);
        uiTabToolBar = new QToolBar(MainWindow);
        uiTabToolBar->setObjectName(QStringLiteral("uiTabToolBar"));
        uiTabToolBar->setMinimumSize(QSize(0, 28));
        uiTabToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, uiTabToolBar);
        MainWindow->insertToolBarBreak(uiTabToolBar);
        uiRevisionTable = new RevisionTable(MainWindow);
        uiRevisionTable->setObjectName(QStringLiteral("uiRevisionTable"));
        uiRevisionTable->setMinimumSize(QSize(461, 38));
        dockWidgetContents_8 = new QWidget();
        dockWidgetContents_8->setObjectName(QStringLiteral("dockWidgetContents_8"));
        uiRevisionTable->setWidget(dockWidgetContents_8);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiRevisionTable);
        uiConsole = new Console(MainWindow);
        uiConsole->setObjectName(QStringLiteral("uiConsole"));
        uiConsole->setMinimumSize(QSize(461, 38));
        uiConsole->setLayoutDirection(Qt::LeftToRight);
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QStringLiteral("dockWidgetContents_3"));
        uiConsole->setWidget(dockWidgetContents_3);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiConsole);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 729, 21));
        MainWindow->setMenuBar(menuBar);

        toolBar->addAction(actionOpen);
        toolBar->addAction(actionAdd_Page);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionClose->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionAbout_SourceLine->setText(QApplication::translate("MainWindow", "About SourceLine...", 0));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings", 0));
        actionAdd_Page->setText(QApplication::translate("MainWindow", "Add Page", 0));
        actionPlugin_Settings->setText(QApplication::translate("MainWindow", "Plugin Settings...", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
        uiTabToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar_2", 0));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
