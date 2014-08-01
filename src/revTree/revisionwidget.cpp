#include "revisionwidget.h"
#include "ui_revisionwidget.h"

#include "view/abstractgraphicsview.h"

#include <QResizeEvent>
#include <QDebug>

RevisionWidget::RevisionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RevisionWidget)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene;
    ui->graphicsView->setScene(mScene);

    mView = new AbstractGraphicsView;
    mModel = new RevisionTableModel;
    mView->setModel(mModel);
    mScene->addItem(mView);
}

RevisionWidget::~RevisionWidget()
{
    delete ui;
}

RevisionTableModel *RevisionWidget::data() const
{
    return mModel;
}

void RevisionWidget::resizeEvent(QResizeEvent *event)
{
    QRect rect = ui->graphicsView->rect();
    if ( rect.height() > mView->rect().height() )
    {
        mView->setSize(QSizeF(rect.width() - 2, rect.height() - 2));
        mScene->setSceneRect(mView->boundingRect());
    }
    else
    {
        mView->setSize(QSizeF(rect.width() - 18, mView->rect().height()));
        mScene->setSceneRect(mView->rect());
    }
    QWidget::resizeEvent(event);
}
