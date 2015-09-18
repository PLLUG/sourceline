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
#include "pluginmanager.h"
#include "pluginloader.h"
#include "plugin.h"

PluginManager::PluginManager(QObject *parent) :
    QObject(parent),
    mPluginLoader(NULL)
{
}

void PluginManager::setPluginLoader(PluginLoader *pPluginLoader)
{
    mPluginLoader = pPluginLoader;
    QList<PluginInfo> lPluginInfoList =  mPluginLoader->pluginsInfo();
    foreach (PluginInfo lPluginInfo, lPluginInfoList)
    {
        mPluginsInfoByPluginId.insert(lPluginInfo.pluginId(), lPluginInfo);
    }
}

QStringList PluginManager::availablePlugins()
{
    return mPluginsInfoByPluginId.keys();
}

QList<PluginInfo> PluginManager::pluginsInfo()
{
    return mPluginsInfoByPluginId.values();
}

PluginInfo PluginManager::pluginInfo(QString pPluginId)
{
    if (mPluginsInfoByPluginId.contains(pPluginId))
    {
        return mPluginsInfoByPluginId[pPluginId];
    }
    else
    {
        return mPluginLoader->pluginInfo(pPluginId);
    }
}

bool PluginManager::loadPlugin(const QString &pPluginId)
{
    bool rResult = false;

    QObject *lPluginInstance = mPluginLoader->load(pPluginId);
    if (!lPluginInstance)
    {
        qDebug("PluginManager::loadPlugin: unable to load plugin %s", qPrintable(pPluginId));
        return rResult;
    }

    Plugin* lPlugin = qobject_cast<Plugin*>(lPluginInstance);
    if(lPlugin)
    {
        mLoadedPluginByPluginId.insert(pPluginId, lPlugin);
        rResult = true;
    }

    return rResult;
}

Plugin *PluginManager::loadedPluginInstance(const QString &pPluginId)
{
    return mLoadedPluginByPluginId.value(pPluginId);
}

QStringList PluginManager::activePlugins() const
{
    return mActivePlugins;
}

QStringList PluginManager::loadedPlugins() const
{
    return mLoadedPluginByPluginId.keys();
}

void PluginManager::slotSetActivePlugins(const QStringList &pActivePlugins)
{
    mActivePlugins = pActivePlugins;
    emit activePluginsChanged(mActivePlugins);
}
