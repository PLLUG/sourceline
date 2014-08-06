/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Alex Chmykhalo (alexchmykhalo@users.sourceforge.net)          ***
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

#include "settingsmanager.h"

#include "settings.h"
#include "settingstorage.h"

SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent),
    mStorage(0)
{
}

void SettingsManager::setStorage(SettingStorage *pStorage)
{
    mStorage = pStorage;
}

QString SettingsManager::pathBySettings(Settings *pSettings)
{
    return mPathBySettings.value(pSettings);
}

void SettingsManager::addSettings(const QString &pPluginId, const QString &pSettingsPageName, Settings *pSettings)
{
    if (pPluginId.isEmpty())
    {
        qDebug("SettingsManager::addSettings: plugin id is empty!");
        return;
    }

    if (pSettingsPageName.isEmpty())
    {
        qDebug("SettingsManager::addSettings: settings page name is empty!");
        return;
    }

    if (!pSettings)
    {
        qDebug("SettingsManager::addSettings: settings object is nullptr!");
        return;
    }

    mPluginIdBySettings.insert(pSettings, pPluginId);
    mPageNameBySettings.insert(pSettings, pSettingsPageName);
    QString lFullSettingsPath = QString("%1/%2/%3").arg(pPluginId).arg(pSettingsPageName).arg(pSettings->settingsPath());

    mPathBySettings.insert(pSettings, lFullSettingsPath);

    connect(pSettings, SIGNAL(settingsChanged(QMap<QString,QVariant>)),
        this, SLOT(slotWriteSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);
    connect(mStorage, SIGNAL(signalSetSettings(QMap<QString,QVariant>)),
        pSettings, SLOT(slotSetSettings(QMap<QString,QVariant>)), Qt::UniqueConnection);

    if (mStorage)
    {
        mStorage->slotLoadSettings(pathBySettings(pSettings));
    }
}

void SettingsManager::slotWriteSettings(QMap<QString, QVariant> pMap)
{
    if (mStorage)
    {
        QString lPluginId = mPluginIdBySettings.value(sender());
        if (lPluginId.isEmpty())
        {
            qDebug("SettingsManager::slotWriteSettings: could not find plugin id for settings!");
            return;
        }

        QString lSettingsPageName = mPageNameBySettings.value(sender());
        if (lSettingsPageName.isEmpty())
        {
            qDebug("SettingsManager::slotWriteSettings: could not find settings page name for settings!");
            return;
        }

        QString lPath = mPathBySettings.value(sender());
        qDebug() << lPath;
        mStorage->slotSaveSettings(lPath, pMap);
    }
    else
    {
        qDebug("SettingsManager::slotWriteSettings: storage not set!");
    }
}
