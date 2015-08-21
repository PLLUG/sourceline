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

#include "simpleline.h"
#include "revisionnodeitem.h"
#include <QPainter>

SimpleLine::SimpleLine(QGraphicsItem *parent) :
    QGraphicsItem(parent)
{
}

QRectF SimpleLine::boundingRect() const
{
    return QRectF(0, 0, mSize.width(), mSize.height());
}

void SimpleLine::paint(QPainter *pPainter, QStyleOptionGraphicsItem *pOption, QWidget *pWidget)
{
    Q_UNUSED(pOption)
    Q_UNUSED(pWidget)
    pPainter->setRenderHint(QPainter::Antialiasing);
    pPainter->setPen(mPen);
    pPainter->drawLine(boundingRect().topLeft(), boundingRect().bottomRight());
}

void SimpleLine::setPen(const QPen &pPen)
{
    mPen = pPen;
    update();
}

void SimpleLine::setLine(RevisionNodeItem *pFrom, RevisionNodeItem *pTo)
{
    mSize.setWidth(qAbs(pFrom->pos().x() - pTo->pos().x()));
    mSize.setHeight(qAbs(pFrom->pos().y() - pTo->pos().y()));
    setPos(pFrom->pos() + pFrom->boundingRect().center());
}
