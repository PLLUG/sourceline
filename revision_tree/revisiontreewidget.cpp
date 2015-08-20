#include "revisiontreewidget.h"
#include <iostream>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/property_maps/container_property_map.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>
#include <boost/graph/dominator_tree.hpp>
#include <boost/graph/topology.hpp>
#include <QPainter>
#include <QPaintEvent>
#include <QDateTime>

using IndexPropertyMap = boost::property_map<revision_graph, boost::vertex_index_t>::type;
using PredMap = boost::iterator_property_map<typename std::vector<vertex>::iterator, IndexPropertyMap>;

template <typename IndexMap, typename vertex, typename graph>
class bfs_visitor : public boost::default_bfs_visitor
{
public:
    bfs_visitor(IndexMap &rowMap, IndexMap &colMap):
        mRowIndexMap{rowMap}
      ,mColumnIndexMap{colMap}
      ,mPrevVertex{boost::graph_traits<graph>::null_vertex()}
    {
    }

    template < typename Vertex, typename Graph >
    /*!
     * \brief initialize_vertex is invoked on every vertex before the start of the search
     * \param v vertex
     * \param g graph
     */
    void initialize_vertex(Vertex v, const Graph & g)
    {
        Q_UNUSED(g)
        put(mColumnIndexMap, v, 0);
        put(mRowIndexMap, v, 0);
    }

    template < typename Edge, typename Graph >
    /*!
     * \brief examine_edge is invoked on every out-edge of each vertex immediately after the vertex is removed from the queue
     * \param e edge
     * \param g graph
     */
    void examine_edge(Edge e, Graph g)
    {
        auto source = boost::source(e,g);
        put(mRowIndexMap, boost::target(e,g), get(mRowIndexMap,source)+1);
    }

    template < typename Vertex, typename Graph >
    /*!
     * \brief discover_vertex is invoked the first time the algorithm encounters vertex u.
     * All vertices closer to the source vertex have been discovered,
     * and vertices further from the source have not yet been discovered.
     * \param u vertex
     * \param g graph
     */
    void discover_vertex(Vertex v, const Graph & g) const
    {
        Q_UNUSED(v)
        Q_UNUSED(g)
    }

    template <typename Vertex, typename Graph>
    /*!
     * \brief examine_vertex is invoked in each vertex as it is removed from the queue.
     * \param u
     * \param g
     */
    void examine_vertex(Vertex v, Graph& g)
    {
        Q_UNUSED(g)
        if(boost::graph_traits<graph>::null_vertex() != mPrevVertex)
        {
            if(get(mRowIndexMap,mPrevVertex) == get(mRowIndexMap,v))
            {
                put(mColumnIndexMap,v, get(mColumnIndexMap,mPrevVertex)+1 );
            }
            else
            {
                put(mColumnIndexMap,v,0); //TODO: maybe use some column of some dominator vertex of v
            }
        }
        mPrevVertex = v;
    }

private:
    boost::associative_property_map<IndexMap> mRowIndexMap;
    boost::associative_property_map<IndexMap> mColumnIndexMap;
    vertex mPrevVertex;
};

RevisionTreeWidget::RevisionTreeWidget(QWidget *parent):
    QWidget{parent},
    mLeftOffset{20},
    mTopOffset{45}, // height of row of tableView * 3/2
    mRadius{8},
    mWidth{30} // height of row of tableView
{
    mBottomOffset = mWidth / 2;
}

RevisionTreeWidget::~RevisionTreeWidget()
{
}

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
 * \brief RevisionTreeWidget::revisionVertexVector according to pGraph,
 *  build RevisionVertex vector.
 * \param pGraph - revision graph
 * \return vector with RevisionVertex values.
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

    return rRevisionVertexes;
}
float RevisionTreeWidget::getBottomOffset() const
{
    return mBottomOffset;
}

void RevisionTreeWidget::setBottomOffset(float bottomOffset)
{
    mBottomOffset = bottomOffset;
}

float RevisionTreeWidget::getTopOffset() const
{
    return mTopOffset;
}

void RevisionTreeWidget::setTopOffset(float topOffset)
{
    mTopOffset = topOffset;
}

float RevisionTreeWidget::getLeftOffset() const
{
    return mLeftOffset;
}

void RevisionTreeWidget::setLeftOffset(float leftOffset)
{
    mLeftOffset = leftOffset;
}

float RevisionTreeWidget::width() const
{
    return mWidth;
}

void RevisionTreeWidget::setWidth(float width)
{
    mWidth = width;
}

int RevisionTreeWidget::radius() const
{
    return mRadius;
}

void RevisionTreeWidget::setRadius(int radius)
{
    mRadius = radius;
}

void RevisionTreeWidget::setGraph(const revision_graph &pGraph)
{
    using boost::num_vertices;

    mGraph = pGraph;
    if (!num_vertices(mGraph)) return;

    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

    vertex root_vertex = findRoot(mGraph);
    std::cout << "root vertex is: " << root_vertex << std::endl;

    //perform breadth first search
    bfs_visitor<VertexIntMap, vertex, revision_graph> vis{mRowMap, mColumnMap};
    breadth_first_search(mGraph, root_vertex, visitor(vis));

    int row{0};
//    //perform topological sort
//    std::vector< vertex > sorted_vertices;
//    topological_sort(mGraph, std::back_inserter(sorted_vertices));
//    put(rowIndex, root_vertex, 0);
//    for ( std::vector< vertex >::reverse_iterator ii=sorted_vertices.rbegin()+1; ii!=sorted_vertices.rend(); ++ii)
//    {
//        put(rowIndex, *ii, ++row);
//    }

    //perform sort by time
    row = 0;
    std::vector< vertex > sortedVerticesByTime = getSortedGraphByTime(mGraph);
    for ( auto ii=sortedVerticesByTime.rbegin(); ii!=sortedVerticesByTime.rend(); ++ii)
    {
        put(rowIndex, *ii, row++);
    }

// sample of using dominator tree algorithm
//    using IndexMapD = boost::property_map<revision_graph, boost::vertex_index_t>::const_type;
//    using TimeMap = boost::iterator_property_map<typename std::vector<VerticesSizeType>::iterator,IndexMapD>;
//    using PredMap = boost::iterator_property_map<typename std::vector<vertex>::iterator, IndexMapD>;
//    const IndexMapD indexMap = get(boost::vertex_index, mGraph);
//    std::vector<vertex> domTreePredVector = std::vector<vertex>(num_vertices(mGraph), boost::graph_traits<revision_graph>::null_vertex());
//    std::vector<VerticesSizeType> dfnum(numOfVertices, 0);
//    std::vector<vertex> parent(numOfVertices, boost::graph_traits<revision_graph>::null_vertex());
//    //The dominator tree where parents are each children's immediate dominator.
//    PredMap domTreePredMap = boost::make_iterator_property_map(domTreePredVector.begin(), indexMap);
//    //The sequence number of depth first search.
//    TimeMap dfnumMap(make_iterator_property_map(dfnum.begin(), indexMap));
//    //The predecessor map records the parent of the depth first search tree.
//    PredMap parentMap(make_iterator_property_map(parent.begin(), indexMap));
//    // The vector containing vertices in depth first search order.
//    // If we access this vector sequentially, it's equivalent to access vertices by depth first search order.
//    std::vector<vertex> verticesByDFNum(parent);
//    boost::lengauer_tarjan_dominator_tree(mGraph, root_vertex,indexMap,
//                                          dfnumMap, parentMap,verticesByDFNum, domTreePredMap);
//    boost::graph_traits<revision_graph>::vertex_iterator uItr, uEnd;
//    std::vector<int> idom(boost::num_vertices(mGraph));
//    for (boost::tie(uItr, uEnd) = boost::vertices(mGraph); uItr != uEnd; ++uItr)
//    {
//        if (get(domTreePredMap, *uItr) != boost::graph_traits<revision_graph>::null_vertex())
//        {
//            //            std::cout << get(domTreePredMap, *uItr) << " => " << *uItr << std::endl;
//            idom[get(indexMap, *uItr)] =
//                    get(indexMap, get(domTreePredMap, *uItr));
//        }
//        else
//            idom[get(indexMap, *uItr)] = (std::numeric_limits<int>::max)();
//    }
//    std::cout << "DOMINATOR TREE with root " << root_vertex << " : " << mGraph[root_vertex].message << std::endl;
//    std::copy(idom.begin(), idom.end(), std::ostream_iterator<int>(std::cout, " "));
//    std::cout << std::endl;
    setMinimumHeight(mTopOffset + mWidth * (num_vertices(mGraph) - 1) + mBottomOffset);
}


void RevisionTreeWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);

    boost::associative_property_map<VertexIntMap> colIndex(mColumnMap);
    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

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
            painter.drawRect(mLeftOffset + col*mWidth - mRadius, // left corner X
                             mTopOffset + row*mWidth - mRadius, // left corner Y
                             mRadius*2, mRadius*2); // sizes of sides
            break;
        case vsCircle:
            painter.drawEllipse(QPointF{mWidth*col + mLeftOffset, // center X
                                        mWidth*row + mTopOffset}, // center Y
                                mRadius, mRadius);
            break;
        }

        painter.drawText(QPointF{mWidth*col + mLeftOffset,
                                 mWidth*row + mTopOffset},
                         QString::number(v));
    }

    painter.setPen(Qt::darkGray);
    BGL_FORALL_EDGES(e, mGraph, revision_graph)
    {
        int sourceRow = get(rowIndex, boost::source(e, mGraph));
        int sourceCol = get(colIndex, boost::source(e, mGraph));
        int targetRow = get(rowIndex, boost::target(e, mGraph));
        int targetCol = get(colIndex, boost::target(e, mGraph));
        painter.drawLine(QPoint(mWidth*sourceCol + mLeftOffset,
                                mWidth*sourceRow + mTopOffset),
                         QPoint(mWidth*targetCol + mLeftOffset,
                                mWidth*targetRow + mTopOffset));
    }
}

void RevisionTreeWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

bool RevisionTreeWidget::event(QEvent *e)
{
    return QWidget::event(e);
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

