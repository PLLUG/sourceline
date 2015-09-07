#ifndef DFS_VISITOR
#define DFS_VISITOR
/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Halyna Butovych (galynabutovych@gmail.com)                    ***
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

#include <boost/property_map/dynamic_property_map.hpp>
#include <map>
#include <iostream>
#include "revisionnode.h"

template <typename IndexMap, typename vertex, typename graph>
class dfs_visitor : public boost::default_dfs_visitor
{
public:
    dfs_visitor(IndexMap &colMap, IndexMap &orderMap):
        mColumnIndexMap{colMap}
      ,mOrderMap{orderMap}
      ,mVerticesCount{0}
      ,mPrevVertex{boost::graph_traits<graph>::null_vertex()}
      ,mPrevTreeEdgeTarget{boost::graph_traits<graph>::null_vertex()}
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
    }

    template < typename Vertex, typename Graph >
    /*!
     * \brief start_vertex is invoked on the source vertex once before the start of the search
     * \param v
     * \param g
     */
    void start_vertex(Vertex v, const Graph & g)
    {
        Q_UNUSED(g)
        put(mColumnIndexMap,v,0);
    }

    template < typename Edge, typename Graph >
    /*!
     * \brief examine_edge is invoked on every out-edge of each vertex after it is discovered
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
     * \brief is invoked when a vertex is encountered for the first time
     * \param u vertex
     * \param g graph
     */
    void discover_vertex(Vertex v, const Graph & g)
    {
        Q_UNUSED(g)
        if(boost::graph_traits<graph>::null_vertex() == mPrevVertex)
            put(mOrderMap,v,0);
        else
            put(mOrderMap,v,get(mOrderMap,mPrevVertex)+1);
        mPrevVertex = v;
    }

    template < typename Vertex, typename Graph >
    /*!
     * \brief finish_vertex is invoked on a vertex after all of its out edges have been added to the search tree
     * and all of the adjacent vertices have been discovered (but before their out-edges have been examined).
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
     * \brief back_edge is invoked on the back edges in the graph
     * \param e
     * \param g
     */
    void back_edge(Edge e, Graph g)
    {
        Q_UNUSED(e)
        Q_UNUSED(g)
    }

    template < typename Edge, typename Graph >
    /*!
     * \brief forward_or_cross_edge is invoked on forward or cross edges in the graph
     * \param e
     * \param g
     */
    void forward_or_cross_edge(Edge e, Graph g)
    {
        Q_UNUSED(e)
        Q_UNUSED(g)
        std::cout << "forward_or_cross_edge" << e << std::endl;
    }

    template < typename Edge, typename Graph >
    /*!
     * \brief tree_edge is invoked on each edge as it becomes a member of the edges that form the search tree.
     * If you wish to record predecessors, do so at this event point.
     * \param e
     * \param g
     */
    void tree_edge(Edge e, Graph g)
    {
        std::cout << "tree_edge" << e << std::endl;
        if(boost::source(e,g) == mPrevTreeEdgeTarget)
        {
            put(mColumnIndexMap, boost::target(e,g), get(mColumnIndexMap,boost::source(e,g)));
        }
        else
        {
            if(boost::graph_traits<graph>::null_vertex() != mPrevTreeEdgeTarget)
                put(mColumnIndexMap, boost::target(e,g), get(mColumnIndexMap,mPrevTreeEdgeTarget)+1);
        }
        mPrevTreeEdgeTarget = boost::target(e,g);
    }

private:
    boost::associative_property_map<IndexMap> mColumnIndexMap;
    boost::associative_property_map<IndexMap> mOrderMap;
    int mVerticesCount;
    vertex mPrevVertex;
    vertex mPrevTreeEdgeTarget;
    VertexIntMap mRowMap;
};


#endif // DFS_VISITOR

