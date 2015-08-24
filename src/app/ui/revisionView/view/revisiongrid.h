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

QT_FORWARD_DECLARE_CLASS(RevisionNode)
QT_FORWARD_DECLARE_CLASS(RevisionNodeItem)

class RevisionGrid : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    RevisionGrid();
    void setBoundingRect(const QSizeF pSize);
    void setBoundingRect(qreal pWidth, qreal pHeight);

    void view(RevisionNode *pRoot);

    QRectF boundingRect() const;

    QPoint startPoint() const;
    int gridStep() const;

    void drawText(const QString &pText, RevisionNodeItem *pItem);

protected:
    void paint(QPainter * pPainter, const QStyleOptionGraphicsItem * pOption, QWidget * pWidget = 0);
    bool eventFilter(QObject *obj, QEvent *event);

private:
    QSizeF mSize;
    RevisionNode *mRoot;
    QString mText;
    QPointF mTextPos;

    void drawNode(RevisionNode *pItem, int pCurrentCol);
    void drawLines(RevisionNode *pRoot);

    void drawBezier(RevisionNodeItem *pFrom, RevisionNodeItem *pTo);
    void drawLine(RevisionNodeItem *pFrom, RevisionNodeItem *pTo);
};

#endif // REVISIONGRID_H
