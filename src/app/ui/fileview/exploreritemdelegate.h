#ifndef EXPLORERITEMDELEGATE_H
#define EXPLORERITEMDELEGATE_H

#include <QStyledItemDelegate>

//TASK: move to ui folder (together with fileview folder)

class QFileSystemModel;

class ExplorerItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ExplorerItemDelegate(QObject *parent = 0);

    void setFileSystemModel(QFileSystemModel *model);
    QFileSystemModel *fileSystemModel();

    /*!
     * \brief paint models
     * \param painter
     * \param option style
     * \param index item on model
     */
    void paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const;

    /*!
     * \brief define hint size
     * \param option style
     * \param index item on model
     * \return hint size
     */
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*!
     * \brief explorer item delegate for createEditor
     * \param widget which is parent
     * \param option style
     * \param index item on model
     * \return editor
     */
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    /*!
     * \brief set data in editor
     * \param editor
     * \param model item
     * \param index item on model
     */
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    /*!
     * \brief update geometry for editor
     * \param editor
     * \param option style
     * \param index item on model
     */
    void updateEditorGeometry(QWidget *editor,const QStyleOptionViewItem &option, const QModelIndex &index) const;

signals:

public slots:

private:

    /*!
     * \brief model for file system
     */
    QFileSystemModel *mFModel;
};

#endif // EXPLORERITEMDELEGATE_H
