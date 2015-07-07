#include "exploreritemdelegate.h"

#include <QPainter>
#include <QApplication>
#include <QDebug>
#include <QFileSystemModel>
#include <QLineEdit>
#include <QVBoxLayout>

//TASK: move to ui folder (together with fileview folder)

ExplorerItemDelegate::ExplorerItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
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
    qDebug()<<"creatrEditor"<<"\n";
    QLineEdit* line = new QLineEdit(parent);
    //line->setGeometry(option.rect);
    return line;
}

void ExplorerItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QString pathToFile = mFModel->fileInfo(index).absoluteFilePath();
    QLineEdit* lineName = qobject_cast<QLineEdit*>(editor);
    QString newFileName = lineName->text();
    int indexSlesh = pathToFile.lastIndexOf("/");
    QString tempPath = pathToFile.left(indexSlesh+1);
    tempPath+=newFileName;
    QFile file(pathToFile);
    file.rename(tempPath);
    qDebug()<<"setModelData "+ tempPath<<"\n";
}

void ExplorerItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<"updateEditorGeometry"<<"\n";
    QRect natureRext = option.rect;
    QRect r = option.rect;
    r.setSize(editor->sizeHint());
    editor->setGeometry(natureRext.bottomLeft().x(),natureRext.bottomLeft().y()-r.height(),r.width(),r.height());
}
