#include "revisionwidget.h"
#include "ui_revisionwidget.h"

#include "view/abstractgraphicsview.h"

#include <QResizeEvent>
#include <QDebug>

RevisionWidget::RevisionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RevisionWidget),
    mView(0)
{
    ui->setupUi(this);
    mScene = new QGraphicsScene;
    ui->graphicsView->setScene(mScene);

    mView = new AbstractGraphicsView;
    mModel = new RevisionTableModel;
    mView->setModel(mModel);
    mScene->addItem(mView);

    connect(mView, SIGNAL(updateUI()), this, SLOT(updateUI()));
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
    updateUI();
    QWidget::resizeEvent(event);
}

void RevisionWidget::updateUI()
{
    QRect rect = ui->graphicsView->rect();
    if ( rect.height() > mView->rect().height() )
    {
        mView->setSize(QSizeF(rect.width() - 2, rect.height() - 2));
        mScene->setSceneRect(mView->boundingRect());
    }
    else
    {
        mView->setSize(QSizeF(rect.width() - 20, mView->boundingRect().height()));
        mScene->setSceneRect(mView->rect());
    }
}
