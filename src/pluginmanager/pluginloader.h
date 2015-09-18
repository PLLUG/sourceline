#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H
/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Priyma Yuriy (priymayuriy@gmail.com)                          ***
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
#include <QDir>
#include <QStringList>
#include "plugininfo.h"
#include "pluginmanager_global.h"

class PLUGINMANAGERSHARED_EXPORT PluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = nullptr);
    void setPluginsFolder(const QDir &);
    QStringList pluginIds() const;
    QObject* load(const QString &);
    PluginInfo pluginInfo(const QString &pPluginId) const;
    QList<PluginInfo> pluginsInfo() const;
    QString libPath(const QString &pPluginId) const;
    static QString pluginsExtension();
    static QStringList pluginsExtensionFilters();

private:
    QString defaultPluginDirPath() const;

private:
    QDir mPluginsFolder;
};

#endif // PLUGINLOADER_H
