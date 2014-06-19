#ifndef REVISIONNODEITEM_H
#define REVISIONNODEITEM_H

#include <QGraphicsItem>

class RevisionNode;

class RevisionNodeItem : public QGraphicsItem/*, public RevisionNode*/
{
public:
    RevisionNodeItem(RevisionNode *dataNode, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void addChild(RevisionNodeItem *child);

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    QSizeF mSize;
    RevisionNode *mData;
    QList<RevisionNodeItem *> mChildren;
};

#endif // REVISIONNODEITEM_H
