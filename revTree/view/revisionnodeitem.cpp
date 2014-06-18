#include "revisionnodeitem.h"

RevisionNodeItem::RevisionNodeItem(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    mSize = QSize(20, 20);
}

QRectF RevisionNodeItem::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void RevisionNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //
}
