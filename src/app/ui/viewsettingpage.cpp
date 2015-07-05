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

#include "viewsettingpage.h"
#include "ui_mainwindow.h"
#include "settings.h"

#include <QFileDialog>


ViewSettingPage::ViewSettingPage(Settings *pSettings, QWidget *parent) :
    SettingsPage(pSettings, parent)
{
    mDialogUi = new Ui::Form;
    QWidget *lWidget = new QWidget();
    mDialogUi->setupUi(lWidget);
    QVBoxLayout *lLayout = new QVBoxLayout;
    setLayout(lLayout);
    lLayout->addWidget(lWidget);
    connect(mDialogUi->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(slotBtnOpen()));
    settings()->add("file_view_visible", mDialogUi->checkBox, "checked");
    settings()->subscribe("file_view_visible", this, SLOT(slotFileViewChanged(QVariant)));
    settings()->add("editor_view_visible", mDialogUi->checkBox_2, "checked");
    settings()->subscribe("editor_view_visible", this, SLOT(slotEditorViewChanged(QVariant)));
    settings()->add("revision_table_visible", mDialogUi->checkBox_3, "checked");
    settings()->subscribe("revision_table_visible", this, SLOT(slotRevTreeChanged(QVariant)));
    settings()->add("console_visible", mDialogUi->checkBox_4, "checked");
    settings()->subscribe("console_visible", this, SLOT(slotConsoleChanged(QVariant)));
    settings()->add("history_tree_visible", mDialogUi->checkBox_5, "checked");
    settings()->subscribe("history_tree_visible", this, SLOT(slotTreeChanged(QVariant)));
    settings()->add("path_to_console", mDialogUi->lineEdit, "text");
    settings()->subscribe("path_to_console", this, SLOT(slotConsolePath(QVariant)));

    setName("View");
    setIcon(QIcon(":/splash/img/sourceline.ico"));
    settings()->setSettingsPath("view_settings/docks_visibility");
}

ViewSettingPage::~ViewSettingPage()
{
    delete mDialogUi;
}

void ViewSettingPage::setMainUi(Ui::MainWindow *lMainUi)
{
    mMainUi = lMainUi;
}

void ViewSettingPage::slotBtnOpen()
{
    consolePath = QFileDialog::getOpenFileName();
    mDialogUi->lineEdit->setText(consolePath);
//    ConsoleView *lConsoleView = qobject_cast<ConsoleView *>(mMainUi->uiConsole->widget());
//    if(lConsoleView)
//    {

//    }
}

void ViewSettingPage::slotFileViewChanged(QVariant pValue)
{
    mMainUi->uiFileView->setVisible(pValue.toBool());
}

void ViewSettingPage::slotEditorViewChanged(QVariant pValue)
{
    mMainUi->uiEditorView->setVisible(pValue.toBool());
}

void ViewSettingPage::slotRevTreeChanged(QVariant pValue)
{
    mMainUi->uiRevisionTable->setVisible(pValue.toBool());
}

void ViewSettingPage::slotConsoleChanged(QVariant pValue)
{
    mMainUi->uiConsole->setVisible(pValue.toBool());
}

void ViewSettingPage::slotTreeChanged(QVariant pValue)
{
    mMainUi->uiHistoryTree->setVisible(pValue.toBool());
}

void ViewSettingPage::slotConsolePath(QVariant pValue)
{
    ConsoleView *lConsoleView = qobject_cast<ConsoleView *>(mMainUi->uiConsole->widget());
    if(lConsoleView)
    {
        lConsoleView->slotSetConsolePath(pValue.toString());
    }
}
