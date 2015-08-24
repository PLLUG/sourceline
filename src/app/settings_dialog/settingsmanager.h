#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

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

#include <QObject>
#include <QMap>
#include <QVariant>

class Settings;
class SettingStorage;

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);

    void setStorage(SettingStorage *pStorage);
    QString pathBySettings(Settings *pSettings);

    void addSettings(const QString &pPluginId, const QString &pSettingsGroupName, Settings *pSettings);

signals:

public slots:
    void slotWriteSettings(QMap<QString, QVariant> pMap);

private:
    QMap<QObject *, QString> mPluginIdBySettings;
    QMap<QObject *, QString> mPageNameBySettings;
    QMap<QObject *, QString> mPathBySettings;

    SettingStorage *mStorage;
};

#endif // SETTINGSMANAGER_H
