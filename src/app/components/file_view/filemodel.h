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
        FileAttributeRole = Qt::UserRole,
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
    QVariant data(const QModelIndex &index, int role);

    /*!
     * \brief add pair role->icon to hash
     * \param role for file
     * \param path to icon
     */
    void setIconForRole(QString &path);

private:

    QString pathToIcon;
};

#endif // FILEMODEL_H
