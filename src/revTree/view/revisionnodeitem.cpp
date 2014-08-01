#include "revisionnodeitem.h"
#include "revisionnode.h"
#include "revisiongrid.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QStyleOptionGraphicsItem>

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

void RevisionNodeItem::paintRevisionPoint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    if ( option->state & QStyle::State_MouseOver )
    {
        painter->setBrush(QColor(255, 150, 150));
    }
    else
    {
        painter->setBrush(QColor(255, 0, 0));
    }
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect().center(), 3, 3);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
}

void RevisionNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintRevisionPoint(painter, option, widget);
}

void RevisionNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    RevisionGrid *grid = dynamic_cast<RevisionGrid*>(parentItem());
    if ( grid )
        grid->drawText(mData->data(RevisionNode::IDR_DisplayRole).toString(), this);
}

void RevisionNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    RevisionGrid *grid = dynamic_cast<RevisionGrid*>(parentItem());
    if ( grid )
        grid->drawText(QString(), this);
}
