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

#include "customsettingpage.h"

CustomSettingPage::CustomSettingPage(Settings *pSettings, QWidget *parent) :
    SettingsPage(pSettings, parent)
{
    QVBoxLayout *lLayout = new QVBoxLayout;
    setLayout(lLayout);

    QCheckBox *lCheckBox = new QCheckBox("auto");
    lLayout->addWidget(lCheckBox);

    QComboBox *lComboBox = new QComboBox();
    QStringList str;
    str << "text1" << "text2" << "text3";
    lComboBox->addItems(str);
    lLayout->addWidget(lComboBox);

    settings()->add("auto", lCheckBox, "checked");
    settings()->subscribe("auto", this, SLOT(slotSmthChanged(QVariant)));
    settings()->add("combo", lComboBox, "currentText");
    settings()->subscribe("combo", this, SLOT(slotComboChanged(QVariant)));

    setName("GitFake");
    setIcon(QIcon(":/splash/img/sourceline.ico"));
    settings()->setSettingsPath("fake_plugin/group1");
}

void CustomSettingPage::slotSmthChanged(QVariant pValue)
{
    qDebug() << "inside plugin : smth changed = " << pValue.toBool();
}

void CustomSettingPage::slotComboChanged(QVariant pValue)
{
    qDebug() << "inside plugin : combo changed = " << pValue.toString();
}
