#include "filemodel.h"

#include <QString>

FileModel::FileModel(QWidget *parent) : QFileSystemModel(parent)
{
    //setIconForRole(1,QStringLiteral(":/splash/img/added.png"));
}

QVariant FileModel::data(const QModelIndex &index, int role)
{
    QVariant result = "";
    if (role == Roles::FileAttributeIconRole)
    {
        result = hashRoleIcon[Roles::FileAttributeRole];
    }
    else
    {
        result = QFileSystemModel::data(index,role);
    }

    return result;
}

void FileModel::setIconForRole(Roles role, QString &path)
{
    hashRoleIcon.insert(role,path);
}

