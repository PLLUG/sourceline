#include "historytree.h"
#include "ui_historytree.h"

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

DockTypes::DockType HistoryTree::type() const
{
    return DockTypes::DockType::HistoryTree;
}

void HistoryTree::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
