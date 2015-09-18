#include "revisiontreedock.h"
#include "ui_revisiontreedock.h"

RevisionTreeDock::RevisionTreeDock(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::RevisionTreeDock)
{
    ui->setupUi(this);
}

RevisionTreeDock::~RevisionTreeDock()
{
    delete ui;
}

DockType RevisionTreeDock::type() const
{
    return DockType::HistoryTree;
}
