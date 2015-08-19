/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Mykola Molochiy (molochiy@gmail.com)                          ***
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

#ifndef CONTENTFORTABWORKPLACE_H
#define CONTENTFORTABWORKPLACE_H

#include <QMainWindow>
#include <QSettings>
#include <QFile>

class HistoryTree;
class RevisionView;
class EditorView;
class FileView;
class DockFileView;
class RevisionTable;
class DockConsole;
class ConsoleView;

namespace Ui {
class ContentForTabWorkplace;
}

class ContentForTabWorkplace : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QByteArray tabState READ tabState WRITE setTabState NOTIFY tabStateChanged)

public:
    explicit ContentForTabWorkplace(QWidget *parent = 0, QString TabName = "");
    ~ContentForTabWorkplace();
    /*!
     * \brief Set Visible For All Component
     * \param pVisible
     */
    void setVisibleForContent(bool pVisible);

    bool isContentVisible();

    QByteArray tabState() const;

public slots:
    void setTabState(QVariant pTabState);
    void sentSignalTabStateChanged();

signals:
    void tabStateChanged(QByteArray pTabState);

private:
    Ui::ContentForTabWorkplace *ui;

    HistoryTree *uiHistoryTree;
    RevisionView *uiHistoryTreeContents;
    EditorView *uiEditorView;
    DockFileView *uiFileView;
    FileView *uiFileViewContents;
    RevisionTable *uiRevisionTable;
    DockConsole *uiConsole;
    ConsoleView *uiConsoleContents;
    bool mIsVisble;
    QString mPathToSettingsFile;
    QSettings *mSettings;    

private:
    void closeEvent(QCloseEvent *pEvent);
};

#endif // CONTENTFORTABWORKPLACE_H
