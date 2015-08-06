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

#include "contentfortabworkplace.h"
#include "ui_contentfortabworkplace.h"
#include "ui/consoleview.h"
#include "ui/dockconsole.h"
#include "ui/dockfileview.h"
#include "ui/editorview.h"
#include "ui/fileview.h"
#include "ui/historytree.h"
#include "ui/revisiontable.h"
#include "ui/revisionview.h"

ContentForTabWorkplace::ContentForTabWorkplace(QWidget *parent, QString TabName) :
    QMainWindow(parent),    
    ui(new Ui::ContentForTabWorkplace)
{
    ui->setupUi(this);

    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setSizePolicy(sizePolicy);
    setMouseTracking(false);
    setAutoFillBackground(false);
    setDockNestingEnabled(true);
    setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);

    //COMMENT: Create DockWidget HistoryTree, set content for it and add this HistoryTree to ContentForTabWorkplace
    uiHistoryTree = new HistoryTree(this);
    uiHistoryTreeContents = new RevisionView(uiHistoryTree);
    uiHistoryTree->setWidget(uiHistoryTreeContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiHistoryTree);

    //COMMENT: Create DockWidget EditorView and add this EditorView to ContentForTabWorkplace
    uiEditorView = new EditorView(this);
    addDockWidget(static_cast<Qt::DockWidgetArea>(8), uiEditorView);

    //COMMENT: Create DockWidget DockFileView, set content for it and add this DockFileView to ContentForTabWorkplace
    uiFileView = new DockFileView(this);
    uiFileViewContents = new FileView(uiFileView);
    uiFileView->setWidget(uiFileViewContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(1), uiFileView);

    //COMMENT: Create DockWidget RevisionTable and add this RevisionTable to ContentForTabWorkplace
    uiRevisionTable = new RevisionTable(this);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiRevisionTable);

    //COMMENT: Create DockWidget DockConsole, set content for it and add this DockConsole to ContentForTabWorkplace
    uiConsole = new DockConsole(this);
    uiConsole->setLayoutDirection(Qt::LeftToRight);
    uiConsoleContents = new ConsoleView(uiConsole);
    uiConsole->setWidget(uiConsoleContents);
    addDockWidget(static_cast<Qt::DockWidgetArea>(2), uiConsole);

    splitDockWidget(uiRevisionTable, uiEditorView, Qt::Horizontal);
    splitDockWidget(uiEditorView, uiConsole, Qt::Vertical);
    tabifyDockWidget(uiEditorView, uiFileView);
    tabifyDockWidget(uiRevisionTable, uiHistoryTree);

    mPathToSettingsFile = "Tabs Settings/" + TabName + ".ini";

    mSettings = new QSettings(mPathToSettingsFile, QSettings::IniFormat);

    saveSettings();

    mIsVisble = true;
}

ContentForTabWorkplace::~ContentForTabWorkplace()
{
    QFile::remove(mPathToSettingsFile);
    delete uiConsole;
    delete uiEditorView;
    delete uiFileView;
    delete uiHistoryTree;
    delete uiRevisionTable;
    delete ui;
}

void ContentForTabWorkplace::saveSettings()
{
    mSettings->setValue("state",saveState());
    mSettings->setValue("geometry",saveGeometry());
    mSettings->sync();
}

void ContentForTabWorkplace::restoreSettings()
{
    QByteArray lGeometryData = mSettings->value("geometry").toByteArray();
    restoreGeometry(lGeometryData);
    QByteArray lStateData = mSettings->value("state").toByteArray();
    restoreState(lStateData);
}

void ContentForTabWorkplace::setVisibleForContent(bool pVisible)
{
    uiHistoryTree->setVisible(pVisible);
    uiFileView->setVisible(pVisible);
    uiConsole->setVisible(pVisible);
    uiEditorView->setVisible(pVisible);
    uiRevisionTable->setVisible(pVisible);
    mIsVisble = pVisible;
}

bool ContentForTabWorkplace::isContentVisible()
{
    return mIsVisble;
}

QByteArray ContentForTabWorkplace::tabState() const
{
    return saveState();
}

void ContentForTabWorkplace::setTabState(QByteArray pTabState)
{
    if (tabState() == pTabState)
        return;

    restoreState(pTabState);
    emit tabStateChanged(pTabState);
}
