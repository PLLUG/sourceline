#include "filemodel.h"

#include <QString>

/*!
 * \brief constructor FileModel
 * \param parent
 */
FileModel::FileModel(QWidget *parent) : QFileSystemModel(parent)
{
    //setIconForRole(1,QStringLiteral(":/splash/img/added.png"));
}

/*!
 * \brief set icon for role
 * \param index item on model
 * \param role item
 * \return icon
 */
QVariant FileModel::data(const QModelIndex &index, int role)
{
    QVariant result;

    switch (role)
    {
    case Roles::FileAttributeIconRole:
        result = iconPathForIndex(index);
        break;
    default:
        result = QFileSystemModel::data(index,role);
        break;
    }

    return result;
}

/*!
 * \brief add pair role->icon to hash
 * \param role for file
 * \param path to icon
 */
void FileModel::setIconForAttributes(quint32 attributes, QString path)
{
    mIcons.insert(attributes, path);
}

/*!
 * \brief Returns icon for given index if any.
 * \return Path to icon. If there is no icon - return empty string.
 */
QString FileModel::iconPathForIndex(const QModelIndex &index)
{
    QString iconPath;

    if (fileInfo(index).absoluteFilePath().contains(rootPath()))
    {
        quint32 attribute = QFileSystemModel::data(index, FileAttributeRole).toUInt();
        iconPath = mIcons.value(attribute);
    }
    return iconPath;
}

