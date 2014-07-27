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
}

QList<PluginInfo> PluginManager::pluginsInfo()
{
    return mPluginLoader->pluginsInfo();
}

QStringList PluginManager::activePlugins()
{
    return mActivePlugins;
}

void PluginManager::slotSetActivePlugins(const QStringList &pActivePlugins)
{
    mActivePlugins = pActivePlugins;
}
