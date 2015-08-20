#include "exploreritemdelegate.h"

#include <QPainter>
#include <QApplication>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include "texteditforrename.h"
#include <QTextCursor>
#include "../filemodel.h"
#include <QFileSystemWatcher>
#include <QHash>
#include <QDateTime>
#include <QDebug>

//TASK: move to ui folder (together with fileview folder)
const QString invalidCharacters = "\\/:*?\"<>|";

ExplorerItemDelegate::ExplorerItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
//    icons.insert(FileStatus::None, QStringLiteral(""));
//    icons.insert(FileStatus::Normal, QStringLiteral(":/Overlays/overlays/normal.png"));
//    icons.insert(FileStatus::Modified, QStringLiteral(":/Overlays/overlays/modified.png"));
}

void ExplorerItemDelegate::setFileSystemModel(FileModel *model)
{
    mFModel = model;
}

FileModel* ExplorerItemDelegate::fileSystemModel()
{
    return mFModel;
}

/*!
 * \brief paint models
 * \param painter
 * \param option style
 * \param index item on model
 */
void ExplorerItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 optv4 = opt;
    initStyleOption(&optv4, index);

    optv4.text = "";
    QStyle *style = optv4.widget ? optv4.widget->style() : QApplication::style();
    optv4.icon = QIcon();
    optv4.decorationSize = (QSize(0,0));
    style->drawControl(QStyle::CE_ItemViewItem, &optv4, painter, optv4.widget);

    QStyledItemDelegate::paint(painter, opt, index);
    painter->save();
    painter->setBrush(QColor(Qt::black));
    painter->setPen(Qt::NoPen);

    QPixmap lPixmap;
    lPixmap = QPixmap(mFModel->data(index, FileModel::FileAttributeIconRole).toString());
    int l = 16;
    QRect rect(optv4.rect.center().x() + 2, optv4.rect.topRight().y() + 18, l, l);
    painter->drawPixmap(rect, lPixmap.scaled(l, l, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter->restore();
}

/*!
 * \brief define hint size
 * \param option style
 * \param index item on model
 * \return hint size
 */
QSize ExplorerItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}

/*!
 * \brief explorer item delegate for createEditor
 * \param widget which is parent
 * \param option style
 * \param index item on model
 * \return editor
 */
QWidget *ExplorerItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)
    TextEditForRename* lineName = new TextEditForRename(parent);
    lineName->installEventFilter(parent);
    return lineName;
}

/*!
 * \brief check valid name for file
 * \param name file
 * \return true in name is valid
 */
bool checkValidName(QString nameItem)
{
    for(int i = 0; i < nameItem.length(); i++)
    {
        if (invalidCharacters.indexOf(nameItem[i]) != -1)
        {
            return false;
        }
    }
    return true;
}

/*!
 * \brief set data in editor
 * \param editor
 * \param model item
 * \param index item on model
 */
void ExplorerItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    Q_UNUSED(model)
    QString pathToFile = mFModel->fileInfo(index).absoluteFilePath();
    TextEditForRename* lineName = new TextEditForRename();
    if (editor != NULL)
    {
        lineName = qobject_cast<TextEditForRename*>(editor);
    }
    QString newFileName = lineName->toPlainText();

    int indexSlash = pathToFile.lastIndexOf("/");
    QString newPathToFile = pathToFile.left(indexSlash+1);
    qDebug()<<newPathToFile;
    newPathToFile += newFileName;

    QFile file(pathToFile);
    if (!checkValidName(newFileName))
    {
        QMessageBox::information(editor,"Error","A file name can't contain any of the following characters: " + invalidCharacters);
        return;
    }
    if (newFileName.isEmpty())
    {
        QMessageBox::information(editor,"Error","A file name is empty");
        return;
    }
    if (pathToFile != newPathToFile)
    {
        if (QFile(newPathToFile).exists())
        {
            QMessageBox::information(editor,"Error","File with name \"" + newFileName + "\" is already exist");
        }
        else
        {
            file.rename(newPathToFile);
        }
    }
}

/*!
 * \brief update geometry for editor
 * \param editor
 * \param option style
 * \param index item on model
 */
void ExplorerItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    TextEditForRename* lineName = new TextEditForRename();
    if (editor != NULL)
    {
        lineName = qobject_cast<TextEditForRename*>(editor);
    }
    QRect optionRect = option.rect;

    //place text editor on background widget
    lineName->move(optionRect.x()-5, optionRect.y()+35);

    //fixed width that this is looking native
    lineName->setFixedWidth(optionRect.width()+10);
}
