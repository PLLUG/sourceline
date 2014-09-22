#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H
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
#include <QStringList>
#include <QMap>

#include <plugin.h>
#include "plugininfo.h"
class PluginLoader;

class PluginManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList activePlugins READ activePlugins WRITE slotSetActivePlugins NOTIFY activePluginsChanged)
public:
    explicit PluginManager(QObject *parent = 0);

    void setPluginLoader(PluginLoader *pPluginLoader);

    QStringList availablePlugins();
    QList<PluginInfo> pluginsInfo();
    PluginInfo pluginInfo(QString pPluginId);
    bool loadPlugin(const QString &pPluginId);
    Plugin* loadedPluginInstance(QString pPluginId);
    QStringList activePlugins();
    QStringList loadedPlugins();

signals:
    void activePluginsChanged(QStringList);

public slots:
    void slotSetActivePlugins(const QStringList &pActivePlugins);

private:
    PluginLoader *mPluginLoader;
    QMap<QString, PluginInfo> mPluginsInfoByPluginId;
    QMap<QString, Plugin *> mLoadedPluginByPluginId;
    QStringList mActivePlugins;
};

#endif // PLUGINMANAGER_H
