#ifndef BFS_VISITOR
#define BFS_VISITOR

#include <boost/property_map/dynamic_property_map.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <set>
#include <map>
#include "revisionnode.h"
template <typename IndexMap, typename vertex, typename graph>
class bfs_visitor : public boost::default_bfs_visitor
{
public:
    bfs_visitor(IndexMap &colMap, IndexMap &bfsOrderMap, IndexMap &rowMap):
        mRowIndexMap{mRowMap}
      ,mColumnIndexMap{colMap}
      ,mBFSOrderMap{bfsOrderMap}
      ,mDiscoveredVerticesCount{0}
      ,mPrevVertex{boost::graph_traits<graph>::null_vertex()}
      ,mPrevTreeEdgeTarget{boost::graph_traits<graph>::null_vertex()}
    {
        Q_UNUSED(rowMap)
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
        put(mColumnIndexMap, v, -1);
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
        Q_UNUSED(e)
        Q_UNUSED(g)
    }

    template < typename Vertex, typename Graph >
    /*!
     * \brief discover_vertex is invoked the first time the algorithm encounters vertex u.
     * All vertices closer to the source vertex have been discovered,
     * and vertices further from the source have not yet been discovered.
     * \param u vertex
     * \param g graph
     */
    void discover_vertex(Vertex v, const Graph & g)
    {
        Q_UNUSED(g)
        if(!mDiscoveredVerticesCount)
        {
            put(mColumnIndexMap,v,0);
        }
        put(mBFSOrderMap,v,mDiscoveredVerticesCount++);
    }

    template < typename Vertex, typename Graph >
    /*!
     * \brief finish_vertex
     * \param v
     * \param g
     */
    void finish_vertex(Vertex v, Graph& g)
    {
        Q_UNUSED(v)
        Q_UNUSED(g)
    }

    template < typename Edge, typename Graph >
    /*!
     * \brief non_tree_edge is invoked (in addition to examine_edge()) if the edge is not a tree edge
     * \param e
     * \param g
     */
    void non_tree_edge(Edge e, Graph g)
    {
        Q_UNUSED(e)
        Q_UNUSED(g)
    }

    template < typename Edge, typename Graph >
    /*!
     * \brief tree_edge  is invoked (in addition to examine_edge()) if the edge is a tree edge.
     * The target vertex of edge e is discovered at this time.
     * \param e
     * \param g
     */
    void tree_edge(Edge e, Graph g)
    {
        put(mRowIndexMap, boost::target(e,g), get(mRowIndexMap,boost::source(e,g))+1);
        {
            if(mPrevTreeEdgeTarget != boost::graph_traits<graph>::null_vertex())
            {
                put(mColumnIndexMap, boost::target(e,g), get(mColumnIndexMap,mPrevTreeEdgeTarget)+1);
            }
            else
            {
                put(mColumnIndexMap, boost::target(e,g), get(mColumnIndexMap,boost::source(e,g)));
            }
            mPrevTreeEdgeTarget = boost::target(e,g);
        }
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
        mPrevTreeEdgeTarget = boost::graph_traits<graph>::null_vertex();
        if(boost::graph_traits<graph>::null_vertex() != mPrevVertex)
        {
            int col{0};
            if(get(mRowIndexMap,mPrevVertex) == get(mRowIndexMap,v))
            {
                col = get(mColumnIndexMap,mPrevVertex)+1;
            }
            else
            {
                col = 0;
            }
            put(mColumnIndexMap, v, col);
        }
        mPrevVertex = v;
    }

private:
    boost::associative_property_map<IndexMap> mRowIndexMap;
    boost::associative_property_map<IndexMap> mColumnIndexMap;
    boost::associative_property_map<IndexMap> mBFSOrderMap;
    int mDiscoveredVerticesCount;
    vertex mPrevVertex;
    vertex mPrevTreeEdgeTarget;
    VertexIntMap mRowMap;
};
#endif // BFS_VISITOR

