#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "revisionmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RevisionModel *model = new RevisionModel;
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}
