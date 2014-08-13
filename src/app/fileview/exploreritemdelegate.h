#ifndef EXPLORERITEMDELEGATE_H
#define EXPLORERITEMDELEGATE_H

#include <QStyledItemDelegate>

class QFileSystemModel;

class ExplorerItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ExplorerItemDelegate(QObject *parent = 0);

    void setFileSystemModel(QFileSystemModel *model);
    QFileSystemModel *fileSystemModel();

    void paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

private:
    QFileSystemModel *mFModel;

};

#endif // EXPLORERITEMDELEGATE_H
