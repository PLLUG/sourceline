#ifndef REVISIONVERTEX
#define REVISIONVERTEX
/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Nazarii Plebanskii (nazar796@gmail.com)                       ***
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

#include <QColor>
/*!
 * \brief The VertexType enum represents types of vertexes.
 *
 * Vertex type is defined according to how many edges enter in vertex and
 * how many exit from.
 */
enum VertexType
{
    /// Number of input edges = 0
    vtNoIn,
    /// Number of output edges = 0
    vtNoOut,
    /// Number of input edges = 1, Number of output edges = 1
    vtOneInOneOut,
    /// Number of input edges > 1, Number of output edges > 1
    vtManyInManyOut,
    /// Number of input edges = 1, Number of output edges > 1
    vtOneInManyOut,
    /// Number of input edges > 1, Number of output edges = 1
    vtManyInOneOut
};

/*!
 * \brief The VertexShape enum represents shapes of vertexes.
 */
enum VertexShape
{
    /// Square shape of vertex
    vsSquare,
    /// Circle shape of vertex
    vsCircle
};

struct RevisionVertex
{
    VertexType type;
    VertexShape shape;
    QColor color;
    int row;
    int column;
};

#endif // REVISIONVERTEX
