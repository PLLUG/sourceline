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

#ifndef FILEVIEW_H
#define FILEVIEW_H

#include <QWidget>
#include <QFileSystemModel>
#include <QMenu>
#include <QLabel>
#include "iconizedlineedit.h"
#include "exploreritemdelegate.h"

#include <QDebug>


class Ui_FileView;


class FileView : public QWidget
{
    Q_OBJECT

public:
    explicit FileView(QWidget *parent = 0);

    void setRootPath(const QString pPath);
    QString currentRootPath() const;

    ~FileView();

private:
    Ui_FileView *ui;
    QString mRootPath;
    QFileSystemModel *mFileModel;

    QMenu *mFileMenu;
    QMenu *mDirMenu;
    QMenu *mMenu;

private slots:
    void slotDoubleClick(const QModelIndex &index);
    void slotGoUp();
    void slotRightBtnClick(const QPoint &pos);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *);

};

#endif // FILEVIEW_H
