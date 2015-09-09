#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QWidget>
#include <QFileSystemModel>
#include <QHash>

class FileModel : public QFileSystemModel
{
public:

    enum Roles
    {
        FileAttributeRole = Qt::UserRole,
        FileAttributeIconRole = Qt::UserRole + 1,
    };

    FileModel(QWidget *parent);

    QVariant data(const QModelIndex &index, int role);

    void setIconForAttributes(quint32 attributes, const QString &path);

private:
    QString iconPathForIndex(const QModelIndex &);

private:
    QHash<quint32, QString> mIcons;
};

#endif // FILEMODEL_H
