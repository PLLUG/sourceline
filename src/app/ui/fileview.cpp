#include "fileview.h"
#include "ui_fileview.h"
#include "guidefs.h"

FileView::FileView(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);
    this->setVisible(true);
}

FileView::~FileView()
{
    delete ui;
}

DockTypes::DockType FileView::type() const
{
    return DockTypes::FileView;
}

void FileView::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
