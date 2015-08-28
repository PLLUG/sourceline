#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pluginloader.h"
#include "commandmanager.h"
#include "pluginapi.h"
#include "testcommand.h"
#include "aggregator.h"

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
///
///
///
///

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CommandManager *cm = new CommandManager();
    PluginAPI *papi = new PluginAPI();
    TestCommand *tc = new TestCommand();
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
