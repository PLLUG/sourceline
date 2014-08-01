#include "abstractgraphicsview.h"
#include "abstractrevisiondelegate.h"
#include <QPainter>
#include <QAbstractItemModel>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

AbstractGraphicsView::AbstractGraphicsView()
{
    mSize = QSizeF(150, 150);
    setFlag(ItemClipsChildrenToShape);
}

AbstractGraphicsView::~AbstractGraphicsView()
{
    delete mModel;
}

QRectF AbstractGraphicsView::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

QRectF AbstractGraphicsView::rect() const
{
    return childrenBoundingRect();
}

void AbstractGraphicsView::setSize(qreal width, qreal height)
{
    setSize(QSizeF(width, height));
}

void AbstractGraphicsView::setSize(const QSizeF &size)
{
    prepareGeometryChange();
    mSize = size;
    updateGeometry();
}

void AbstractGraphicsView::setItemDelegate(AbstractRevisionDelegate *item)
{
    //
}

void AbstractGraphicsView::setModel(QAbstractItemModel *model)
{
    mModel = model;
    connect(mModel, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(slotModelChanged()));
    initModelData();
    updateGeometry();
}

void AbstractGraphicsView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(150, 150, 150));
    painter->drawRect(boundingRect());
}

void AbstractGraphicsView::initModelData()
{
    if ( mModel )
    {
        qDeleteAll(mItems);
        mItems.clear();
        AbstractRevisionDelegate *temp;
        for (int i = 0; i < mModel->rowCount(); ++i)
        {
            temp = new AbstractRevisionDelegate(this);
            mItems.append(temp);
            temp->setData(AbstractRevisionDelegate::DR_Drawing, mModel->data(mModel->index(i, 0), Qt::DisplayRole));
            temp->setData(AbstractRevisionDelegate::DR_Text, mModel->data(mModel->index(i, 2), Qt::DisplayRole));
            temp->setData(AbstractRevisionDelegate::DR_Id, mModel->data(mModel->index(i, 1), Qt::DisplayRole));
            connect(temp, SIGNAL(needRequestFromView(AbstractRevisionDelegate*)),
                    this, SLOT(slotRequestForItem(AbstractRevisionDelegate *)));
        }
    }
}

QRectF AbstractGraphicsView::resizeRect() const
{
    return QRectF (boundingRect().bottomRight() + QPointF(-20, -20), boundingRect().bottomRight());
}

void AbstractGraphicsView::slotRequestForItem(AbstractRevisionDelegate *item)
{
    for (int i = 1; i < mItems.size(); ++i)
    {
        if ( mItems.at(i) == item )
        {
            item->setPreviousState(QPointF(0, i * mItems.at(i - 1)->boundingRect().height()) + QPointF(0, 2 * i));
            break;
        }
    }
}

void AbstractGraphicsView::slotModelChanged()
{
    initModelData();
    updateGeometry();
}

ModelIndex AbstractGraphicsView::createIndex(int row, int column)
{
    return ModelIndex(row, column);
}

void AbstractGraphicsView::updateGeometry()
{
    if ( !mItems.isEmpty() )
    {
        mItems.first()->setSize(mSize.width(), 21);
        mItems.first()->setPos(0, 0);
        for (int i = 1; i < mItems.size(); ++i)
        {
            mItems[i]->setSize(mSize.width(), 21);
            mItems[i]->setPos(mItems[i - 1]->pos() + mItems[i-1]->boundingRect().bottomLeft() + QPointF(0, 2));
        }
    }
}
