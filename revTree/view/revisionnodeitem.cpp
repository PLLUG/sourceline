#include "revisionnodeitem.h"
#include "revisionnode.h"
#include "revisiongrid.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>

RevisionNodeItem::RevisionNodeItem(RevisionNode *dataNode, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    mData(dataNode)
{
    mSize = QSize(10, 10);
    setAcceptHoverEvents(true);
}

QRectF RevisionNodeItem::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void RevisionNodeItem::addChild(RevisionNodeItem *child)
{
    //
}

void RevisionNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::red);

    painter->setBrush(QColor(255, 0, 0));
    painter->drawEllipse(boundingRect().center(), 3, 3);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(boundingRect());
}

void RevisionNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    RevisionGrid *grid = dynamic_cast<RevisionGrid*>(parentItem());
    if ( grid )
        grid->drawText(mData->message(), mapToParent(event->pos()));
}

void RevisionNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    RevisionGrid *grid = dynamic_cast<RevisionGrid*>(parentItem());
    if ( grid )
        grid->drawText(QString(), mapToParent(event->pos()));
}
