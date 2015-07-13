#include "contentfortabworkplace.h"
#include "ui_contentfortabworkplace.h"

ContentForTabWorkplace::ContentForTabWorkplace(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentForTabWorkplace)
{
    ui->setupUi(this);    
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);
    setMouseTracking(false);
    setAutoFillBackground(false);
    setDockNestingEnabled(true);
    setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);

    uiHistoryTree = new HistoryTree(this);
    uiHistoryTree->setMinimumSize(QSize(250, 38));

    dockWidgetContents_5 = new RevisionView();
    uiHistoryTree->setWidget(dockWidgetContents_5);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiHistoryTree);


    uiEditorView = new EditorView(this);
    uiEditorView->setMinimumSize(QSize(461, 38));
    dockWidgetContents = new QWidget();
    uiEditorView->setWidget(dockWidgetContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiEditorView);


    uiFileView = new DockFileView(this);
    sizePolicy.setHeightForWidth(uiFileView->sizePolicy().hasHeightForWidth());
    uiFileView->setSizePolicy(sizePolicy);
    uiFileView->setMinimumSize(QSize(250, 38));
    uiFileView->setBaseSize(QSize(500, 370));
    uiFileView->setFloating(false);    
    dockWidgetContents_4 = new FileView();
    uiFileView->setWidget(dockWidgetContents_4);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), uiFileView);

    uiRevisionTable = new RevisionTable(this);
    uiRevisionTable->setMinimumSize(QSize(461, 38));
    dockWidgetContents_8 = new QWidget();
    uiRevisionTable->setWidget(dockWidgetContents_8);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiRevisionTable);


    uiConsole = new DockConsole(this);
    uiConsole->setMinimumSize(QSize(461, 38));
    uiConsole->setLayoutDirection(Qt::LeftToRight);
    dockWidgetContents_3 = new ConsoleView();
    uiConsole->setWidget(dockWidgetContents_3);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiConsole);

    splitDockWidget(uiRevisionTable, uiEditorView, Qt::Horizontal);
    splitDockWidget(uiEditorView, uiConsole, Qt::Vertical);
    tabifyDockWidget(uiEditorView, uiFileView);
    tabifyDockWidget(uiRevisionTable, uiHistoryTree);
}

ContentForTabWorkplace::~ContentForTabWorkplace()
{
    delete ui;
}
