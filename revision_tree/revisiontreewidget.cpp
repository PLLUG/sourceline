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
    bfs_visitor(IndexMap &rowMap, IndexMap &colMap, std::vector<vertex>& BFSVertexRow):
        mRowIndexMap{rowMap}
      ,mColumnIndexMap{colMap}
      ,mBFSVertexRow{BFSVertexRow}
      ,mPrevVertex{boost::graph_traits<graph>::null_vertex()}
    {
    }

    /*!
     * \brief initialize_vertex is invoked on every vertex before the start of the search
     * \param v vertex
     * \param g graph
     */
    template < typename Vertex, typename Graph >
    void initialize_vertex(Vertex v, const Graph & g)
    {
        put(mColumnIndexMap, v, 0);
        put(mRowIndexMap, v, 0);
    }

    /*!
     * \brief examine_edge is invoked on every out-edge of each vertex immediately after the vertex is removed from the queue
     * \param e
     * \param g
     */
    template < typename Edge, typename Graph >
    void examine_edge(Edge e, Graph g)
    {
        auto source = boost::source(e,g);
        put(mRowIndexMap, boost::target(e,g), get(mRowIndexMap,source)+1);
    }

    /*!
     * \brief discover_vertex is invoked the first time the algorithm encounters vertex u.
     * All vertices closer to the source vertex have been discovered,
     * and vertices further from the source have not yet been discovered.
     * \param u vertex
     * \param g graph
     */
    template < typename Vertex, typename Graph >
    void discover_vertex(Vertex u, const Graph & g) const
    {
        std::cout << "discover_vertex: " << u << std::endl;
    }

    /*!
     * \brief examine_vertex  is invoked in each vertex as it is removed from the queue.
     * \param u
     * \param g
     */
    template <typename Vertex, typename Graph>
    void examine_vertex(Vertex v, Graph& g)
    {
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
        mBFSVertexRow.push_back(v);
        std::cout << "examine_vertex: " << v << std::endl;
        mPrevVertex = v;
    }
    std::vector<vertex> getBFSRow()
    {
        std::cout << "SIZE: " << mBFSVertexRow.size();
        return mBFSVertexRow;
    }

private:
    boost::associative_property_map<IndexMap> mRowIndexMap;
    boost::associative_property_map<IndexMap> mColumnIndexMap;
    std::vector<vertex> &mBFSVertexRow;
    vertex mPrevVertex;
};

RevisionTreeWidget::RevisionTreeWidget(QWidget *parent):
    QOpenGLWidget{parent}
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

void RevisionTreeWidget::setGraph(const revision_graph &pGraph)
{
    mGraph = pGraph;
    boost::vertices(mGraph);
    boost::associative_property_map<IndexMap> colIndex(mColumnMap);
    boost::associative_property_map<IndexMap> rowIndex(mRowMap);
    std::vector<vertex> BFSVertexRow;
//    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
//    {
//        put(colIndex, v, -1);
//        put(rowIndex, v, -1);
//    }

    //perform topological sort
    std::vector< vertex > sorted_vertices;
    topological_sort(mGraph, std::back_inserter(sorted_vertices));
    vertex root_vertex = findRoot(mGraph);

    //perform breadth first search
    bfs_visitor<IndexMap, vertex, revision_graph> vis{mRowMap, mColumnMap, BFSVertexRow};
    breadth_first_search(mGraph, root_vertex, visitor(vis));

    boost::associative_property_map<std::map<vertex, Point>> positionMap(mPositionMap);
    boost::random_graph_layout
            (mGraph,
             positionMap,
             boost::rectangle_topology<>(5,5,500,500)
             );
    //    boost::fruchterman_reingold_force_directed_layout //slow
    //            (mGraph,
    //             positionMap,
    //             boost::rectangle_topology<>(5,5,450,500));

    using VerticesSizeType = boost::graph_traits<revision_graph>::vertices_size_type;
    using IndexMapD = boost::property_map<revision_graph, boost::vertex_index_t>::const_type;
    using TimeMap = boost::iterator_property_map<typename std::vector<VerticesSizeType>::iterator,IndexMapD>;
    using PredMap = boost::iterator_property_map<typename std::vector<vertex>::iterator, IndexMapD>;

    // Make property maps
    const VerticesSizeType numOfVertices = boost::num_vertices(mGraph);
    if (numOfVertices == 0) return;

    // index map
    const IndexMapD indexMap = get(boost::vertex_index, mGraph);
    std::vector<vertex> domTreePredVector = std::vector<vertex>(num_vertices(mGraph), boost::graph_traits<revision_graph>::null_vertex());
    std::vector<VerticesSizeType> dfnum(numOfVertices, 0);
    std::vector<vertex> parent(numOfVertices, boost::graph_traits<revision_graph>::null_vertex());

    //The dominator tree where parents are each children's immediate dominator.
    PredMap domTreePredMap = boost::make_iterator_property_map(domTreePredVector.begin(), indexMap);
    //The sequence number of depth first search.
    TimeMap dfnumMap(make_iterator_property_map(dfnum.begin(), indexMap));
    //The predecessor map records the parent of the depth first search tree.
    PredMap parentMap(make_iterator_property_map(parent.begin(), indexMap));
    // The vector containing vertices in depth first search order.
    // If we access this vector sequentially, it's equivalent to access vertices by depth first search order.
    std::vector<vertex> verticesByDFNum(parent);

    // Run main algorithm
    boost::lengauer_tarjan_dominator_tree(mGraph, root_vertex,indexMap,
                                          dfnumMap, parentMap,verticesByDFNum, domTreePredMap);
    boost::graph_traits<revision_graph>::vertex_iterator uItr, uEnd;
    std::vector<int> idom(boost::num_vertices(mGraph));
    for (boost::tie(uItr, uEnd) = boost::vertices(mGraph); uItr != uEnd; ++uItr)
    {
        if (get(domTreePredMap, *uItr) != boost::graph_traits<revision_graph>::null_vertex())
        {
            //            std::cout << get(domTreePredMap, *uItr) << " => " << *uItr << std::endl;
            idom[get(indexMap, *uItr)] =
                    get(indexMap, get(domTreePredMap, *uItr));
        }
        else
            idom[get(indexMap, *uItr)] = (std::numeric_limits<int>::max)();
    }
    std::cout << "DOMINATOR TREE with root " << root_vertex << " : " << mGraph[root_vertex].message << std::endl;
    std::copy(idom.begin(), idom.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    for (boost::tie(uItr, uEnd) = boost::vertices(mGraph); uItr != uEnd; ++uItr)
    {
        if (get(parentMap, *uItr) != boost::graph_traits<revision_graph>::null_vertex())
        {
            //            std::cout << get(domTreePredMap, *uItr) << " => " << *uItr << std::endl;
            idom[get(indexMap, *uItr)] =
                    get(indexMap, get(parentMap, *uItr));
        }
        else
            idom[get(indexMap, *uItr)] = (std::numeric_limits<int>::max)();
    }
    std::cout << "DOMINATOR TREE with root " << root_vertex << " : " << mGraph[root_vertex].message << std::endl;
    std::copy(idom.begin(), idom.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    put(colIndex, root_vertex, 0);
    put(rowIndex, root_vertex, 0);
    int row{0};
    for ( std::vector< vertex >::reverse_iterator ii=sorted_vertices.rbegin()+1; ii!=sorted_vertices.rend(); ++ii)
    {
        auto v = *ii;
        put(rowIndex, v, ++row);
//        put(colIndex, v, get(colIndex, get(domTreePredMap,v)));
//        if(get(domTreePredMap,v) == *(ii-1))//if dominator is parent
//        {
//            put(colIndex, v, get(colIndex, get(domTreePredMap,v)));
//        }
//        else if(boost::out_degree(get(domTreePredMap,v), mGraph) > 1)
//        {
//            int col = get(colIndex,*(ii-1));
//            auto pair = boost::out_edges(get(domTreePredMap,v),mGraph);
//            for(auto e=pair.first;e!=pair.second;++e)
//            {
//                auto target = boost::target(*e,mGraph);
//                if(get(colIndex,target) > col)
//                    col = get(colIndex,target);
//            }
//                put(colIndex, v, col+1);
//        }

//        if(boost::in_degree(v, mGraph) > 1)
//        {
//            int col = get(colIndex, get(domTreePredMap,v));
//            auto pair = boost::in_edges(v,mGraph);
//            for(auto e=pair.first;e!=pair.second;++e)
//            {
//                auto source = boost::source(*e,mGraph);
//                if(get(colIndex,source) < col)
//                    col = get(colIndex,source);
//            }
//            put(colIndex, v, col);
//        }

////        if(boost::out_degree(v, mGraph) > 1)
////        {
////            if (get(colIndex, get(domTreePredMap,v)) < get(colIndex, *(ii-1)))
////            {
//////                put(colIndex, v, get(colIndex, *(ii-1))+1);
////                auto dv = get(domTreePredMap,v);
////                while (dv != boost::graph_traits<revision_graph>::null_vertex())
////                {
////                    if(boost::out_degree(dv, mGraph) > 1 || boost::in_degree(dv, mGraph) > 1)
////                        break;
////                    put(colIndex, dv, get(colIndex,v));
////                    dv = get(domTreePredMap,dv);
////                }
////            }
////            else
////                put(colIndex, v, get(colIndex, *(ii-1)));
////        }
    }
    setMinimumHeight(25*boost::num_vertices(mGraph));
}

void RevisionTreeWidget::initializeGL()
{
    QOpenGLWidget::initializeGL();
}

void RevisionTreeWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resizeGL(w,h);
}

void RevisionTreeWidget::paintGL()
{
    QOpenGLWidget::paintGL();
    glClearColor(1,1,1,1);
}

void RevisionTreeWidget::paintEvent(QPaintEvent *event)
{
    QOpenGLWidget::paintEvent(event);

    QPainter painter(this);

    painter.setBrush(Qt::red);
    painter.setPen(Qt::black);

    const int offset{20};
    const float width = 25;
    const float radius = 8;

    boost::associative_property_map<IndexMap> colIndex(mColumnMap);
    boost::associative_property_map<IndexMap> rowIndex(mRowMap);

    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
        int row = get(rowIndex, v);
        int col = get(colIndex, v);
        if(!boost::in_degree(v,mGraph))
        {
            painter.setBrush(Qt::black);
            painter.drawRect(width*col + offset - radius, width*row - radius, radius*2, radius*2);
        }
        else if(!boost::out_degree(v,mGraph))
        {
            painter.setBrush(Qt::yellow);
            painter.drawRect(width*col + offset - radius, width*row - radius, radius*2, radius*2);
        }
        else if(boost::in_degree(v,mGraph) > 1 && boost::out_degree(v,mGraph) > 1)
        {
            painter.setBrush(Qt::magenta);
            painter.drawRect(width*col + offset - radius, width*row - radius, radius*2, radius*2);
        }
        else if(boost::in_degree(v,mGraph) > 1)
        {
            painter.setBrush(Qt::red);
            painter.drawRect(width*col + offset - radius, width*row - radius, radius*2, radius*2);
        }
        else if(boost::out_degree(v,mGraph) > 1)
        {
            painter.setBrush(Qt::blue);
            painter.drawRect(width*col + offset - radius, width*row - radius, radius*2, radius*2);
        }
        else
        {
            painter.setBrush(Qt::green);
            painter.drawEllipse(QPointF{width*col + offset, width*row},
                                radius, radius);
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
    QOpenGLWidget::resizeEvent(e);
}

bool RevisionTreeWidget::event(QEvent *e)
{
    QOpenGLWidget::event(e);
}

