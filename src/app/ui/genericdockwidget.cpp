#include "genericdockwidget.h"
#include <QMessageBox>

GenericDockWidget::GenericDockWidget(QWidget *parent):
    QDockWidget(parent)
{

}

void GenericDockWidget::addPage(int pIndex, QWidget *pWidget)
{
    Q_UNUSED(pIndex);
    Q_UNUSED(pWidget);
}

void GenericDockWidget::slotSetPage(int pPage)
{
    Q_UNUSED(pPage);
    //TASK: add implementation, make method virtual
}
