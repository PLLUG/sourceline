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

#include "revisionmodel.h"
#include <boost/graph/graphviz.hpp>
#include <boost/graph/iteration_macros.hpp>

//maybe use labeled_graph where labeles are commit ids (and remove id from property)? - no
//#include <boost/graph/labeled_graph.hpp>
//using labeled_graph = boost::labeled_graph<revision_graph,
//std::string // node ID
//>;

//boost bundled properties
//modified adjacency_list.hpp because of compile error
//TODO: choose the best containers for V and E

RevisionModel::RevisionModel(QObject *parent):
    QAbstractItemModel(parent)
{
}

/*!
 * \brief RevisionModel::debugTree Represent graph in DOT format and send to cout
 * \param graph
 */
void RevisionModel::debugTree(const revision_graph &graph) const
{
    std::cout << "======== rev tree =========" << std::endl;
    boost::write_graphviz(std::cout, graph);
    std::cout << "======= end rev tree ======" << std::endl;
}

/*!
 * \brief RevisionModel::addNode Add new node (vertex to graph), call for each parent if node has many parents (e.g. merge)
 * \param pParentID ID of parent, may be empty if node nas no parent (e.g. initial commit or filtered data)
 * \param pNodeInfo Info about new node
 */
void RevisionModel::addNode(const std::string &pParentID, const RevisionNode &pNodeInfo)
{
    vertex v_new = boost::graph_traits<revision_graph>::null_vertex();
    vertex v_parent = boost::graph_traits<revision_graph>::null_vertex();
    //find vertexes in graph if they are present
    BGL_FORALL_VERTICES(v, mGraph, revision_graph)
    {
       const auto &name = mGraph[v].name;
        if(pNodeInfo.name == name)
        {
            v_new = v;
            if(boost::graph_traits<revision_graph>::null_vertex() != v_parent || pParentID.empty())
                break;
        }
        else if(pParentID == name)
        {
            v_parent = v;
            if(boost::graph_traits<revision_graph>::null_vertex() != v_new)
                break;
        }
    }
    if(boost::graph_traits<revision_graph>::null_vertex() == v_parent)
    {
        // parent not found
        // node has no parent if parent is empty
        if(!pParentID.empty())
        {
            RevisionNode parentNodeInfo;
            parentNodeInfo.name = pParentID;
            v_parent = boost::add_vertex(parentNodeInfo, mGraph);
        }
    }
    if(boost::graph_traits<revision_graph>::null_vertex() == v_new)
    {
        //create if not found
        v_new = boost::add_vertex(pNodeInfo, mGraph);
    }
    else
    {
        // node already in, modify data, because probably it was empty
        mGraph[v_new].author = pNodeInfo.author;
        mGraph[v_new].created = pNodeInfo.created;
        mGraph[v_new].message = pNodeInfo.message;
    }
    if(boost::graph_traits<revision_graph>::null_vertex() != v_parent &&
            boost::graph_traits<revision_graph>::null_vertex() != v_new &&
            !boost::edge(v_parent,v_new,mGraph).second // edge doesn't exist
            )
    {
        boost::add_edge(v_parent, v_new, mGraph);
    }
}

QModelIndex RevisionModel::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex RevisionModel::parent(const QModelIndex &child) const
{
    //return a node from which the edge to child starts
    return QModelIndex();
}

int RevisionModel::rowCount(const QModelIndex &parent) const
{
    return boost::num_vertices(mGraph);
}

int RevisionModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant RevisionModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

revision_graph RevisionModel::graph() const
{
    debugTree(mGraph);
    return mGraph;
}

