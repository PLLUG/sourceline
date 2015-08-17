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
    QWidget{parent}
{
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
 * \brief RevisionTreeWidget::getVertexTypeVector according to pGraph, build vertex type vector.
 * \param pGraph
 * \return vector with VertexType values.
 */
std::vector<VertexType> RevisionTreeWidget::getVertexTypeVector(const revision_graph &pGraph)
{
    std::vector<VertexType> rVertexTypeVector(num_vertices(pGraph));
    BGL_FORALL_VERTICES(v, pGraph, revision_graph)
    {
        int i = v;

        if(!boost::in_degree(v,pGraph))
        {
            rVertexTypeVector[i] = vtNoIn;
        }
        else if(!boost::out_degree(v,pGraph))
        {
            rVertexTypeVector[i] = vtNoOut;
        }
        else if(boost::in_degree(v,pGraph) > 1 && boost::out_degree(v,pGraph) > 1)
        {
            rVertexTypeVector[i] = vtManyInManyOut;
        }
        else if(boost::in_degree(v,pGraph) > 1)
        {
            rVertexTypeVector[i] = vtManyInOneOut;
        }
        else if(boost::out_degree(v,pGraph) > 1)
        {
            rVertexTypeVector[i] = vtOneInManyOut;
        }
        else
        {
            rVertexTypeVector[i] = vtOneInOneOut;
        }
    }

    return rVertexTypeVector;
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
    for ( auto ii=sortedVerticesByTime.begin()+1; ii!=sortedVerticesByTime.end(); ++ii)
    {
        put(rowIndex, *ii, ++row);
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
    setMinimumHeight(25*num_vertices(mGraph));
}


void RevisionTreeWidget::paintEvent(QPaintEvent *e)
{
    QWidget::paintEvent(e);
    QPainter painter(this);

    painter.setBrush(Qt::red);
    painter.setPen(Qt::black);

    const int offset{20};
    const float width = 25;
    const float radius = 8;

    boost::associative_property_map<VertexIntMap> colIndex(mColumnMap);
    boost::associative_property_map<VertexIntMap> rowIndex(mRowMap);

    std::vector<VertexType> vertexTypeVector = getVertexTypeVector(mGraph);

    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
        int row = get(rowIndex, v);
        int col = get(colIndex, v);

        switch(vertexTypeVector[v])
        {
        case vtNoIn:
            painter.setBrush(Qt::black);
            painter.drawRect(width*col + offset - radius, width*row - radius,
                             radius*2, radius*2);
            break;
        case vtNoOut:
            painter.setBrush(Qt::yellow);
            painter.drawRect(width*col + offset - radius, width*row - radius,
                             radius*2, radius*2);
            break;
        case vtManyInManyOut:
            painter.setBrush(Qt::magenta);
            painter.drawRect(width*col + offset - radius, width*row - radius,
                             radius*2, radius*2);
            break;
        case vtManyInOneOut:
            painter.setBrush(Qt::red);
            painter.drawRect(width*col + offset - radius, width*row - radius,
                             radius*2, radius*2);
            break;
        case vtOneInManyOut:
            painter.setBrush(Qt::blue);
            painter.drawRect(width*col + offset - radius, width*row - radius,
                             radius*2, radius*2);
            break;
        case vtOneInOneOut:
            painter.setBrush(Qt::green);
            painter.drawEllipse(QPointF{width*col + offset, width*row},
                                radius, radius);
            break;
        }
        painter.drawText(QPointF{width*col + offset, width*row + radius}, QString::number(v));
    }

    painter.setPen(Qt::darkGray);
    BGL_FORALL_EDGES(e, mGraph, revision_graph)
    {
        int sourceRow = get(rowIndex, boost::source(e, mGraph));
        int sourceCol = get(colIndex, boost::source(e, mGraph));
        int targetRow = get(rowIndex, boost::target(e, mGraph));
        int targetCol = get(colIndex, boost::target(e, mGraph));
        painter.drawLine(QPoint(width*sourceCol + offset, width*sourceRow), QPoint(width*targetCol + offset, width*targetRow));
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

