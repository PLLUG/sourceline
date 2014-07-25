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

ViewSettingPage::ViewSettingPage(PluginSettings *pSettings, QWidget *parent) :
    SettingsPage(pSettings, parent)
{
    ui = new Ui::Form;
    QWidget *lWidget = new QWidget();
    ui->setupUi(lWidget);
    QVBoxLayout *lLayout = new QVBoxLayout;
    setLayout(lLayout);
    lLayout->addWidget(lWidget);
    settings()->add("file_view_visible", ui->checkBox, "checked");
    settings()->subscribe("file_view_visible", this, "slotFileViewChanged");
    settings()->add("editor_view_visible", ui->checkBox_2, "checked");
    settings()->subscribe("editor_view_visible", this, "slotEditorViewChanged");
    settings()->add("revision_table_visible", ui->checkBox_3, "checked");
    settings()->subscribe("revision_table_visible", this, "slotRevTreeChanged");
    settings()->add("console_visible", ui->checkBox_4, "checked");
    settings()->subscribe("console_visible", this, "slotConsoleChanged");
    settings()->add("history_tree_visible", ui->checkBox_5, "checked");
    settings()->subscribe("history_tree_visible", this, "slotTreeChanged");

    setName("View");
    setIcon(QIcon(":/Icons/Icons/IconsLand.png"));
    settings()->setSettingsPath("view_settings/docks_visibility");
}

ViewSettingPage::~ViewSettingPage()
{
    delete ui;
}

void ViewSettingPage::slotFileViewChanged(QVariant pValue)
{
    qDebug() << "inside ViewSettings : FView changed = " << pValue.toBool();
}

void ViewSettingPage::slotEditorViewChanged(QVariant pValue)
{
    qDebug() << "inside ViewSettings : EView changed = " << pValue.toBool();
}

void ViewSettingPage::slotRevTreeChanged(QVariant pValue)
{
    qDebug() << "inside ViewSettings : RevTree changed = " << pValue.toBool();
}

void ViewSettingPage::slotConsoleChanged(QVariant pValue)
{
    qDebug() << "inside ViewSettings : Console changed = " << pValue.toBool();
}

void ViewSettingPage::slotTreeChanged(QVariant pValue)
{
    qDebug() << "inside ViewSettings : Tree changed = " << pValue.toBool();
}
