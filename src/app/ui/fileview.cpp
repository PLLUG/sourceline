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

#include "fileview/exploreritemdelegate.h"

FileView::FileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileView)
{
    ui->setupUi(this);

    ui->lineEdit->setIconPixmap(QPixmap(":splash/img/up.png"));
    ui->lineEdit->setIconVisibility(IconizedLineEdit::IconAlwaysVisible);

    //context menu
    mMenu = new QMenu(this);
    QAction* actionNewFolder = new QAction("New Folder",mMenu);
    connect(actionNewFolder, SIGNAL(triggered(bool)), this, SLOT(slotNewFolder()));
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

    mFileModel = new QFileSystemModel(this);
    mRootPath = "My Computer";
    mFileModel->setRootPath(mRootPath);

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
    ui->listView->setRootIndex(mFileModel->index(mRootPath));
    ui->listView->setAcceptDrops(true);
    ui->listView->setDragEnabled(true);
    ui->listView->setDragDropMode(QAbstractItemView::DragDrop);
    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mFileModel->setReadOnly(false);

    ui->lineEdit->setText(mRootPath);

    connect(ui->listView, SIGNAL(doubleClicked(QModelIndex)), SLOT(slotDoubleClick(QModelIndex)));
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(slotRightBtnClick(QPoint)));
    connect(ui->lineEdit, SIGNAL(signalIconClicked()), SLOT(slotGoUp()));
}

void FileView::setRootPath(const QString pPath)
{
    mRootPath = pPath;
}

QString FileView::currentRootPath() const
{
    return mRootPath;
}

FileView::~FileView()
{
    delete ui;
}

void FileView::slotDoubleClick(const QModelIndex &index)
{
    bool q = mFileModel->isDir(index);
    if(q)
    {
        ui->listView->setRootIndex(index);
        mRootPath = mFileModel->fileInfo(index).absoluteFilePath();
        ui->lineEdit->setText(mRootPath);
    }
}

void FileView::slotGoUp()
{
    QModelIndex up_index = (QModelIndex)ui->listView->rootIndex().parent();
    ui->listView->setRootIndex(up_index);
    if(up_index.isValid())
    {
        mRootPath = mFileModel->fileInfo(up_index).absoluteFilePath();
        ui->lineEdit->setText(mRootPath);
    }
    else
    {
        ui->lineEdit->setText("My Computer");
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

void FileView::slotNewFolder()
{
    //create folder
    QModelIndex index = (QModelIndex)ui->listView->rootIndex();
    QString pathSrart = mFileModel->fileInfo(index).absoluteFilePath()+"/"+"New Folder";
    QString pathForNewFolder = pathSrart;

    int i = 1;
    while(QDir(pathForNewFolder).exists())
    {
        pathForNewFolder = pathSrart + " (" + QString::number(i)+")";
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
bool removeDir(const QString& dirName)
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

//    qDebug()<<QMessageBox::question(this,"About delete","really?",QMessageBox::Ok | QMessageBox::Cancel);
    if (QMessageBox::question(this,"About delete","really?",QMessageBox::Ok | QMessageBox::Cancel) == 1024)
    {

        //delete filder
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
    QFile::remove(path);

}

void FileView::slotRenameFolderOrFile()
{
    QModelIndex index = ui->listView->currentIndex();
    if (index.isValid() && (index.flags() & Qt::ItemIsEditable ))
    {
        ui->listView->edit(index);
    }
}

void FileView::resizeEvent(QResizeEvent *)
{
    ui->lineEdit->updateIconPositionAndSize();
}

