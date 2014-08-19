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


ViewSettingPage::ViewSettingPage(Settings *pSettings, QWidget *parent) :
    SettingsPage(pSettings, parent)
{
    mDialogUi = new Ui::Form;
    QWidget *lWidget = new QWidget();
    mDialogUi->setupUi(lWidget);
    QVBoxLayout *lLayout = new QVBoxLayout;
    setLayout(lLayout);
    lLayout->addWidget(lWidget);
    settings()->add("file_view_visible", mDialogUi->checkBox, "checked");
    settings()->subscribe("file_view_visible", this, "slotFileViewChanged");
    settings()->add("editor_view_visible", mDialogUi->checkBox_2, "checked");
    settings()->subscribe("editor_view_visible", this, "slotEditorViewChanged");
    settings()->add("revision_table_visible", mDialogUi->checkBox_3, "checked");
    settings()->subscribe("revision_table_visible", this, "slotRevTreeChanged");
    settings()->add("console_visible", mDialogUi->checkBox_4, "checked");
    settings()->subscribe("console_visible", this, "slotConsoleChanged");
    settings()->add("history_tree_visible", mDialogUi->checkBox_5, "checked");
    settings()->subscribe("history_tree_visible", this, "slotTreeChanged");

    connect(mDialogUi->checkBox, SIGNAL(stateChanged(int)), SIGNAL(signalSettingsStateChanged()));
    connect(mDialogUi->checkBox_2, SIGNAL(stateChanged(int)), SIGNAL(signalSettingsStateChanged()));
    connect(mDialogUi->checkBox_3, SIGNAL(stateChanged(int)), SIGNAL(signalSettingsStateChanged()));
    connect(mDialogUi->checkBox_4, SIGNAL(stateChanged(int)), SIGNAL(signalSettingsStateChanged()));
    connect(mDialogUi->checkBox_5, SIGNAL(stateChanged(int)), SIGNAL(signalSettingsStateChanged()));

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

void ViewSettingPage::slotFileViewChanged(QVariant pValue)
{
//    mMainUi->uiFileView->setVisible(pValue.toBool());
    qDebug() << "inside ViewSettings : FView changed = " << pValue.toBool();
}

void ViewSettingPage::slotEditorViewChanged(QVariant pValue)
{
    mMainUi->uiEditorView->setVisible(pValue.toBool());
    qDebug() << "inside ViewSettings : EView changed = " << pValue.toBool();
}

void ViewSettingPage::slotRevTreeChanged(QVariant pValue)
{
    mMainUi->uiRevisionTable->setVisible(pValue.toBool());
    qDebug() << "inside ViewSettings : RevTree changed = " << pValue.toBool();
}

void ViewSettingPage::slotConsoleChanged(QVariant pValue)
{
    mMainUi->uiConsole->setVisible(pValue.toBool());
    qDebug() << "inside ViewSettings : Console changed = " << pValue.toBool();
}

void ViewSettingPage::slotTreeChanged(QVariant pValue)
{
    mMainUi->uiHistoryTree->setVisible(pValue.toBool());
    qDebug() << "inside ViewSettings : Tree changed = " << pValue.toBool();
}
