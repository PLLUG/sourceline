#include "filemodel.h"

FileModel::FileModel(QWidget *parent) : QFileSystemModel(parent)
{
    addToHash(FileVisibleRole,static_cast<QString>(":/splash/img/added.png"));
    addToHash(FileModifiedRole,static_cast<QString>(":/splash/img/up.png"));
}

QVariant FileModel::data(const QModelIndex &index, int role)
{
    QVariant result = "";
    switch (role)
    {
        case Roles::FileVisibleRole:
            result = hash[FileVisibleRole];
            break;
        case Roles::FileModifiedRole:
            result = hash[FileModifiedRole];
            break;
        default:
            result = QFileSystemModel::data(index,role);
            break;
    }
    return result;
}

void FileModel::addToHash(FileModel::Roles role, QString &path)
{
    hash.insert(role,path);
}

