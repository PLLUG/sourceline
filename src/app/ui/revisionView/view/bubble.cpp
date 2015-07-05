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

#include "bubble.h"
#include "abstractrevisiondelegate.h"
#include "../parameters.h"
#include <QPainter>
#include <QDebug>

Bubble::Bubble(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
    prepareGeometryChange();
    mArea = Parameters::bubbleRect();

    setFlags(ItemIsMovable | ItemIsSelectable);
}

QRectF Bubble::boundingRect() const
{
    return QRectF(mArea.x() - 1, mArea.y() - 1, mArea.width() + 2, mArea.height() + 2);
}

void Bubble::setPen(const QPen &pen)
{
    mPen = pen;
    update();
}

void Bubble::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    painter->setBrush(mPen.brush());
    painter->drawEllipse(boundingRect().center(), 3, 3);
    painter->setPen(mPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(boundingRect());
}

void Bubble::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateBubble();
    QGraphicsItem::mouseReleaseEvent(event);
}
