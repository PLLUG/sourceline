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

#include "revisionnodeitem.h"
#include "revisionnode.h"
#include "revisiongrid.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QStyleOptionGraphicsItem>

RevisionNodeItem::RevisionNodeItem(RevisionNode *dataNode, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    mData(dataNode)
{
    mSize = QSize(10, 10);
    setAcceptHoverEvents(true);
}

QRectF RevisionNodeItem::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void RevisionNodeItem::paintRevisionPoint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) const
{
    painter->setRenderHint(QPainter::Antialiasing);
    if ( option->state & QStyle::State_MouseOver )
    {
        painter->setBrush(QColor(255, 150, 150));
    }
    else
    {
        painter->setBrush(QColor(255, 0, 0));
    }
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(boundingRect().center(), 3, 3);
    painter->setBrush(Qt::NoBrush);
    painter->setPen(Qt::red);
    painter->drawEllipse(boundingRect());
}

void RevisionNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    paintRevisionPoint(painter, option, widget);
}

void RevisionNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    RevisionGrid *grid = dynamic_cast<RevisionGrid*>(parentItem());
    if ( grid )
        grid->drawText(mData->data(RevisionNode::IDR_DisplayRole).toString(), this);
}

void RevisionNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    RevisionGrid *grid = dynamic_cast<RevisionGrid*>(parentItem());
    if ( grid )
        grid->drawText(QString(), this);
}
