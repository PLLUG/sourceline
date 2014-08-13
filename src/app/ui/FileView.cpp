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

FileView::FileView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui_FileView)
{
    ui->setupUi(this);

    ui->lineEdit->setIconPixmap(QPixmap(":splash/img/up.png"));
    ui->lineEdit->setIconVisibility(IconizedLineEdit::IconAlwaysVisible);

    mMenu = new QMenu(this);
    mMenu->addAction("Empty1");
    mMenu->addAction("Empty2");
    mMenu->addAction("Empty3");
    mFileMenu = new QMenu(this);
    mFileMenu->addAction("File1");
    mFileMenu->addAction("File2");
    mFileMenu->addAction("File3");
    mDirMenu = new QMenu(this);
    mDirMenu->addAction("Dir1");
    mDirMenu->addAction("Dir2");
    mDirMenu->addAction("Dir3");

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

void FileView::resizeEvent(QResizeEvent *)
{
    ui->lineEdit->updateIconPositionAndSize();
}
