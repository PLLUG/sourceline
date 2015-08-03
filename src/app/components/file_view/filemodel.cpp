#include "filemodel.h"

FileModel::FileModel(QWidget *parent) : QFileSystemModel(parent)
{
    setIconForRole(1,static_cast<QString>(":/splash/img/added.png"));
}

QVariant FileModel::data(const QModelIndex &index, int role)
{
    QVariant result = "";
    if (role == Roles::FileAttributeIconRole)
    {
        result = (*hashRoleIcon.begin());
    }
    else
    {
        result = QFileSystemModel::data(index,role);
    }

    return result;
}

void FileModel::setIconForRole(int id, QString &path)
{
    hashRoleIcon.insert(id,path);
}

