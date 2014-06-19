#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "revisionmodel.h"
#include <QGraphicsScene>

#include "view/revisiongrid.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    RevisionModel *model = new RevisionModel;
    ui->treeView->setModel(model);

    ui->graphicsView->setScene(new QGraphicsScene);

    RevisionGrid *grid = new RevisionGrid;
    ui->graphicsView->scene()->addItem(grid);

    grid->view(model->root());
}

MainWindow::~MainWindow()
{
    delete ui;
}
