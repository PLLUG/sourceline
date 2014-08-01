#include "revisiontree.h"
#include "revisiontablemodel.h"
#include <QDebug>

RevisionTree::RevisionTree(RevisionTableModel *parent) :
    current(0),
    mParentModel(parent)
{
}

void RevisionTree::addCommit(const QString &message)
{
    if (vertices(g).second - vertices(g).first == 0)
    {
        current = RevisionNode(message);
        currentVertex = add_vertex(current, g);
        mBranches.append(currentVertex);
        g[currentVertex].updateData();
    }
    else
    {
        RevisionNode tmp(message);
        Vertex u = add_vertex(tmp, g);
        g[u].mPos = g[currentVertex].mPos;
        add_edge(currentVertex, u, g);
        currentVertex = u;
    }
    update();
    if (mParentModel)
        mParentModel->dataChange();
}

Vertex RevisionTree::addBranch(const QString &message)
{
    RevisionNode tmp(message);
    Vertex u = add_vertex(tmp, g);
    mBranches.append(u);
    add_edge(currentVertex, u, g);
    g[u].mPos = g[currentVertex].mPos + 1;
    currentVertex = u;
    if (mParentModel)
        mParentModel->dataChange();
    update();
    return u;
}

bool RevisionTree::switchTo(const Vertex &v)
{
    for (int i = 0; i < mBranches.size(); ++i)
    {
        if (v == mBranches.at(i))
        {
            currentVertex = v;
            return true;
        }
    }
    return false;
}

QVariant RevisionTree::data(const Vertex &v, RevisionNode::ItemDataRole role) const
{
    return g[v].data(role);
}

Vertex RevisionTree::getVertex(int index) const
{
    graph_traits < Graph >::vertex_iterator i, end;
    int in = 0;
    for (tie(i, end) = vertices(g); i != end; ++i, ++in)
    {
        if (index == in)
            return *i;
    }
    return Vertex ();
}

RevisionNode RevisionTree::node(const Vertex &v) const
{
    return g[v];
}

int RevisionTree::vertexSize() const
{
    graph_traits < Graph >::vertex_iterator i, end;
    tie(i, end) = vertices(g);
    return (end - i);
}

QString RevisionTree::currentBranch() const
{
    return g[currentVertex].data(RevisionNode::IDR_DisplayRole).toString();
}

void RevisionTree::show()
{
    graph_traits < Graph >::vertex_iterator i, end;
    graph_traits < Graph >::adjacency_iterator a, aend;
    for (tie(i, end) = vertices(g); i != end; ++i)
    {
        qDebug() << g[*i].data(RevisionNode::IDR_DisplayRole);

        tie(a, aend) = adjacent_vertices(*i, g);
        for (;a != aend; ++a)
        {
            qDebug() << "\t" << g[*a].data(RevisionNode::IDR_DisplayRole);
        }
    }
}

void RevisionTree::update()
{
    graph_traits < Graph >::vertex_iterator i, end;
    graph_traits < Graph >::adjacency_iterator a, aend;
    for (tie(i, end) = vertices(g); i != end; ++i)
    {
        tie(a, aend) = adjacent_vertices(*i, g);
        int count = 0;
        for (;a != aend; ++a, ++count)
        {}
        g[*i].branchCount = ((count-1) >= 1) ? count : 0;
        g[*i].isLast = ((end - i) == 1);
        g[*i].updateData();
    }
}
