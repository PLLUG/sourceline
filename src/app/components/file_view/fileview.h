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

namespace Ui {
    class FileView;
}

class QMenu;
class QFileSystemModel;

/*!
 * \brief The class for representation file view
 */
class FileView : public QWidget
{
    Q_OBJECT

public:

    explicit FileView(QWidget *parent = 0);
    ~FileView();

    /*!
     * \brief set root path for system
     * \param path which must be root
     */
    void setRootPath(const QString &pPath);

    void setTextToLineEdit(const QString &path);
    /*!
     * \brief set root path in different platforms
     * \return path
     */
    static QString getHomePathForCurrentSystem()
    {
        QString rHomePath;
        #ifdef Q_OS_LINUX
        rHomePath = "/";
        #endif
        #ifdef Q_OS_WIN
        rHomePath = "My Computer";
        #endif
        #ifdef Q_OS_MAC
        rHomePath = "/";
        #endif
        return rHomePath;
    }

    /*!
     * \brief set slash for different system
     */
    void setSlash()
    {
        #ifdef Q_OS_LINUX
        Slash = "/";
        NoSlash = "\\";
        #endif
        #ifdef Q_OS_WIN
        Slash = "\\";
        NoSlash = "/";
        #endif
        #ifdef Q_OS_MAC
        Slash = "/";
        NoSlash = "\\";
        #endif
    }

private:

    /*!
      * \brief filter for events for object
      * \param object name
      * \param event for this object
      * \return
      */
     bool eventFilter(QObject *obj, QEvent *event);
private slots:

    /*!
     * \brief open folder on double click
     * \param index item in model
     */
    void slotDoubleClick(const QModelIndex &index);

    /*!
     * \brief go up to repository
     */
    void slotGoUp();

    /*!
     * \brief go to last repository
     */
    void slotGoToPath();

    /*!
     * \brief action create menu on right button click
     * \param position item on view
     */
    void slotRightBtnClick(const QPoint &pos);

    /*!
     * \brief create new folder
     */
    void slotCreateNewFolder();

    /*!
     * \brief delete folder
     */
    void slotDeleteFolder();

    /*!
     * \brief delete file
     */
    void slotDeleteFile();

    /*!
     * \brief rename rolder or file
     */
    void slotRenameFolderOrFile();

private:

    /*!
     * \brief user interface
     */
    Ui::FileView *ui;

    /*!
     * \brief main context menu
     */
    QMenu *mMenu;

    /*!
     * \brief context menu for file
     */
    QMenu *mFileMenu;

    /*!
     * \brief context menu for folders
     */
    QMenu *mDirMenu;

    /*!
     * \brief file model
     */
    QFileSystemModel *mFileModel;

    /*!
     * \brief Slash for system
     */
    QString Slash;

    /*!
     * \brief is not slash for system
     */
    QString NoSlash;
};

#endif // FILEVIEW_H
