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

void Bubble::setPen(const QPen &pPen)
{
    mPen = pPen;
    update();
}

void Bubble::paint(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
    Q_UNUSED(pOption)
    Q_UNUSED(pWidget)
    pPainter->setRenderHint(QPainter::Antialiasing);
    pPainter->setPen(Qt::NoPen);
    pPainter->setBrush(mPen.brush());
    pPainter->drawEllipse(boundingRect().center(), 3, 3);
    pPainter->setPen(mPen);
    pPainter->setBrush(Qt::NoBrush);
    pPainter->drawEllipse(boundingRect());
}

void Bubble::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit updateBubble();
    QGraphicsItem::mouseReleaseEvent(event);
}
