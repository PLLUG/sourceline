#include "revisiongrid.h"

#include <QPainter>

RevisionGrid::RevisionGrid()
{
    mSize = QSizeF(250, 250);
}

void RevisionGrid::setBoundingRect(const QSizeF size)
{
    prepareGeometryChange();
    mSize = size;
}

void RevisionGrid::setBoundingRect(qreal w, qreal h)
{
    setBoundingRect(QSizeF(w, h));
}

void RevisionGrid::view(RevisionNode *root)
{
    mRoot = root;
    drawItems(mRoot->children, gridStep());
}

QRectF RevisionGrid::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

QPoint RevisionGrid::startPoint() const
{
    return boundingRect().bottomLeft().toPoint();
}

int RevisionGrid::gridStep() const
{
    return 20;
}

void RevisionGrid::drawText(const QString &txt, const QPointF &pos)
{
    mText = txt;
    mTextPos = pos;
    update();
}

void RevisionGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(100, 100, 100)));
    painter->drawRoundedRect(boundingRect(), 6, 6);

    if ( !mText.isEmpty())
    {
        QFontMetricsF fm(painter->font());
        QRectF rect (mTextPos + QPointF(0, -fm.height() - 5), QSizeF(fm.width(mText), fm.height()));
        painter->setBrush(QColor(150, 150, 150));
        painter->drawRoundedRect(rect, 3, 3);
        painter->setPen(Qt::white);
        painter->drawText(rect, mText);
    }
}

void RevisionGrid::drawItems(const QList<RevisionNode *> &items, int currentCol)
{
    static int currentRow = gridStep();
    int currentColumn = currentCol;
    for (int i = 0; i < items.size(); ++i)
    {
        RevisionNodeItem *it = new RevisionNodeItem(items.at(i), this);
        it->setPos(startPoint() + QPoint(currentColumn, -currentRow));
        currentRow += gridStep();
        if ( !items.at(i)->children.isEmpty() )
        {
            drawItems(items.at(i)->children, currentCol + gridStep());
        }
    }
}
