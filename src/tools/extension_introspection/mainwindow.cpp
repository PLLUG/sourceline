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
    CommandManager *cm = new CommandManager();
    PluginAPI *papi = new PluginAPI();
    TestCommand *tc = new TestCommand();
    FileViewAPI *fvAPI = new FileViewAPI();
    InvocationBased *ib = new InvocationBased();
    PublicFileViewAPI *pfvAPI = new PublicFileViewAPI();
    ib->setTarget(fvAPI);

    connect(pfvAPI, SIGNAL(invokeCommand(QByteArray)), ib, SLOT(invoke(QByteArray,QVariant,QVariant,QVariant,QVariant,QVariant)));

    connect(papi, SIGNAL(newCommandRegistered(QString)), cm, SLOT(slotCommandRegistered(QString)));
    papi->slotRegisterCommand(tc);

    connect(cm, SIGNAL(invokeCommand(QString,QByteArray)), papi, SLOT(slotInvokeCommand(QString,QByteArray)));
    cm->slotInvokeCommand();

    Aggregator a;
    a.addObject(papi);
    tc->init(a);
}

MainWindow::~MainWindow()
{
    delete ui;
}
