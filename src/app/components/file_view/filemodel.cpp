#include "filemodel.h"

#include <QString>

FileModel::FileModel(QWidget *parent) : QFileSystemModel(parent)
{
    //setIconForRole(1,QStringLiteral(":/splash/img/added.png"));
    pathToIcon = "";
}

QVariant FileModel::data(const QModelIndex &index, int role)
{
    QVariant result = "";
    if (role == Roles::FileAttributeIconRole)
    {
        result = pathToIcon;
    }
    else
    {
        result = QFileSystemModel::data(index,role);
    }

    return result;
}

void FileModel::setIconForRole(QString &path)
{
    pathToIcon = path;
}

