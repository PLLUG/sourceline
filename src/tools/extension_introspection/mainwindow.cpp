#include "clonecommand.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pluginloader.h"
#include "commandmanager.h"
#include "pluginapi.h"
#include "testcommand.h"
#include "aggregator.h"
#include "fileviewapi.h"
#include "invocationbased.h"
#include "publicfileviewapi.h"
#include "file_view/fileview.h"

/// MK: commit everything, merge to metaconnector-refactoring
/// MK: include fileview.pri
/// MM: create class FileViewAPI
///      * slot addToMenu(QString commandId)
///      * setCommandManager(CommandManager *)
/// MM: create new InvokationBased
///      * setTarget(FileViewAPI)
/// MM: create PublicFileViewAPI
///      * connect to InvokationBased (FileViewAPI)
///


/// MM: implement method CommandApi *CommandManager::command(QString commandID)
/// MM: add PublicFileViewAPI instance to Aggregare that will be passed to Command::init()
/// MM: add second command GitCloneCommand
///
///
/// MK: implement FileViewAPI::setFileView(FileView *)
///  MK: implement FileViewAPI::addToMenu(QString commandId)
///     * Create new QAction()
///     * get CommandApi instance by commandId
///     * set QAction text as commandId
///     * add QAction to FileView context menu (No selection)



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    FileView* lFileView = new FileView();
    setCentralWidget(lFileView);

    CommandManager *lCommandManager = new CommandManager();
    PluginAPI *lPluginAPI = new PluginAPI();

    connect(lCommandManager, &CommandManager::invokeCommand, lPluginAPI, &PluginAPI::slotInvokeCommand);

    TestCommand *lTestCommand = new TestCommand();
    lTestCommand->mName = "TestCommand";
    FileViewAPI *lFileViewAPI = new FileViewAPI();
    lFileViewAPI->setFileView(lFileView);
    lFileViewAPI->setCommandManeger(lCommandManager);

    InvocationBased *lInvocationBased = new InvocationBased();
    PublicFileViewAPI *lPublicFileViewAPI = new PublicFileViewAPI();
    lInvocationBased->setTarget(lFileViewAPI);

    connect(lPublicFileViewAPI, SIGNAL(invokeCommand(QByteArray,QVariant)), lInvocationBased, SLOT(invoke(QByteArray,QVariant)));
    connect(lPluginAPI, &PluginAPI::newCommandRegistered, lCommandManager, &CommandManager::slotCommandRegistered);

    Aggregator a;
    a.addObject(lPluginAPI);
    a.addObject(lPublicFileViewAPI);

    lTestCommand->init(a);
    CloneCommand *lGitTestCommand = new CloneCommand();
    lGitTestCommand->init(a);

    //lCommandManager->slotInvokeCommand("clone");
}

MainWindow::~MainWindow()
{
    delete ui;
}
