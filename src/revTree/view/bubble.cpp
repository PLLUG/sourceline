#include "bubble.h"
#include "abstractrevisiondelegate.h"
#include <QPainter>
#include <QDebug>

Bubble::Bubble(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    prepareGeometryChange();
    mArea = QRectF(0, 0, 10, 10);

    setFlags(ItemIsMovable | ItemIsSelectable);
}

QRectF Bubble::boundingRect() const
{
    return QRectF(mArea.x() - 1, mArea.y() - 1, mArea.width() + 2, mArea.height() + 2);
}

void Bubble::setPen(const QPen &pen)
{
    mPen = pen;
    update();
}

void Bubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    painter->setBrush(mPen.brush());
    painter->drawEllipse(boundingRect().center(), 3, 3);
    painter->setPen(mPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(boundingRect());
}

void Bubble::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateBubble();
    QGraphicsItem::mouseReleaseEvent(event);
}
