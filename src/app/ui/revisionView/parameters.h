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

#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <QBrush>
#include <QPen>

class Parameters
{
public:
    static QBrush ViewBackground() { return QColor(200, 200, 200); }
    static QPen ItemBoudingRectPen() { return QPen(QColor(30, 30, 30), 1); }
    static QColor ItemSelectedColor() { return QColor(170, 170, 170, 150); }
    static QColor ItemBackground() { return QColor(150, 150, 150, 150); }
    static QColor LinesColor() { return QColor(30, 130, 210, 255); }

    static QRectF bubbleRect() { return QRectF(0, 0, 8, 8); }

    static const int GridStep = 15;
};

#endif // PARAMETERS_H
