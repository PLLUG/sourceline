#include "revisiontreewidget.h"
#include <iostream>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/property_maps/container_property_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <QPainter>
#include <QPaintEvent>
#include <QDateTime>
#include "dfs_visitor.h"

using IndexPropertyMap = boost::property_map<revision_graph, boost::vertex_index_t>::type;
using PredMap = boost::iterator_property_map<typename std::vector<vertex>::iterator, IndexPropertyMap>;

RevisionTreeWidget::RevisionTreeWidget(QWidget *parent):
    QWidget{parent},
    mLeftOffset{20},
    mTopOffset{45}, // height of row of tableView * 3/2
    mRadius{8},
    mRowHeight{30} // height of row of tableView
{
    mBottomOffset = mRowHeight / 2;
}

RevisionTreeWidget::~RevisionTreeWidget()
{
}

/*!
 * \brief RevisionTreeWidget::setGraph Sets graph.
 * \param pGraph Boost graph.
 */
void RevisionTreeWidget::setGraph(const revision_graph &pGraph)
{
    using boost::num_vertices;

    mGraph = pGraph;
    if (!num_vertices(mGraph)) return;

    mRowMap.clear();
    mColumnMap.clear();
    mTestOrderMap.clear();

    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

    vertex root_vertex = findRoot(mGraph);
    std::cout << "root vertex is: " << root_vertex << std::endl;

    //perform depth first search
    using ColorMap = std::map<vertex, boost::default_color_type>;
    ColorMap colorMap;
    boost::associative_property_map<ColorMap> propColorMap(colorMap);
    dfs_visitor<VertexIntMap, vertex, revision_graph> dfs_vis{mColumnMap,mTestOrderMap};
    depth_first_search(mGraph,dfs_vis,propColorMap,root_vertex);

    //perform topological sort
    int row{0};
    std::vector< vertex > sorted_vertices;
    topological_sort(mGraph, std::back_inserter(sorted_vertices));
    for (auto ii=sorted_vertices.begin(); ii!=sorted_vertices.end(); ++ii)
    {
        put(rowIndex, *ii, row++);
    }

    setMinimumHeight(mTopOffset + mRowHeight * (num_vertices(mGraph) - 1) + mBottomOffset);
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
    QPainter painter(this);

    boost::associative_property_map<VertexIntMap> colIndex(mColumnMap);
    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

    boost::associative_property_map<VertexIntMap> testAlgorithmIndexes{mTestOrderMap};

    std::vector<RevisionVertex> revisionVertexes = revisionVertexVector(mGraph);

    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
        int row = revisionVertexes[v].row;
        int col = revisionVertexes[v].column;
        painter.setBrush(revisionVertexes[v].color);

        // Drawing vertex
        switch(revisionVertexes[v].shape)
        {
        case vsSquare:
            painter.drawRect(mLeftOffset + col*mRowHeight - mRadius, // left corner X
                             mTopOffset + row*mRowHeight - mRadius, // left corner Y
                             mRadius*2, mRadius*2); // sizes of sides
            break;
        case vsCircle:
            painter.drawEllipse(QPointF{mRowHeight*col + mLeftOffset, // center X
                                        mRowHeight*row + mTopOffset}, // center Y
                                mRadius, mRadius);
            break;
        }
        painter.drawText(QPointF{mRowHeight*col + mLeftOffset,
                                 mRowHeight*row + mTopOffset},
                         QString::number(get(testAlgorithmIndexes,v)));
        //        painter.drawText(QPointF{mWidth*col + mLeftOffset,
        //                                 mWidth*row + mTopOffset},
        //                         QString::number(v));
    }

    painter.setPen(Qt::darkGray);
    BGL_FORALL_EDGES(e, mGraph, revision_graph)
    {
        int sourceRow = get(rowIndex, boost::source(e, mGraph));
        int sourceCol = get(colIndex, boost::source(e, mGraph));
        int targetRow = get(rowIndex, boost::target(e, mGraph));
        int targetCol = get(colIndex, boost::target(e, mGraph));
        painter.drawLine(QPoint(mRowHeight*sourceCol + mLeftOffset,
                                mRowHeight*sourceRow + mTopOffset),
                         QPoint(mRowHeight*targetCol + mLeftOffset,
                                mRowHeight*targetRow + mTopOffset));
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

    return rVector;
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

    return rRevisionVertexes;
}
