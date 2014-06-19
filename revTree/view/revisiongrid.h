#ifndef REVISIONGRID_H
#define REVISIONGRID_H

#include <QGraphicsItem>
#include "revisionnodeitem.h"
#include "revisionnode.h"

class RevisionGrid : public QGraphicsItem
{
public:
    RevisionGrid();
    void setBoundingRect(const QSizeF size);
    void setBoundingRect(qreal w, qreal h);

    void view(RevisionNode *root);

    QRectF boundingRect() const;

    QPoint startPoint() const;
    int gridStep() const;

    void drawText(const QString &txt, const QPointF &pos);

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

private:
    QSizeF mSize;
    RevisionNode *mRoot;
    QString mText;
    QPointF mTextPos;

    void drawItems(const QList<RevisionNode *> &items, int currentCol);

};

#endif // REVISIONGRID_H
