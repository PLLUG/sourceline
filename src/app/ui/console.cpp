#include "console.h"
#include "ui_console.h"
#include "guidefs.h"

Console::Console(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
}
Console::~Console()
{
    delete ui;
}

DockTypes::DockType Console::type() const
{
    return DockTypes::Console;
}

void Console::slotSetPage(int pPage)
{
    ui->label->setText("Page " + QString::number(pPage));
}
