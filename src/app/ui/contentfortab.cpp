#include "contentfortab.h"
#include "ui_contentfortab.h"
#include "components/console/consoleview.h"
#include "ui/dockconsole.h"
#include "ui/dockfileview.h"
#include "ui/editorview.h"
#include "ui/historytree.h"
#include "ui/revisiontable.h"
#include "ui/revisionview.h"
#include "../components/file_view/fileview.h"

ContentForTab::ContentForTab(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ContentForTab)
{
    ui->setupUi(this);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);
    setMouseTracking(false);
    setAutoFillBackground(false);
    setDockNestingEnabled(true);
    setDockOptions(QMainWindow::AllowNestedDocks
                   |QMainWindow::AllowTabbedDocks
                   |QMainWindow::AnimatedDocks);

    //COMMENT: Create DockWidget HistoryTree, set content for it and add this HistoryTree to ContentForTabWorkplace
    mHistoryTree = new HistoryTree(this);
    mHistoryTreeContents = new RevisionView(mHistoryTree);
    mHistoryTree->setWidget(mHistoryTreeContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), mHistoryTree);

    //COMMENT: Create DockWidget EditorView and add this EditorView to ContentForTabWorkplace
    mEditorView = new EditorView(this);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), mEditorView);

    //COMMENT: Create DockWidget DockFileView, set content for it and add this DockFileView to ContentForTabWorkplace
    mFileView = new DockFileView(this);
    mFileViewContents = new FileView(mFileView);
    mFileView->setWidget(mFileViewContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), mFileView);

    //COMMENT: Create DockWidget RevisionTable and add this RevisionTable to ContentForTabWorkplace
    mRevisionTable = new RevisionTable(this);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), mRevisionTable);

    //COMMENT: Create DockWidget DockConsole, set content for it and add this DockConsole to ContentForTabWorkplace
    mConsole = new DockConsole(this);
    mConsole->setLayoutDirection(Qt::LeftToRight);
    mConsoleContents = new ConsoleView(mConsole);
    mConsole->setWidget(mConsoleContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), mConsole);

    splitDockWidget(mRevisionTable, mEditorView, Qt::Horizontal);
    splitDockWidget(mEditorView, mConsole, Qt::Vertical);
    tabifyDockWidget(mEditorView, mFileView);
    tabifyDockWidget(mRevisionTable, mHistoryTree);
}

ContentForTab::~ContentForTab()
{
    delete ui;
}
