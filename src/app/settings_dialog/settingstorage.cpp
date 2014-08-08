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

#include "settingstorage.h"

SettingStorage::SettingStorage(QObject *parent) :
    QObject(parent)
{
    mSettings = new QSettings(QSettings::IniFormat, QSettings::UserScope,
                              "SourceLine", "settings");
    mPluginGroups = new QMap<QString, QStringList>();
}

void SettingStorage::slotSaveSettings(QString pSettingPath, QMap<QString, QVariant> pHashData)
{

    QStringList lGroupsList = parsePath(pSettingPath);

    for(int i = 0; i < lGroupsList.count(); i++)
    {
        mSettings->beginGroup(lGroupsList.at(i));
    }
    QList<QString> lList = pHashData.keys();
    for(int i = 0; i < lList.count(); i++)
    {
        QString lKey = lList.at(i);
        qDebug() << lKey << pHashData.value(lKey).toString();
        mSettings->setValue(lKey, pHashData.value(lKey));
    }
    for(int i = 0; i < lGroupsList.count(); i++)
    {
        mSettings->endGroup();
    }
}

void SettingStorage::slotLoadSettings(QString pSettingPath)
{
    QStringList lGroupsList = parsePath(pSettingPath);
    QMap<QString, QVariant> lHashSetting;

    for(int i = 0; i < lGroupsList.count(); i++)
    {
        mSettings->beginGroup(lGroupsList.at(i));
    }
    QStringList lList = mSettings->allKeys();
    for(int i = 0; i < lList.count(); i++)
    {
        QString lKey = lList.at(i);
        lHashSetting.insert(lKey, mSettings->value(lKey));
    }
    for(int i = 0; i < lGroupsList.count(); i++)
    {
        mSettings->endGroup();
    }
    emit signalSetSettings(lHashSetting);
}

QStringList SettingStorage::parsePath(QString pPath)
{
    QStringList lGroupsList;
    QStringList lTmpList = pPath.split(QRegExp("/"));
    for(int i = 0; i < lTmpList.count(); i++)
    {
        QString elem = lTmpList.at(i);
        if(!elem.isEmpty())
        {
            lGroupsList.append(elem);
        }
    }
    return lGroupsList;
}
