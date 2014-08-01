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

#ifndef ABSTRACTGRAPHICSVIEW_H
#define ABSTRACTGRAPHICSVIEW_H

#include <QGraphicsItem>
#include <QObject>
#include "modelindex.h"

QT_FORWARD_DECLARE_CLASS (AbstractRevisionDelegate)
QT_FORWARD_DECLARE_CLASS (QAbstractItemModel)

class AbstractGraphicsView : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    AbstractGraphicsView();
    ~AbstractGraphicsView();
    QRectF boundingRect() const;
    QRectF rect() const;
    void setSize(qreal width, qreal height);
    void setSize(const QSizeF &size);

    void setItemDelegate(AbstractRevisionDelegate *item);
    virtual void setModel(QAbstractItemModel *model);

protected:
    virtual ModelIndex createIndex(int row, int column);
    virtual void updateGeometry();

private:
    QSizeF mSize;
    QList<AbstractRevisionDelegate *> mItems;
    QList<AbstractRevisionDelegate *>::iterator mItemIterator;
    QAbstractItemModel *mModel;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void initModelData();
    QRectF resizeRect() const;

private slots:
    void slotRequestForItem(AbstractRevisionDelegate *item);
    void slotModelChanged();
};

#endif // ABSTRACTGRAPHICSVIEW_H
