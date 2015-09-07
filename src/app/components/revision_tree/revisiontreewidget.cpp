#include "revisiontreewidget.h"
#include <iostream>
#include <boost/graph/property_maps/container_property_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QPen>
#include <QLinearGradient>
#include <QDateTime>
#include "dfs_visitor.h"

using IndexPropertyMap = boost::property_map<revision_graph, boost::vertex_index_t>::type;
using PredMap = boost::iterator_property_map<typename std::vector<vertex>::iterator, IndexPropertyMap>;

RevisionTreeWidget::RevisionTreeWidget(QWidget *parent):
    QWidget{parent}
  ,mLeftOffset{20} // offset from left side
  ,mTopOffset{45} // height of row of tableView * 3/2
  ,mRadius{6} // radius of vertex
  ,mStep{3} // radius of rounding of edge
  ,mRowHeight{30} // height of row of tableView
  ,mColumnWidth{20} // width between column of revision tree
  ,mModel{nullptr}
{
    // Offset from bottom
    mBottomOffset = mRowHeight / 2;
    // Offset from center of vertex to first rounding of edge
    mEdgeOffset = mRadius + mStep * 2;
}

/*!
 * \brief RevisionTreeWidget::resetGraph Resets graph, recalculates.
 */
void RevisionTreeWidget::resetGraph()
{
    using boost::num_vertices;

    mRowMap.clear();
    mColumnMap.clear();
    mTestOrderMap.clear();

    if(!mModel) return;
    const int numVertices{num_vertices(mModel->graph())};
    if (!numVertices) return;

    const vertex root_vertex = findRoot(mModel->graph());
    std::cout << "root vertex is: " << root_vertex << std::endl;

    //perform depth first search
    using ColorMap = std::map<vertex, boost::default_color_type>;
    ColorMap colorMap;
    boost::associative_property_map<ColorMap> propColorMap(colorMap);
    dfs_visitor<VertexIntMap, vertex, revision_graph> dfs_vis{mColumnMap,mTestOrderMap};
    depth_first_search(mModel->graph(),dfs_vis,propColorMap,root_vertex);

    //perform topological sort
    int row{0};
    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);
    for (auto ii=mModel->sortedVertices().cbegin(); ii!=mModel->sortedVertices().cend(); ++ii)
    {
        put(rowIndex, *ii, row++);
    }

    mRevisionVertexes = revisionVertexVector(mModel->graph());

    setMinimumWidth(mLeftOffset + mColumnWidth * maxColumnFromColumnMap(mColumnMap) + 2 * mRadius);
    setMinimumHeight(mTopOffset + mRowHeight * (numVertices - 1) + mBottomOffset);
    updateGeometry();
}

int RevisionTreeWidget::radius() const
{
    return mRadius;
}

void RevisionTreeWidget::setRadius(int radius)
{
    mRadius = radius;
}

float RevisionTreeWidget::rowHeight() const
{
    return mRowHeight;
}

/*!
 * \brief RevisionTreeWidget::setItemWidth
 * \param width
 */
void RevisionTreeWidget::setRowHeight(float width)
{
    mRowHeight = width;
}

float RevisionTreeWidget::getLeftOffset() const
{
    return mLeftOffset;
}

/*!
 * \brief RevisionTreeWidget::setLeftOffset Sets left offset.
 * \param leftOffset Offset value.
 */
void RevisionTreeWidget::setLeftOffset(float leftOffset)
{
    mLeftOffset = leftOffset;
}

float RevisionTreeWidget::getTopOffset() const
{
    return mTopOffset;
}

/*!
 * \brief RevisionTreeWidget::setTopOffset Sets top offset.
 * \param topOffset Offset value.
 */
void RevisionTreeWidget::setTopOffset(float topOffset)
{
    mTopOffset = topOffset;
}

float RevisionTreeWidget::getBottomOffset() const
{
    return mBottomOffset;
}

/*!
 * \brief RevisionTreeWidget::setBottomOffset Sets bottom offset.
 * \param bottomOffset Offset value.
 */
void RevisionTreeWidget::setBottomOffset(float bottomOffset)
{
    mBottomOffset = bottomOffset;
}

/*!
 * \brief RevisionTreeWidget::paintEvent Paints graph.
 * \param e Paint event.
 */
void RevisionTreeWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    if(!mModel)
    {
        return;
    }
    // Getting of first and last visible row of revision tree
    int rectBeginY = e->rect().top();
    int rectEndY = e->rect().bottom();
    int firstRow = std::floor((rectBeginY - mTopOffset) / mRowHeight);
    if(rectBeginY < mTopOffset)
    {
        firstRow = 0;
    }
    if(firstRow >= mModel->rowCount()) return;
    if(mRevisionVertexes.size() != mModel->rowCount()) return;
    int lastRow = std::ceil((rectEndY - mTopOffset) / mRowHeight);
    lastRow = std::min(lastRow,mModel->rowCount()-1);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    boost::associative_property_map<VertexIntMap> colIndex(mColumnMap);
    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

    // Drawing rectangle fields
    painter.setPen(Qt::NoPen);
    for(int row = firstRow; row <= lastRow; ++row)
    {
        painter.setBrush(mModel->data(mModel->index(row,0),Qt::BackgroundRole).value<QColor>());
        painter.drawRect(0, mRowHeight + row*mRowHeight,
                         width(), mRowHeight);
    }
    painter.setBrush(Qt::NoBrush);

    // Drawing of edges
    QPen lPen;
    lPen.setWidth(2);
    lPen.setColor(Qt::darkGray);
    BGL_FORALL_EDGES(e, mModel->graph(), revision_graph)
    {
        const auto v1 = boost::source(e, mModel->graph());
        const auto v2 = boost::target(e, mModel->graph());

        const int sourceRow = get(rowIndex, v1);
        const int sourceCol = get(colIndex, v1);
        const int targetRow = get(rowIndex, v2);
        const int targetCol = get(colIndex, v2);

        // Painting of edge, only if it is within the display
        if(!((sourceRow < firstRow && targetRow < firstRow) ||
             (sourceRow > lastRow && targetRow > lastRow)))
        {
            QPainterPath myPath;
            QLinearGradient gradient(QPointF(mRowHeight*sourceCol + 1.0 * mLeftOffset,
                                             mRowHeight*sourceRow + 1.0 * mTopOffset),
                                     QPointF(mRowHeight*targetCol + 1.0 * mLeftOffset,
                                             mRowHeight*targetRow + 1.0 * mTopOffset));
            gradient.setColorAt(0, mRevisionVertexes[v1].color);
            gradient.setColorAt(1, mRevisionVertexes[v2].color);
            lPen.setBrush(gradient);
            painter.setPen(lPen);

            if(targetCol > sourceCol)
            {
                // Moving to center of source vertex
                myPath.moveTo(QPointF(mColumnWidth*sourceCol + mLeftOffset,
                                      mRowHeight*sourceRow + mTopOffset));
                // Drawing line to first rounding of edge
                myPath.lineTo(QPointF(mColumnWidth*sourceCol + mLeftOffset,
                                      mRowHeight*sourceRow + mTopOffset - mEdgeOffset));
                // Drawing first rounding
                myPath.quadTo(QPointF(mColumnWidth*sourceCol + mLeftOffset,
                                      mRowHeight*sourceRow + mTopOffset - mEdgeOffset),
                              QPointF(mColumnWidth*sourceCol + mLeftOffset + mStep,
                                      mRowHeight*sourceRow + mTopOffset - mEdgeOffset - mStep));
                // Drawing line from first rounding to second rounding
                myPath.lineTo(QPointF(mColumnWidth*targetCol + mLeftOffset - mStep,
                                      mRowHeight*sourceRow + mTopOffset - mEdgeOffset - mStep));
                // Drawing second rounding
                myPath.quadTo(QPointF(mColumnWidth*targetCol + mLeftOffset - mStep,
                                      mRowHeight*sourceRow + mTopOffset - mEdgeOffset - mStep),
                              QPointF(mColumnWidth*targetCol + mLeftOffset,
                                      mRowHeight*sourceRow + mTopOffset - mEdgeOffset - 2 * mStep));
                // Drawing line from second rouding to target vertex
                myPath.lineTo(QPointF(mColumnWidth*targetCol + mLeftOffset,
                                      mRowHeight*targetRow + mTopOffset));
            }
            else if(targetCol < sourceCol)
            {
                // Moving to center of target vertex
                myPath.moveTo(QPointF(mColumnWidth*targetCol + mLeftOffset,
                                      mRowHeight*targetRow + mTopOffset));
                // Drawing line to first rounding of edge
                myPath.lineTo(QPointF(mColumnWidth*targetCol + mLeftOffset,
                                      mRowHeight*targetRow + mTopOffset + mEdgeOffset));
                // Drawing first rounding
                myPath.quadTo(QPointF(mColumnWidth*targetCol + mLeftOffset,
                                      mRowHeight*targetRow + mTopOffset + mEdgeOffset),
                              QPointF(mColumnWidth*targetCol + mLeftOffset + mStep,
                                      mRowHeight*targetRow + mTopOffset + mEdgeOffset + mStep));
                // Drawing line from first rounding to second rounding
                myPath.lineTo(QPointF(mColumnWidth*sourceCol + mLeftOffset - mStep,
                                      mRowHeight*targetRow + mTopOffset + mEdgeOffset + mStep));
                // Drawing second rounding
                myPath.quadTo(QPointF(mColumnWidth*sourceCol + mLeftOffset - mStep,
                                      mRowHeight*targetRow + mTopOffset + mEdgeOffset + mStep),
                              QPointF(mColumnWidth*sourceCol + mLeftOffset,
                                      mRowHeight*targetRow + mTopOffset + mEdgeOffset + 2 * mStep));
                // Drawing line from second rouding to source vertex
                myPath.lineTo(QPointF(mColumnWidth*sourceCol + mLeftOffset,
                                      mRowHeight*sourceRow + mTopOffset));
            }
            else
            {
                myPath.moveTo(QPointF(mColumnWidth*sourceCol + mLeftOffset,
                                      mRowHeight*sourceRow + mTopOffset));
                myPath.lineTo(QPointF(mColumnWidth*targetCol + mLeftOffset,
                                      mRowHeight*targetRow + mTopOffset));
            }
            painter.drawPath(myPath);
        }
    }

    //    boost::associative_property_map<VertexIntMap> testAlgorithmIndexes{mTestOrderMap};

    painter.setPen(Qt::darkGray);
    for(int row = firstRow; row <= lastRow; ++row)
    {
        const vertex v = mModel->vertexAt(row);
        const int col = mRevisionVertexes[v].column;

        // Drawing vertex
        painter.setBrush(mRevisionVertexes[v].color);
        switch(mRevisionVertexes[v].shape)
        {
        case vsSquare:
            painter.drawRect(mLeftOffset + col*mColumnWidth - mRadius, // left corner X
                             mTopOffset + row*mRowHeight - mRadius, // left corner Y
                             mRadius*2, mRadius*2); // sizes of sides
            break;
        case vsCircle:
            painter.drawEllipse(QPointF{mColumnWidth*col + mLeftOffset, // center X
                                        mRowHeight*row + mTopOffset}, // center Y
                                mRadius, mRadius);
            break;
        }
        //        // Draws number of vertex
        //        painter.drawText(QPointF{mRowHeight*col + mLeftOffset,
        //                                 mRowHeight*row + mTopOffset},
        //                         QString::number(get(testAlgorithmIndexes,v)));

        //        painter.drawText(QPointF{mRowHeight*col + mLeftOffset,
        //                                 mRowHeight*row + mTopOffset},
        //                         QString::number(v));
    }
}

/*!
 * \brief getSortedGraphByTime sorts graph by commit-time
 * \param graph - graph to be sorted
 * \return vector with sorted vertices
 */
std::vector<vertex> RevisionTreeWidget::getSortedGraphByTime(const revision_graph &graph)
{
    int verticesNumb = num_vertices(graph);
    std::vector< vertex > rVector;
    rVector.reserve(verticesNumb);

    // Copying vertices from graph to rVector
    boost::graph_traits< revision_graph >::vertex_iterator vi, vi_end;
    for(boost::tie(vi, vi_end) = boost::vertices(graph); vi != vi_end; ++vi)
    {
        rVector.push_back(*vi);
    }

    // Sorting vertices in rVector
    std::sort(rVector.begin(), rVector.end(),
              [&graph](const vertex &vert1, const vertex &vert2) -> bool
    {
        return graph[vert1].created < graph[vert2].created;
    });

    return std::move(rVector);
}

/*!
 * \brief RevisionTreeWidget::findRoot Finds root vertex in graph.
 * \param pGraph
 * \return Root vertex
 */
vertex RevisionTreeWidget::findRoot(const revision_graph &pGraph)
{
    // assuming root exists1
    vertex root_vertex{boost::graph_traits<revision_graph>::null_vertex()};
    BGL_FORALL_VERTICES(v, pGraph, revision_graph)
    {
        if(!boost::in_degree(v,pGraph))
        {
            root_vertex = v;
            break;
        }
    }
    return root_vertex;
}

/*!
 * \brief RevisionTreeWidget::revisionVertexVector returns vector of RevisionVertex.
 * \param pGraph - graph, from which vertices are taken.
 * \return vector of RevisionVertex.
 */
std::vector<RevisionVertex> RevisionTreeWidget::revisionVertexVector(const revision_graph &pGraph)
{
    boost::associative_property_map<VertexIntMap> colIndex(mColumnMap);
    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

    std::vector<RevisionVertex> rRevisionVertexes(num_vertices(pGraph));

    // Setting values of vertexes from rRevisionVertexes
    BGL_FORALL_VERTICES(v, pGraph, revision_graph)
    {
        rRevisionVertexes[v].row = get(rowIndex, v);
        rRevisionVertexes[v].column = get(colIndex, v);

        // Initial commit
        if(!boost::in_degree(v,pGraph))
        {
            rRevisionVertexes[v].type = vtNoIn;
            rRevisionVertexes[v].color = Qt::black;
            rRevisionVertexes[v].shape = vsCircle;
        }
        // Last commit
        else if(!boost::out_degree(v,pGraph))
        {
            rRevisionVertexes[v].type = vtNoOut;
            rRevisionVertexes[v].color = Qt::yellow;
            rRevisionVertexes[v].shape = vsCircle;
        }
        else if(boost::in_degree(v,pGraph) > 1 && boost::out_degree(v,pGraph) > 1)
        {
            rRevisionVertexes[v].type = vtManyInManyOut;
            rRevisionVertexes[v].color = Qt::magenta;
            rRevisionVertexes[v].shape = vsSquare;
        }
        // Merge
        else if(boost::in_degree(v,pGraph) > 1)
        {
            rRevisionVertexes[v].type = vtManyInOneOut;
            rRevisionVertexes[v].color = Qt::red;
            rRevisionVertexes[v].shape = vsSquare;
        }
        // Branching
        else if(boost::out_degree(v,pGraph) > 1)
        {
            rRevisionVertexes[v].type = vtOneInManyOut;
            rRevisionVertexes[v].color = Qt::blue;
            rRevisionVertexes[v].shape = vsSquare;
        }
        // Usual commit
        else
        {
            rRevisionVertexes[v].type = vtOneInOneOut;
            rRevisionVertexes[v].color = Qt::green;
            rRevisionVertexes[v].shape = vsCircle;
        }
    }
    return std::move(rRevisionVertexes);
}

void RevisionTreeWidget::setModel(RevisionModel *pModel)
{
    mModel = pModel;
    if(mModel)
    {
        //        connect(mModel,&RevisionModel::graphReset,this,&RevisionTreeWidget::resetGraph,Qt::UniqueConnection);
    }
}

float RevisionTreeWidget::columnWidth() const
{
    return mColumnWidth;
}

void RevisionTreeWidget::setColumnWidth(float width)
{
    mColumnWidth = width;
}

int RevisionTreeWidget::maxColumnFromColumnMap(const VertexIntMap &pColumnMap)
{
    auto rMaxCol = std::max_element(pColumnMap.cbegin(), pColumnMap.cend(),
                                    [](const std::pair<vertex, int> &iter1,
                                    const std::pair<vertex, int> &iter2)
    {
        return iter1.second < iter2.second;
    });
    return rMaxCol->second;
}

int RevisionTreeWidget::getEdgeOffset() const
{
    return mEdgeOffset;
}

void RevisionTreeWidget::setEdgeOffset(int edgeOffset)
{
    mEdgeOffset = edgeOffset;
}

int RevisionTreeWidget::getStep() const
{
    return mStep;
}

void RevisionTreeWidget::setStep(int step)
{
    mStep = step;
}
