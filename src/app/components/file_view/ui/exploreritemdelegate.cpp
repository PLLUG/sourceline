#include "exploreritemdelegate.h"

#include <QPainter>
#include <QApplication>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTextEdit>
#include "texteditforrename.h"
#include <QTextCursor>

//TASK: move to ui folder (together with fileview folder)
const QString invalidCharacters = "\\/:*?\"<>|";

ExplorerItemDelegate::ExplorerItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
    mFModel = nullptr;
}

void ExplorerItemDelegate::setFileSystemModel(QFileSystemModel *model)
{
    mFModel = model;
}

QFileSystemModel* ExplorerItemDelegate::fileSystemModel()
{
    return mFModel;
}

void ExplorerItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &opt, const QModelIndex &index) const
{
    QStyleOptionViewItemV4 optv4 = opt;
    initStyleOption(&optv4, index);

    optv4.text = "";
    QStyle *style = optv4.widget ? optv4.widget->style() : QApplication::style();
    optv4.icon = QIcon();
    optv4.decorationSize = (QSize(0,0));
    style->drawControl(QStyle::CE_ItemViewItem, &optv4, painter, optv4.widget);

    QPixmap lPixmap;
    if(mFModel->fileInfo(index).isDir())
    {
        lPixmap = QPixmap(":/splash/img/added.png");
    }
    else
    {
        lPixmap = QPixmap(":/splash/img/up.png");
    }

    QStyledItemDelegate::paint(painter, opt, index);

    painter->save();
    int l = 16;
    painter->setBrush(QColor(Qt::black));
    painter->setPen(Qt::NoPen);

    QRect rect(optv4.rect.center().x() + 2, optv4.rect.topRight().y() + 18, l, l);
    painter->drawPixmap(rect, lPixmap.scaled(l, l, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    painter->restore();
}

QSize ExplorerItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QStyledItemDelegate::sizeHint(option, index);
}


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
