/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Volodymyr Kochyn  (vovakochyn@gmail.com)                      ***
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

#ifndef REVISIONTREE_H
#define REVISIONTREE_H

#include "revisionnode.h"
#include <iostream>
#include <vector>
#include <string>
//#include <boost/graph/adjacency_list.hpp>
//#include <boost/tuple/tuple.hpp>
//using namespace boost;

QT_FORWARD_DECLARE_CLASS(RevisionTableModel)
/*
namespace boost
{
   template <> struct graph_traits<RevisionNode>
    {
        typedef int vertex_descriptor;
        typedef std::pair <vertex_descriptor, vertex_descriptor> edge_descriptor;
        typedef boost::undirected_tag directed_category;
        typedef boost::disallow_parallel_edge_tag edge_parallel_category;
        typedef vertex_list_graph_tag traversal_category;

//        typedef VertexIteratorImpl vertex_iterator;
//        typedef OutEdgeIteratorImpl out_edge_iterator;
        typedef int degree_size_type;
        typedef int vertices_size_type;

        typedef void in_edge_iterator;
        typedef void edge_iterator;
        typedef void edges_size_type;
    };
}

typedef adjacency_list<boost::listS, boost::vecS, boost::directedS, RevisionNode> Graph;
typedef graph_traits<Graph>::vertex_descriptor Vertex;
//typedef graph_traits<RevisionNode>::edge_descriptor OutEdgeIterator;
//typedef graph_traits<RevisionNode>::vertices_size_type VerticlesSize;

//VerticlesSize out_degree(Vertex v, const Graph &g)
//{
//    VerticlesSize result = 0;

//    std::pair<OutEdgeIterator, OutEdgeIterator> edges = out_edges(v, g);
//    for (OutEdgeIterator i = edges.first; i != edges.second; ++i) {
//        ++result;
//    }

//    return result;
//}

class RevisionTree
{
public:
    RevisionTree(RevisionTableModel *parent = 0);

    void addCommit(const QString &message);
    Vertex addBranch(const QString &message);

    bool switchTo(const Vertex &v);
    QVariant data(const Vertex &v, RevisionNode::ItemDataRole role) const;
    Vertex getVertex(int index) const;
    RevisionNode node(const Vertex &v) const;
    int vertexSize() const;
    QString currentBranch() const;
    const QList<Vertex>& branches() const { return mBranches; }
    void show();

private:
    Graph g;
    Vertex currentVertex;
    QList<Vertex> mBranches;
    RevisionNode current;
    RevisionTableModel *mParentModel;

    void update();
};*/

#endif // REVISIONTREE_H
