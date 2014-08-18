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
#include "plugininfo.h"

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
        mPluginsInfo.insert(lPluginInfo.pluginId(), lPluginInfo);
    }
}

QList<PluginInfo> PluginManager::pluginsInfo()
{
    return mPluginsInfo.values();
}

PluginInfo PluginManager::pluginInfo(QString pPluginId)
{
    if (mPluginsInfo.contains(pPluginId))
    {
        return mPluginsInfo[pPluginId];
    }
    else
    {
        return mPluginLoader->pluginInfo(pPluginId);
    }
}

Plugin *PluginManager::plugin(QString pPluginId)
{
    Plugin* lPlugin = qobject_cast<Plugin*>(mPluginLoader->plugin(pPluginId));
    if (lPlugin)
    {
        return lPlugin;
    }
    else
    {

    }
}

QStringList PluginManager::activePlugins()
{
    return mActivePlugins;
}

void PluginManager::slotSetActivePlugins(const QStringList &pActivePlugins)
{
    mActivePlugins = pActivePlugins;
    emit activePluginsChanged(mActivePlugins);
}
