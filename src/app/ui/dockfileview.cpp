#include "dockfileview.h"
#include "ui_dockfileview.h"

DockFileView::DockFileView(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::DockFileView)
{
    ui->setupUi(this);
}

DockFileView::~DockFileView()
{
    delete ui;
}

DockTypes::DockType DockFileView::type() const
{
    return DockTypes::FileView;
}

void DockFileView::slotSetPage(int pPage)
{
}
