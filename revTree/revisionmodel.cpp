#include "revisionmodel.h"
#include "createtree.h"

RevisionModel::RevisionModel(QObject *parent) :
    QAbstractItemModel(parent)
{
    CreateTree ct;
    root = ct.create();
}

int RevisionModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

int RevisionModel::rowCount(const QModelIndex &parent) const
{
    RevisionNode *node = 0;
    if ( !parent.isValid() )
        node = root;
    else
        node = static_cast<RevisionNode *>(parent.internalPointer());
    if ( node )
        return node->children.size();
    return 0;
}

QVariant RevisionModel::data(const QModelIndex &index, int role) const
{
    if ( role == Qt::DisplayRole )
    {
        if ( index.column() == 0 )
            return QVariant(static_cast<RevisionNode *>(index.internalPointer())->revId());
        if ( index.column() == 1 )
            return QVariant(static_cast<RevisionNode *>(index.internalPointer())->message());
    }
    return QVariant();
}

QModelIndex RevisionModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( !hasIndex(row, column, parent) )
        return QModelIndex();

    RevisionNode *parentNode;
    if ( !parent.isValid() )
        parentNode = root;
    else
        parentNode = static_cast<RevisionNode *>(parent.internalPointer());

    if ( !parentNode )
        return QModelIndex();

    if ( parentNode->children.size() > row )
    {
        return createIndex(row, column, parentNode->children.at(row));
    }
    return QModelIndex();
}

QModelIndex RevisionModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() )
        return QModelIndex();

    RevisionNode *childItem = static_cast<RevisionNode*>(child.internalPointer());
    RevisionNode *parentItem = childItem->parent;

    if ( parentItem == root )
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}
