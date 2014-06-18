#ifndef REVISIONNODEITEM_H
#define REVISIONNODEITEM_H

#include <QGraphicsItem>

class RevisionNodeItem : public QGraphicsItem
{
public:
    RevisionNodeItem(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:
    QSizeF mSize;
};

#endif // REVISIONNODEITEM_H
