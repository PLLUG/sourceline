#include "genericdockwidget.h"
#include <QMessageBox>
#include <QTimer>

static const int INTERVAL = 1000; // 1 sec

GenericDockWidget::GenericDockWidget(QWidget *parent):
    QDockWidget(parent)
{
    mTimer = new QTimer(this);
    mTimer->setSingleShot(true);
    connect(mTimer, SIGNAL(timeout()), this, SIGNAL(dockSizeChanged()));

}

void GenericDockWidget::slotSetPage(int pPage)
{
    Q_UNUSED(pPage);
    //TASK: add implementation, make method virtual
}

void GenericDockWidget::reportDockChanged()
{
    mTimer->start(INTERVAL);
}

void GenericDockWidget::resizeEvent(QResizeEvent *pEvent)
{
    reportDockChanged();
    QDockWidget::resizeEvent(pEvent);
}
