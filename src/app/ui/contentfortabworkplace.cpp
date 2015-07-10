#include "contentfortabworkplace.h"
#include "ui_contentfortabworkplace.h"

ContentForTabWorkplace::ContentForTabWorkplace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentForTabWorkplace)
{
    ui->setupUi(this);

    //this->resize(729, 552);
    QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy.setHeightForWidth(this->sizePolicy().hasHeightForWidth());
    this->setSizePolicy(sizePolicy);
    this->setMouseTracking(false);
    this->setAutoFillBackground(false);
    this->setDockNestingEnabled(true);
    this->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);

    uiHistoryTree = new HistoryTree(this);
    uiHistoryTree->setMinimumSize(QSize(250, 38));
    dockWidgetContents_5 = new RevisionView();
    uiHistoryTree->setWidget(dockWidgetContents_5);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiHistoryTree);


    uiEditorView = new EditorView(this);
    uiEditorView->setMinimumSize(QSize(461, 38));
    dockWidgetContents = new QWidget();
    uiEditorView->setWidget(dockWidgetContents);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiEditorView);


    uiFileView = new DockFileView(this);
    sizePolicy.setHeightForWidth(uiFileView->sizePolicy().hasHeightForWidth());
    uiFileView->setSizePolicy(sizePolicy);
    uiFileView->setMinimumSize(QSize(250, 38));
    uiFileView->setBaseSize(QSize(500, 370));
    uiFileView->setFloating(false);
    dockWidgetContents_4 = new FileView();
    uiFileView->setWidget(dockWidgetContents_4);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(1), uiFileView);

    uiRevisionTable = new RevisionTable(this);
    uiRevisionTable->setMinimumSize(QSize(461, 38));
    dockWidgetContents_8 = new QWidget();
    uiRevisionTable->setWidget(dockWidgetContents_8);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiRevisionTable);


    uiConsole = new DockConsole(this);
    uiConsole->setMinimumSize(QSize(461, 38));
    uiConsole->setLayoutDirection(Qt::LeftToRight);
    dockWidgetContents_3 = new ConsoleView();
    uiConsole->setWidget(dockWidgetContents_3);
    this->addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiConsole);

    this->splitDockWidget(uiRevisionTable, uiEditorView, Qt::Horizontal);
    this->splitDockWidget(uiEditorView, uiConsole, Qt::Vertical);
    this->tabifyDockWidget(uiEditorView, uiFileView);
    this->tabifyDockWidget(uiRevisionTable, uiHistoryTree);

}

ContentForTabWorkplace::~ContentForTabWorkplace()
{
    delete ui;
}
