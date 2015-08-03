#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QWidget>
#include <QFileSystemModel>
#include <QHash>

class FileModel : public QFileSystemModel
{
public:

    /*!
     * \brief roles for icons for files
     */
    enum Roles {
        FileAttributeRole = Qt::DecorationRole,
        FileAttributeIconRole = Qt::UserRole + 1,
    };

    /*!
     * \brief constructor FileModel
     * \param parent
     */
    FileModel(QWidget *parent);

    /*!
     * \brief set icon for role
     * \param index item on model
     * \param role item
     * \return icon
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole);

    /*!
     * \brief add pair role->icon to hash
     * \param role for file
     * \param path to icon
     */
    void setIconForRole(Roles role, QString &path);

private:

    /*!
     * \brief hash role->icon
     */
    QHash<int,QString> hashRoleIcon;
};

#endif // FILEMODEL_H
