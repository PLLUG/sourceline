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

#include "settingspage.h"

SettingsPage::SettingsPage(Settings *pSettings, QWidget *parent) :
    QWidget(parent),
    mSettings(pSettings)
{
}

QString SettingsPage::name() const
{
    return mName;
}

QIcon SettingsPage::icon() const
{
    return mIcon;
}

Settings *SettingsPage::settings() const
{
    return mSettings;
}

void SettingsPage::slotApply()
{
    if (mSettings)
    {
        mSettings->commit();
    }
}

void SettingsPage::slotCancel()
{
    if (mSettings)
    {
        mSettings->revert();
    }
}

void SettingsPage::setName(const QString &pName)
{
    mName = pName;
}

void SettingsPage::setIcon(const QIcon &pIcon)
{
    mIcon = pIcon;
}
