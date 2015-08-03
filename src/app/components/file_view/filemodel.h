#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QWidget>
#include <QFileSystemModel>
#include <QHash>

class FileModel : public QFileSystemModel
{
public:
    enum Roles {
        FileVisibleRole = Qt::DecorationRole,
        FileModifiedRole = Qt::UserRole + 1,
    };

    FileModel(QWidget *parent);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);

    QHash<int,QString> hash;

    void addToHash(Roles role, QString &path);

};

#endif // FILEMODEL_H
