#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "invocationbased.h"
#include "remoteapiprovider.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mApiProvider(new RemoteApiProvider(this))
{
    ui->setupUi(this);

    InvocationBased *textInvoker = new InvocationBased;
    textInvoker->setTarget(ui->plainTextEdit);
    mApiProvider->addApiProvider(textInvoker);
//    connect(mApiProvider, &RemoteApiProvider::invoked, textInvoker, &InvocationBased::invoke, Qt::UniqueConnection);
    mApiProvider->listen("sl");
//    textInvoker->invoke("appendPlainText(QString)", QString("Hello Meta!"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
