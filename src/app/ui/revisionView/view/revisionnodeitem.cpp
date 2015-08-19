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
#include "../revisionnode.h"
#include "revisiongrid.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneHoverEvent>
#include <QStyleOptionGraphicsItem>

RevisionNodeItem::RevisionNodeItem(RevisionNode *pDataNode, QGraphicsItem *parent) :
    QGraphicsItem(parent),
    mData(pDataNode)
{
    mSize = QSize(10, 10);
    setAcceptHoverEvents(true);
}

QRectF RevisionNodeItem::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void RevisionNodeItem::paintRevisionPoint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *) const
{
    pPainter->setRenderHint(QPainter::Antialiasing);
    if (pOption->state & QStyle::State_MouseOver)
    {
        pPainter->setBrush(QColor(255, 150, 150));
    }
    else
    {
        pPainter->setBrush(QColor(255, 0, 0));
    }
    pPainter->setPen(Qt::NoPen);
    pPainter->drawEllipse(boundingRect().center(), 3, 3);
    pPainter->setBrush(Qt::NoBrush);
    pPainter->setPen(Qt::red);
    pPainter->drawEllipse(boundingRect());
}

void RevisionNodeItem::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
    paintRevisionPoint(pPainter, pOption, pWidget);
}

void RevisionNodeItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    RevisionGrid *lGrid = dynamic_cast<RevisionGrid*>(parentItem());
    if (lGrid)
    {
        lGrid->drawText(mData->data(RevisionNode::IDR_DisplayRole).toString(), this);
    }
}

void RevisionNodeItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    RevisionGrid *lGrid = dynamic_cast<RevisionGrid*>(parentItem());
    if (lGrid)
    {
        lGrid->drawText(QString(), this);
    }
}
