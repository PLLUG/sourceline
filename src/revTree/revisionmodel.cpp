#include "revisionmodel.h"
#include "createtree.h"

RevisionModel::RevisionModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    CreateTree ct;
    mRoot = ct.create();
}

int RevisionModel::columnCount(const QModelIndex &) const
{
    return 2;
}

int RevisionModel::rowCount(const QModelIndex &parent) const
{
    RevisionNode *node = 0;
    if ( !parent.isValid() )
        node = mRoot;
    else
        node = static_cast<RevisionNode *>(parent.internalPointer());
    if ( node )
        return node->branches.size();
    return 0;
}

QVariant RevisionModel::data(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole )
    {
        if ( index.column() == 0 )
            return QVariant(static_cast<RevisionNode *>(index.internalPointer())->revId());
        if ( index.column() == 1 )
            return QVariant(static_cast<RevisionNode *>(index.internalPointer())->data(RevisionNode::IDR_DisplayRole));
    }
    return QVariant();
}

QModelIndex RevisionModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( !hasIndex(row, column, parent) )
        return QModelIndex();

    RevisionNode *parentNode;
    if ( !parent.isValid() )
        parentNode = mRoot;
    else
        parentNode = static_cast<RevisionNode *>(parent.internalPointer());

    if ( !parentNode )
        return QModelIndex();

    if ( parentNode->branches.size() > row )
    {
        return createIndex(row, column, parentNode->branches.at(row));
    }
    return QModelIndex();
}

QModelIndex RevisionModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() )
        return QModelIndex();

    RevisionNode *childItem = static_cast<RevisionNode*>(child.internalPointer());
    RevisionNode *parentItem = childItem->parent;

    if ( parentItem == mRoot )
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

RevisionNode *RevisionModel::root() const
{
    return mRoot;
}
