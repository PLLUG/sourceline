#include "revisiongrid.h"

#include <QPainter>
#include <QDebug>

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
    drawNode(mRoot, gridStep());
    drawLines(root);
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

void RevisionGrid::drawNode(RevisionNode *item, int currentCol)
{
    static int currentRow = gridStep();
    int currentColumn = currentCol;
    RevisionNode *node = item;
    while ( node != 0 )
    {
        RevisionNodeItem *it = new RevisionNodeItem(node, this);
        node->graphicsItem = it;
        it->setPos(startPoint() + QPoint(currentColumn, -currentRow));
        currentRow += gridStep();
        if ( !node->children.isEmpty() )
        {
            for (int i = 0; i < node->children.size(); ++i)
            {
                drawNode(node->children.at(i), currentCol + gridStep());
            }
        }
        node = node->child;
    }
}

void RevisionGrid::drawLines(RevisionNode *root)
{
    RevisionNode *next = root;
    while ( next )
    {
        if ( next->child )
        {
            drawLine(next->graphicsItem, next->child->graphicsItem);
            if ( !next->children.isEmpty() )
            {
                drawLine(next->graphicsItem, next->children.first()->graphicsItem);
                drawLines(next->children.first());
            }
            next = next->child;
        }
        else
        {
            if ( !next->children.isEmpty() )
            {
                drawLine(next->graphicsItem, next->children.first()->graphicsItem);
                drawLines(next->children.first());
            }
            break;
        }
    }
}

void RevisionGrid::drawLine(RevisionNodeItem *from, RevisionNodeItem *to)
{
    QGraphicsLineItem *line = new QGraphicsLineItem(this);
    line->setPen(QPen(Qt::red));
    line->setLine(QLineF(from->pos() + from->boundingRect().center(), to->pos() + to->boundingRect().center()));
}
