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

//maybe use labeled_graph where labeles are commit ids (and remove id from property)? - no
//#include <boost/graph/labeled_graph.hpp>
//using labeled_graph = boost::labeled_graph<revision_graph,
//std::string // node ID
//>;

//boost bundled properties
//modified adjacency_list.hpp because of compile error
//TODO: choose the best containers for V and E

RevisionModel::RevisionModel(QObject *parent):
    QAbstractItemModel(parent),
    mInitialNode{boost::graph_traits<revision_graph>::null_vertex()}
{
    RevisionNode initialCommit = {
        "94eaeb7661f3960d8ccb2be1be2405eea111ab0c",
        "Initial commit",
        "Alex",
        QDateTime::currentDateTime()
    };

    RevisionNode commit1 = {
        "0fe7872d5dbb295da057a2f7db558edd884f6284",
        "add project description;",
        "Volodymyr",
        QDateTime::currentDateTime()
    };

    RevisionNode commit2 = {
        "0fe4872d2295rr2da057a2f789758edd884f6286",
        "lalala;",
        "Halyna",
        QDateTime::currentDateTime()
    };

    setInitialNode(initialCommit);
    addNode(initialCommit, commit1);
    addNode(commit1, commit2);

    debugTree(mGraph);
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
 * \brief RevisionModel::addNode Adds node and creates path from parent node to that node.
 * \param pParentInfo parent node
 * \param pNodeInfo node
 */
void RevisionModel::addNode(const RevisionNode &pParentInfo, const RevisionNode &pNodeInfo)
{
    vertex v_new = boost::graph_traits<revision_graph>::null_vertex();
    vertex v_parent = boost::graph_traits<revision_graph>::null_vertex();
    //find vertexes in graph
    for(auto v : mNodes)
    {
        auto name = mGraph[v].name;
        if(name == pNodeInfo.name)
        {
            v_new = v;
            if(boost::graph_traits<revision_graph>::null_vertex() != v_parent)
                break;
        }
        else if(name == pParentInfo.name)
        {
            v_parent = v;
            if(boost::graph_traits<revision_graph>::null_vertex() != v_new)
                break;
        }
    }
    //if parent not found exit (?)
    if(v_parent == boost::graph_traits<revision_graph>::null_vertex())
        return;
    //create if not found
    if(v_new == boost::graph_traits<revision_graph>::null_vertex())
    {
        v_new = boost::add_vertex(pNodeInfo, mGraph);
        mNodes.insert(v_new);
    }
    boost::add_edge(v_parent, v_new, mGraph);
}

/*!
 * \brief RevisionModel::setInitialNode Sets the node that is a parent for all other nodes (the top node).
 * \param pNodeInfo
 */
void RevisionModel::setInitialNode(const RevisionNode &pNodeInfo)
{
    vertex v_initial = boost::graph_traits<revision_graph>::null_vertex();
    //find vertexes in graph
    for(auto v : mNodes)
    {
        if(mGraph[v].name == pNodeInfo.name)
        {
            v_initial = v;
            break;
        }
    }
    //exit if parent not found (?)
    if(v_initial == boost::graph_traits<revision_graph>::null_vertex())
    {
        v_initial = boost::add_vertex(pNodeInfo, mGraph);
        mNodes.insert(v_initial);
        mInitialNode = v_initial;
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
    return 0;
}

int RevisionModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}

QVariant RevisionModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

vertex RevisionModel::initialNode() const
{
    return mInitialNode;
}

revision_graph RevisionModel::graph() const
{
    return mGraph;
}

