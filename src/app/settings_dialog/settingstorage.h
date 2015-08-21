#ifndef SETTINGSTORAGE_H
#define SETTINGSTORAGE_H

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

#include <QObject>
#include <QMap>
#include <QVariant>

class QSettings;

class SettingStorage : public QObject
{
    Q_OBJECT
public:
    explicit SettingStorage(QObject *parent = 0);

signals:
    void signalSetSettings(QMap<QString, QVariant> pHashData);

public slots:
    void slotSaveSettings(QString pSettingPath, QMap<QString, QVariant> pHashData);
    void slotLoadSettings(QString pSettingPath);

private:
    QStringList parsePath(QString pPath);

private:
    QSettings *mSettings;
    QMap<QString, QStringList> *mPluginGroups;

};

#endif // SETTINGSTORAGE_H
