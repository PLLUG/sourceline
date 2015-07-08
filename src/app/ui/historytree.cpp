#include "historytree.h"
#include "ui_historytree.h"
#include "guidefs.h"

#include <QWidget>

HistoryTree::HistoryTree(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::HistoryTree)
{
    ui->setupUi(this);
}

HistoryTree::~HistoryTree()
{
    delete ui;
}

DockType HistoryTree::type() const
{
    return DockType::HistoryTree;
}

void HistoryTree::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
