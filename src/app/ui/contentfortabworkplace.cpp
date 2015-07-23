#include "contentfortabworkplace.h"
#include "ui_contentfortabworkplace.h"
#include "components/console/consoleview.h"
#include "ui/dockconsole.h"
#include "ui/dockfileview.h"
#include "ui/editorview.h"
#include "ui/historytree.h"
#include "ui/revisiontable.h"
#include "ui/revisionview.h"
#include "../components/file_view/fileview.h"

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

    //COMMENT: Create DockWidget HistoryTree, set content for it and add this HistoryTree to ContentForTabWorkplace
    uiHistoryTree = new HistoryTree(this);
    uiHistoryTreeContents = new RevisionView(uiHistoryTree);
    uiHistoryTree->setWidget(uiHistoryTreeContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiHistoryTree);

    //COMMENT: Create DockWidget EditorView and add this EditorView to ContentForTabWorkplace
    uiEditorView = new EditorView(this);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiEditorView);

    //COMMENT: Create DockWidget DockFileView, set content for it and add this DockFileView to ContentForTabWorkplace
    uiFileView = new DockFileView(this);
    uiFileViewContents = new FileView(uiFileView);
    uiFileView->setWidget(uiFileViewContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), uiFileView);

    //COMMENT: Create DockWidget RevisionTable and add this RevisionTable to ContentForTabWorkplace
    uiRevisionTable = new RevisionTable(this);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiRevisionTable);

    //COMMENT: Create DockWidget DockConsole, set content for it and add this DockConsole to ContentForTabWorkplace
    uiConsole = new DockConsole(this);
    uiConsole->setLayoutDirection(Qt::LeftToRight);
    uiConsoleContents = new ConsoleView(uiConsole);
    uiConsole->setWidget(uiConsoleContents);
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
