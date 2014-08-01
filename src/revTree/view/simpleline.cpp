#include "simpleline.h"
#include "revisionnodeitem.h"
#include <QPainter>

SimpleLine::SimpleLine(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

QRectF SimpleLine::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void SimpleLine::paint(QPainter *painter, QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(mPen);
    painter->drawLine(boundingRect().topLeft(), boundingRect().bottomRight());
}

void SimpleLine::setPen(const QPen &pPen)
{
    mPen = pPen;
    update();
}

void SimpleLine::setLine(RevisionNodeItem *from, RevisionNodeItem *to)
{
    mSize.setWidth(qAbs(from->pos().x() - to->pos().x()));
    mSize.setHeight(qAbs(from->pos().y() - to->pos().y()));
    setPos(from->pos() + from->boundingRect().center());
}
