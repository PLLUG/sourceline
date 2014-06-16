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
    if ( parent.isValid() ) {
        RevisionNode *node = static_cast<RevisionNode *>(parent.internalPointer());
        if ( node )
            return node->children.size();
    }
    return root->children.size();
}

QVariant RevisionModel::data(const QModelIndex &index, int role) const
{
    //
}

QModelIndex RevisionModel::index(int row, int column, const QModelIndex &parent) const
{
    if ( !parent.isValid() ) {
        return createIndex(row, column, root->children.at(row));
    }
    if ( !parent.child(row, column).isValid() ) {
        RevisionNode *node = static_cast<RevisionNode *>(parent.internalPointer());
        if ( node )
            return createIndex(row, column, node->children.at(row));
    } else {
        parent.child(row, column);
    }
    return QModelIndex();
}

QModelIndex RevisionModel::parent(const QModelIndex &child) const
{
    if ( !child.isValid() )
        return QModelIndex();

    return child.parent();
}
