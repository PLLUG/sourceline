#include "revisiontablemodel.h"
#include "createtree.h"
#include <QDebug>

RevisionTableModel::RevisionTableModel()
{
    CreateTree ct;
    mRoot = ct.create();

    tree = 0;
    createTree();
}

int RevisionTableModel::rowCount(const QModelIndex &) const
{
    if (tree)
        return tree->vertexSize();
    return 0;
}

int RevisionTableModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant RevisionTableModel::data(const QModelIndex &index, int role) const
{
    if (!tree)
        return QVariant();
    if ( role == Qt::DisplayRole )
    {
//        if ( index.column() == 2 )
//            return mRoot->node(index.row())->data(RevisionNode::IDR_DisplayRole);
//        if ( index.column() == 1 )
//            return QVariant(mRoot->node(index.row())->revId());
//        if ( index.column() == 0 )
//        {
//            const RevisionNode *node = mRoot->node(index.row());
//            return node->data(RevisionNode::IDR_DrawRole);
//        }
        if ( index.column() == 2 )
        {
            if (index.row() < tree->vertexSize())
                return tree->data(tree->getVertex(index.row()), RevisionNode::IDR_DisplayRole);
        }
        else if ( index.column() == 1 )
        {
            return tree->node(tree->getVertex(index.row())).revId();
        }
        else if ( index.column() == 0 )
        {
            return tree->node(tree->getVertex(index.row())).data(RevisionNode::IDR_DrawRole);
        }
    }
    if ( role == Qt::TextAlignmentRole )
    {
        if ( index.column() == 1 )
            return Qt::AlignCenter;
    }
    return QVariant();
}

QVariant RevisionTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if ( role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        if ( section == 0 )
            return "Graph";
        if ( section == 1 )
            return "rev.";
        if ( section == 2 )
            return "Message";
    }
    return QVariant();
}

RevisionTree *RevisionTableModel::createTree()
{
    if (!tree)
    {
        tree = new RevisionTree(this);
        tree->addCommit("init");
        tree->addCommit("seccond test commit");
        tree->addBranch("Branch");
        emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
    }
    return tree;
}

void RevisionTableModel::dataChange()
{
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}
