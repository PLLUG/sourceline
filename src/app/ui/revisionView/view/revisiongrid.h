/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Volodymyr Kochyn  (vovakochyn@gmail.com)                      ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#ifndef REVISIONGRID_H
#define REVISIONGRID_H

#include <QGraphicsItem>
#include "revisionnodeitem.h"
#include "../revisionnode.h"

class RevisionGrid : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    RevisionGrid();
    void setBoundingRect(const QSizeF size);
    void setBoundingRect(qreal w, qreal h);

    void view(RevisionNode *root);

    QRectF boundingRect() const;

    QPoint startPoint() const;
    int gridStep() const;

    void drawText(const QString &txt, RevisionNodeItem *i);

protected:
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QSizeF mSize;
    RevisionNode *mRoot;
    QString mText;
    QPointF mTextPos;

    void drawNode(RevisionNode *item, int currentCol);
    void drawLines(RevisionNode *root);

    void drawBezier(RevisionNodeItem *from, RevisionNodeItem *to);
    void drawLine(RevisionNodeItem *from, RevisionNodeItem *to);
};

#endif // REVISIONGRID_H
