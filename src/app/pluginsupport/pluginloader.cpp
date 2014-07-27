#include "pluginloader.h"
#include <QPluginLoader>
#include <QFileInfo>
#include <QtGlobal>

PluginLoader::PluginLoader(QObject *parent) :
    QObject(parent),
    mPluginsFolder(QDir::currentPath() + "/debug/plugins")
{
}
void PluginLoader::setPluginsFolder(QDir pPluginFolder)
{
    mPluginsFolder = pPluginFolder;
}


QStringList PluginLoader::pluginsExtension()
{
    #ifdef Q_OS_WIN32
        QStringList lExtensions;
        lExtensions.append("*.dll");
        return lExtensions;
    #endif
    #ifdef Q_OS_MAC
        QStringList lExtensions;
        lExtensions.append("*.lib");
        return lExtensions;
    #endif
    #ifdef Q_OS_UNIX
        QStringList lExtensions;
        lExtensions.append("*.so");
        return lExtensions;
    #endif
}

QStringList PluginLoader::pluginIds()
{
    QDir path(mPluginsFolder);
    QPluginLoader pluginLoader;
    QStringList rPluginsIds;
    foreach(QFileInfo info, path.entryInfoList(PluginLoader::pluginsExtension(), QDir::Files | QDir::NoDotAndDotDot))
    {
        pluginLoader.setFileName(info.absoluteFilePath());
        QString lPluginId = pluginLoader.metaData().value("MetaData").toObject().value("pluginId").toString();
        rPluginsIds.append(lPluginId);
    }
    return rPluginsIds;

}
QObject* PluginLoader::plugin(QString pPluginId)
{
    QDir lPath(mPluginsFolder);
    QPluginLoader lPluginLoader(lPath.absoluteFilePath(pPluginId));
    return lPluginLoader.instance();
}

//QList<QObject*> PluginLoader::allPlugins()
//{

//}

QList<PluginInfo> PluginLoader::pluginsInfo()
{
    QDir path(mPluginsFolder);
    QPluginLoader pluginLoader;
    QList<PluginInfo> rPluginsDescriptions;
    foreach(QFileInfo info, path.entryInfoList(PluginLoader::pluginsExtension(), QDir::Files | QDir::NoDotAndDotDot))
    {
        pluginLoader.setFileName(info.absoluteFilePath());

        QString lVersion = pluginLoader.metaData().value("MetaData").toObject().value("version").toString();
        QString lDescription = pluginLoader.metaData().value("MetaData").toObject().value("description").toString();
        QString lCategory = pluginLoader.metaData().value("MetaData").toObject().value("category").toString();
        QStringList lAdditionalKeys = pluginLoader.metaData().value("MetaData").toObject().keys();
        QHash<QString, QString> lAdditionalInfo;
        foreach (QString key, lAdditionalKeys)
        {
            if (key != "version" && key != "description" && key != "category")
            {
                lAdditionalInfo[key] = pluginLoader.metaData().value("MetaData").toObject().value(key).toString();
            }
        }
        PluginInfo lPluginInfo(info.baseName(), lVersion, lDescription, lCategory, lAdditionalInfo);
        rPluginsDescriptions.append(lPluginInfo);
    }
    return rPluginsDescriptions;
}
