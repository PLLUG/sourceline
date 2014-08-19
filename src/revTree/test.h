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

#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <boost/graph/adjacency_list.hpp>

class GameField
{
public:

    GameField();

    bool canPass(int x, int y) const { return true; }
    int getWidth() const { return 10; }
    int getHeight() const { return 10; }
};

struct game_field_traversal_catetory:
    public boost::vertex_list_graph_tag,
    public boost::incidence_graph_tag
{
};

class VertexIteratorImpl : public boost::forward_iterator_helper<VertexIteratorImpl, Vertex, std::ptrdiff_t, Vertex*, Vertex>
{
public:
    VertexIteratorImpl() : mField(NULL), mIndex(0) {}
    VertexIteratorImpl(const GameField& field, int index) : mField(&field), mIndex(index) {}

    void operator++ ()
    {
        if (isValid()) {
            ++mIndex;
        }
    }
    bool operator== (const VertexIteratorImpl& anotherIterator) const { return mIndex == anotherIterator.mIndex; }
    Vertex operator*() const { return mIndex; }

private:
    bool isValid() { return (mField != NULL) && (mIndex < num_vertices(*mField)) && (mIndex >=0); }

    int mIndex;
    const GameField* mField;
};

namespace boost
{
   template <> struct graph_traits<GameField>
    {
        typedef int vertex_descriptor;
        typedef std::pair <vertex_descriptor, vertex_descriptor> edge_descriptor;
        typedef boost::undirected_tag directed_category;
        typedef boost::disallow_parallel_edge_tag edge_parallel_category;
        typedef game_field_traversal_catetory traversal_category;

        typedef VertexIteratorImpl vertex_iterator;
        typedef OutEdgeIteratorImpl out_edge_iterator;
        typedef int degree_size_type;
        typedef int vertices_size_type;

        typedef void in_edge_iterator;
        typedef void edge_iterator;
        typedef void edges_size_type;
    };
}

typedef boost::graph_traits<GameField>::vertex_descriptor Vertex;
typedef boost::graph_traits<GameField>::edge_descriptor Edge;
typedef boost::graph_traits<GameField>::vertex_iterator VertexIterator;
typedef boost::graph_traits<GameField>::out_edge_iterator OutEdgeIterator;
typedef boost::graph_traits<GameField>::degree_size_type DegreeSizeType;
typedef boost::graph_traits<GameField>::vertices_size_type VerticesSizeType;

std::pair<int, int> getCoordinates(const Vertex position, const GameField& graph)
{
    return std::make_pair(position % graph.getWidth(), position / graph.getWidth());
}

Vertex getVertex(int x, int y, const GameField& graph)
{
    return x + y * graph.getWidth();
}

VerticesSizeType num_vertices(const GameField& graph)
{
    return graph.getWidth() * graph.getHeight();
}

std::pair<VertexIterator, VertexIterator> vertices(const GameField& graph)
{
    return std::make_pair(VertexIterator(graph, 0), VertexIterator(graph, num_vertices(graph)));
}

Vertex source(Edge edge, const GameField &graph)
{
    return edge.first;
}

Vertex target(Edge edge, const GameField &graph)
{
    return edge.second;
}
#endif // TEST_H
