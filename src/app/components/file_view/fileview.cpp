/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#include "fileview.h"
#include "ui_fileview.h"

#include <QMenu>
#include <QFileSystemModel>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDialog>
#include <QAction>
#include <QEvent>
#include <QKeyEvent>

#include "ui/exploreritemdelegate.h"


FileView::FileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);
    QAction *actionGoUp = ui->lineEdit->addAction(QPixmap(":splash/img/up.png"), QLineEdit::TrailingPosition);

    //context menu
    mMenu = new QMenu(this);
    QAction* actionNewFolder = new QAction("New Folder",mMenu);
    connect(actionNewFolder, SIGNAL(triggered(bool)), this, SLOT(slotCreateNewFolder()));
    mMenu->addAction(actionNewFolder);

    //menu for files
    mFileMenu = new QMenu(this);
    QAction* actionDeleteFile = new QAction("Delete",mFileMenu);
    connect(actionDeleteFile, SIGNAL(triggered(bool)), this, SLOT(slotDeleteFile()));
    mFileMenu->addAction(actionDeleteFile);
    QAction* actionRemaneFile = new QAction("Rename",mFileMenu);
    connect(actionRemaneFile, SIGNAL(triggered(bool)), this, SLOT(slotRenameFolderOrFile()));
    mFileMenu->addAction(actionRemaneFile);

    //menu for dirs
    mDirMenu = new QMenu(this);
    QAction* actionDeleteFolder = new QAction("Delete",mDirMenu);
    connect(actionDeleteFolder, SIGNAL(triggered(bool)), this, SLOT(slotDeleteFolder()));
    mDirMenu->addAction(actionDeleteFolder);
    QAction* actionRemaneDir = new QAction("Rename",mFileMenu);
    connect(actionRemaneDir, SIGNAL(triggered(bool)), this, SLOT(slotRenameFolderOrFile()));
    mDirMenu->addAction(actionRemaneDir);

    mFileModel = new FileModel(this);
    ui->listView->setModel(mFileModel);
    ExplorerItemDelegate *lDeltegate = new ExplorerItemDelegate();
    lDeltegate->setFileSystemModel(mFileModel);
    ui->listView->setItemDelegate(lDeltegate);
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setMovement(QListView::Static);
    ui->listView->setResizeMode(QListView::Adjust);
    ui->listView->setFlow(QListView::LeftToRight);
    ui->listView->setWordWrap(true);
    ui->listView->setWrapping(true);
    ui->listView->setGridSize(QSize(70,70));
    ui->listView->setAcceptDrops(true);
    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mFileModel->setReadOnly(false);
    setRootPath(QDir::currentPath());
    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), SLOT(slotDoubleClick(QModelIndex)));
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotRightBtnClick(QPoint)));
    connect(actionGoUp, SIGNAL(triggered(bool)), SLOT(slotGoUp()));
    ui->lineEdit->installEventFilter(this);
}

FileView::~FileView()
{
    delete ui;
}

void FileView::setRootPath(const QString &pPath)
{
    setTextToLineEdit(pPath);
    mFileModel->setRootPath(pPath);
    ui->listView->setRootIndex(mFileModel->index(pPath));

}

void FileView::setTextToLineEdit(const QString &path)
{
    QString newPath = QDir::fromNativeSeparators(path);
    ui->lineEdit->setText(QDir::toNativeSeparators(newPath));
}

void FileView::registerAction(QAction *pAction, SelectionFlags pSelecitonFlags)
{
    // More code here...
}

bool FileView::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit)
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent *key = static_cast<QKeyEvent *>(event);
            if (key->key() == Qt::Key_Escape || key->key() == Qt::Key_Return)
            {
                slotGoToPath();
                return true;
            }
        }
        if (event->type() == QEvent::FocusOut)
        {
            slotGoToPath();
            return true;
        }
    }
    return false;
}

void FileView::slotDoubleClick(const QModelIndex &index)
{
    if(mFileModel->isDir(index))
    {
        ui->listView->setRootIndex(index);
        setTextToLineEdit(mFileModel->fileInfo(index).absoluteFilePath());
    }
}

void FileView::slotGoUp()
{
    QModelIndex up_index = (QModelIndex)ui->listView->rootIndex().parent();
    ui->listView->setRootIndex(up_index);
    if(up_index.isValid())
    {
        setTextToLineEdit(mFileModel->fileInfo(up_index).absoluteFilePath());
        ui->listView->setCurrentIndex(mFileModel->index(mFileModel->fileInfo(up_index).absoluteFilePath()));
    }
    else
    {
        setTextToLineEdit(FileView::getHomePathForCurrentSystem());
    }
}

void FileView::slotGoToPath()
{
    const QString path = ui->lineEdit->text();
    setTextToLineEdit(path);
    if (QDir().exists(path))
    {
        mFileModel->setRootPath(ui->lineEdit->text());
        ui->listView->setRootIndex(mFileModel->index(ui->lineEdit->text()));
        ui->listView->setCurrentIndex(mFileModel->index(ui->lineEdit->text()));
    }
    else
    {
        setTextToLineEdit(mFileModel->fileInfo(ui->listView->currentIndex()).absoluteFilePath());
    }
}

void FileView::slotRightBtnClick(const QPoint &pos)
{
    QModelIndex lIndex = ui->listView->indexAt(pos);
    if(mFileModel->fileInfo(lIndex).isDir())
    {
        mDirMenu->exec(QCursor::pos());
    }
    else if(mFileModel->fileInfo(lIndex).isFile())
    {
        mFileMenu->exec(QCursor::pos());
    }
    else
    {
        mMenu->exec(QCursor::pos());
    }
}

void FileView::slotCreateNewFolder()
{
    //create folder
    QModelIndex index = static_cast<QModelIndex>(ui->listView->rootIndex());
    QString pathStart = mFileModel->fileInfo(index).absoluteFilePath()+QDir::toNativeSeparators("/")+"New Folder";
    QString pathForNewFolder = pathStart;

    //counter for standart folder name(New Folder (i)) if "New Folder" is already exist
    int i = 1;
    while(QDir(pathForNewFolder).exists())
    {
        pathForNewFolder = pathStart + " (" + QString::number(i)+")";
        i++;
    }

    QDir().mkdir(pathForNewFolder);

    //select folder
    ui->listView->setCurrentIndex(mFileModel->index(pathForNewFolder));

    //rename folder
    ui->listView->edit(ui->listView->currentIndex());
}

/*!
 * \brief Remove folder and input content
 * \param path to folder which remove
 * \return result removing(true if remove folder)
 */
bool removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);
    if (dir.exists(dirName))
    {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst))
        {
            if (info.isDir())
            {
                result = removeDir(info.absoluteFilePath());
            }
            else
            {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result)
            {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

void FileView::slotDeleteFolder()
{
    QModelIndex currentIndex = ui->listView->currentIndex();
    QString path = mFileModel->fileInfo(currentIndex).absoluteFilePath();

    //create message about delete folder and check what button was clicked
    if (static_cast<QMessageBox::StandardButton>(QMessageBox::question(this,"About delete","Do you wanna delete this repository?",QMessageBox::Ok, QMessageBox::Cancel)) == QMessageBox::Ok)
    {
        //delete folder
        if (!removeDir(path))
        {
            QMessageBox::information(this,"Error","Can't delete this repository");
        }
    }
}

void FileView::slotDeleteFile()
{
    QModelIndex currentIndex = ui->listView->currentIndex();
    QString path = mFileModel->fileInfo(currentIndex).absoluteFilePath();

    //create message about delete file and check what button was clicked
    if (static_cast<QMessageBox::StandardButton>(QMessageBox::question(this,"About delete","Do you wanna delete this file?",QMessageBox::Ok, QMessageBox::Cancel)) == QMessageBox::Ok)
    {
        //delete file
        if (!QFile::remove(path))
        {
            QMessageBox::information(this,"Error","Can't delete this file");
        }
    }
}

void FileView::slotRenameFolderOrFile()
{
    QModelIndex index = ui->listView->currentIndex();
    if (index.isValid() && (index.flags() & Qt::ItemIsEditable ))
    {
        ui->listView->edit(index);
    }
}
