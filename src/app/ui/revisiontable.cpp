#include "revisiontable.h"
#include "ui_revisiontable.h"
#include "guidefs.h"

#include <QWidget>

RevisionTable::RevisionTable(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::RevisionTable)
{
    ui->setupUi(this);
}

RevisionTable::~RevisionTable()
{
    delete ui;
}

DockType RevisionTable::type() const
{
    return DockType::RevisionTable;
}

void RevisionTable::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
