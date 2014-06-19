#ifndef REVISIONMODEL_H
#define REVISIONMODEL_H

#include <QAbstractItemModel>
#include "revisionnode.h"

class RevisionModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RevisionModel(QObject *parent = 0);

    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    RevisionNode *root() const;

protected:
    RevisionNode *mRoot;

signals:

public slots:

};

#endif // REVISIONMODEL_H
