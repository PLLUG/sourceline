#ifndef REVISIONTREEWIDGET_H
#define REVISIONTREEWIDGET_H
/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Halyna Butovych (galynabutovych@gmail.com)                    ***
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
#include "revisionmodel.h"
#include "revisionvertex.h"
#include <QWidget>

using VertexIntMap = std::map<vertex, int>;

/*!
 * \brief The RevisionTreeWidget class Paints revision graph.
 */
class RevisionTreeWidget : public QWidget
{
public:
    RevisionTreeWidget(QWidget* parent = nullptr);

    static int maxColumnFromColumnMap(const VertexIntMap &pColumnMap);
    void resetGraph();
    void setModel(RevisionModel *pModel);

    float bottomOffset() const;
    void setBottomOffset(float bottomOffset);

    float columnWidth() const;
    void setColumnWidth(float columnWidth);

    int edgeOffset() const;
    void setEdgeOffset(int edgeOffset);

    int edgeWidth() const;
    void setEdgeWidth(int edgeWidth);

    float leftOffset() const;
    void setLeftOffset(float leftOffset);

    int roundingRadius() const;
    void setRoundingRadius(int roundingRadius);

    float rowHeight() const;
    void setRowHeight(float rowHeight);

    float topOffset() const;
    void setTopOffset(float topOffset);

    int vertexRadius() const;
    void setVertexRadius(int vertexRadius);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    static vertex findRoot(const revision_graph &pGraph);
    std::vector<RevisionVertex> revisionVertexVector(const revision_graph &pGraph);
    std::vector<vertex> sortedGraphByTime(const revision_graph &graph);

private:
    float mBottomOffset;
    float mColumnWidth;
    int mEdgeOffset;
    int mEdgeWidth;
    float mLeftOffset;
    int mRoundingRadius;
    float mRowHeight;
    float mTopOffset;
    int mVertexRadius;

    VertexIntMap mColumnMap;
    VertexIntMap mRowMap;

    std::vector<RevisionVertex> mRevisionVertexes;
    VertexIntMap mTestOrderMap;
    RevisionModel *mModel;
};

#endif // REVISIONTREEWIDGET_H
