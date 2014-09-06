#include "dockconsole.h"
#include "ui_dockconsole.h"
#include "guidefs.h"

DockConsole::DockConsole(QWidget *parent) :
    GenericDockWidget(parent),
    ui(new Ui::DockConsole)
{
    ui->setupUi(this);
}
DockConsole::~DockConsole()
{
    delete ui;
}

DockTypes::DockType DockConsole::type() const
{
    return DockTypes::Console;
}

void DockConsole::slotSetPage(int pPage)
{
}
