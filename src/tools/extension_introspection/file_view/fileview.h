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
#include <QStandardPaths>

namespace Ui
{
    class FileView;
}

class FileModel;
class QMenu;
class QFileSystemModel;
class QAction;

class FileView : public QWidget
{
    Q_OBJECT

public:

    enum SelectionFlag
    {
        NoneSelection = 0x00,
        FileSelection = 0x01,
        FolderSelection = 0x02,
        MultiSeleciton = 0x04
    };
    Q_DECLARE_FLAGS(SelectionFlags, SelectionFlag)
    Q_FLAG(SelectionFlags)

    explicit FileView(QWidget *parent = 0);
    ~FileView();

    void setRootPath(const QString &pPath);

    void cd(const QString &path);

    /*!
     * \brief set root path in different platforms
     * \return path
     */
//    static QString getHomePathForCurrentSystem()
//    {
//        QString rHomePath;
//        #ifdef Q_OS_LINUX
//        rHomePath = "/";
//        #endif
//        #ifdef Q_OS_WIN
//        rHomePath = "My Computer";
//        #endif
//        #ifdef Q_OS_MAC
//        rHomePath = "/";
//        #endif
//        rHomePath = QStandardPaths::HomeLocation;
//        return rHomePath;
//    }

    void registerAction(QAction *pAction, SelectionFlags pSelecitonFlags);

private:
     bool eventFilter(QObject *obj, QEvent *event);
private slots:

    void slotDoubleClick(const QModelIndex &index);

    void slotGoUp();

    void slotGoToPath();

    void slotRightBtnClick();

    void slotLeftBtnClick();

    void slotCreateNewFolder();

    void slotDeleteFolder();

    void slotDeleteFile();

    void slotRenameFolderOrFile();

private:

    Ui::FileView *ui;

    QMenu *mMenu;

    QMenu *mFileMenu;

    QMenu *mDirMenu;

    FileModel *mFileModel;

    QHash<SelectionFlags, QMenu *> mMenuBySelectionFlags;
};

#endif // FILEVIEW_H
