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

#ifndef SIMPLELINE_H
#define SIMPLELINE_H

#include <QGraphicsItem>
#include <QPen>

class RevisionNodeItem;

class SimpleLine : public QGraphicsItem
{
public:
    SimpleLine(QGraphicsItem *parent = 0);

    QRectF boundingRect() const;
    void paint( QPainter *painter, QStyleOptionGraphicsItem *option, QWidget *widget );

    void setPen(const QPen &pPen);

    void setLine(RevisionNodeItem *from, RevisionNodeItem *to);

private:
    QSizeF mSize;
    QPen mPen;
};

#endif // SIMPLELINE_H
