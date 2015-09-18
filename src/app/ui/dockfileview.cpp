#include "dockfileview.h"
#include "ui_dockfileview.h"

#include <QWidget>

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

DockType DockFileView::type() const
{
    return DockType::FileView;
}

void DockFileView::slotSetPage(int pPage)
{
    Q_UNUSED(pPage)
}
