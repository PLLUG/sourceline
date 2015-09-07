#ifndef EXPLORERITEMDELEGATE_H
#define EXPLORERITEMDELEGATE_H

#include <QStyledItemDelegate>

class FileModel;

class ExplorerItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ExplorerItemDelegate(QObject *parent = 0);

    enum FileStatus
    {
        None = Qt::UserRole,
        Normal = Qt::UserRole + 1,
        Modified = Qt::UserRole + 2,
    };

    void setFileSystemModel(FileModel *model);

    FileModel *fileSystemModel();

    void paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

private:

    FileModel *mFModel;
};

#endif // EXPLORERITEMDELEGATE_H
