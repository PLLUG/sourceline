#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "revisionmodel.h"
#include <QGraphicsScene>

#include "view/revisiongrid.h"
#include "revisiontablemodel.h"
#include "revisiondelegate.h"

#include "view/abstractgraphicsview.h"
#include "revisiontree.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    RevisionModel *model = new RevisionModel;

    //ui->graphicsView->setScene(new QGraphicsScene);
    /*RevisionTableModel *m = new RevisionTableModel;

//    RevisionGrid *grid = new RevisionGrid;
//    ui->graphicsView->installEventFilter(grid);
//    ui->graphicsView->scene()->addItem(grid);
//    AbstractGraphicsView *view = new AbstractGraphicsView;
//    view->setModel(m);

    //ui->graphicsView->scene()->addItem(view);

//    grid->view(model->root());

    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setMinimumSectionSize(1);
    ui->tableView->verticalHeader()->setMinimumSectionSize(1);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setModel(m);
    ui->tableView->setShowGrid(false);
    ui->tableView->setItemDelegateForColumn(0, new RevisionDelegate(this));*/
    ui->tableView->hide();

    tree = ui->widget->data()->createTree();
    updateBranchList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int i = index.row();
    tree->switchTo(tree->branches().at(i));
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty())
        return;
    tree->addCommit(ui->lineEdit->text());
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->lineEdit_2->text().isEmpty())
        return;
    tree->addBranch(ui->lineEdit_2->text());
    updateBranchList();
}

void MainWindow::updateBranchList()
{
    ui->listWidget->clear();
    for (int i = 0; i < tree->branches().size(); ++i)
    {
        ui->listWidget->addItem(tree->data(tree->branches().at(i), RevisionNode::IDR_DisplayRole).toString());
    }
}
