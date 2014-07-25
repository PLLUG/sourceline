#include "revisiontable.h"
#include "ui_revisiontable.h"
#include "guidefs.h"

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

DockTypes::DockType RevisionTable::type() const
{
    return DockTypes::RevisionTable;
}

void RevisionTable::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
