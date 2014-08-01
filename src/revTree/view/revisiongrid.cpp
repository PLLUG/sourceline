#include "revisiongrid.h"

#include <QPainter>
#include <QDebug>
#include <QWheelEvent>

RevisionGrid::RevisionGrid()
{
    mSize = QSizeF(250, 250);
//    setFlag(ItemIsMovable);
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

void RevisionGrid::drawText(const QString &txt, RevisionNodeItem *i)
{
    mText = txt;
    mTextPos = i->pos() + i->boundingRect().topRight();
    update();
}

void RevisionGrid::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(QColor(100, 100, 100)));
    painter->drawRoundedRect(boundingRect(), 5, 5);

    if ( !mText.isEmpty())
    {
        QFontMetricsF fm(painter->font());
        QRectF rect (mTextPos + QPointF(10, 0), QSizeF(fm.width(mText) + 5, fm.height() + 5));
        painter->setBrush(QColor(150, 150, 150));
        painter->drawRoundedRect(rect, 3, 3);
        painter->setPen(Qt::white);
        painter->drawText(rect, mText, QTextOption(Qt::AlignCenter));
    }
}

bool RevisionGrid::eventFilter(QObject *obj, QEvent *event)
{
    if ( event->type() == QEvent::Wheel)
    {
        QWheelEvent *e = dynamic_cast<QWheelEvent *>(event);
        static qreal sc = 1.0;
        if ( e->modifiers() & Qt::ControlModifier )
        {
            if ( e->delta() > 0 )
            {
                sc += 0.1;
            }
            else
            {
                sc -= 0.1;
            }
            setScale(sc);
            return true;
        }
    }
    return QObject::eventFilter(obj, event);
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
        if ( !node->branches.isEmpty() )
        {
            for (int i = 0; i < node->branches.size(); ++i)
            {
                RevisionNodeItem *it = new RevisionNodeItem(node->branches.at(i), this);
                node->branches.at(i)->graphicsItem = it;
                it->setPos(startPoint() + QPoint(currentColumn + gridStep() * (i+1), -currentRow));
                currentRow += gridStep();
            }
            for (int i = 0; i < node->branches.size(); ++i)
            {
                if ( node->branches.at(i)->child )
                    drawNode(node->branches.at(i)->child, currentCol + gridStep() * (i + 1));
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
        if ( next->mMergeTo )
        {
            drawBezier(next->graphicsItem, next->mMergeTo->graphicsItem);
        }
        if ( next->child )
        {
            drawLine(next->graphicsItem, next->child->graphicsItem);
            if ( !next->branches.isEmpty() )
            {
                for (int i = 0; i < next->branches.size(); ++i)
                {
                    drawBezier(next->graphicsItem, next->branches.at(i)->graphicsItem);
                    drawLines(next->branches.at(i));
                }
            }
            next = next->child;
        }
        else
        {
            if ( !next->branches.isEmpty() )
            {
                for (int i = 0; i < next->branches.size(); ++i)
                {
                    drawBezier(next->graphicsItem, next->branches.at(i)->graphicsItem);
                    drawLines(next->branches.at(i));
                }
            }
            break;
        }
    }
}

void RevisionGrid::drawBezier(RevisionNodeItem *from, RevisionNodeItem *to)
{
    QGraphicsPathItem *item = new QGraphicsPathItem(this);
    QPainterPath path;
    QRectF rect(from->pos() + from->boundingRect().center(), to->pos() + to->boundingRect().center());
    path.moveTo(rect.topLeft());
    QPointF c1 = QPointF(rect.bottomLeft().x(), rect.bottomLeft().y() - rect.height() - gridStep() * 0.7);
    QPointF c2 = rect.topRight();
    path.cubicTo(c1, c2, rect.bottomRight());
    item->setPen(QPen(Qt::red));
    item->setPath(path);

//    QGraphicsLineItem *line = new QGraphicsLineItem(this);
//    line->setLine(QLineF(c1, c2));
}

void RevisionGrid::drawLine(RevisionNodeItem *from, RevisionNodeItem *to)
{
    QGraphicsLineItem *line = new QGraphicsLineItem(this);
    line->setPen(QPen(Qt::red));
    line->setLine(QLineF(from->pos() + from->boundingRect().center(), to->pos() + to->boundingRect().center()));
}
