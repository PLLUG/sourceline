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
#include "pluginloader.h"
#include <QPluginLoader>
#include <QFileInfo>
#include <QCoreApplication>

PluginLoader::PluginLoader(QObject *parent) :
    QObject(parent),
    mPluginsFolder(defaultPluginDirPath())
{
}

void PluginLoader::setPluginsFolder(const QDir &pPluginFolder)
{
    mPluginsFolder = pPluginFolder;
}

QStringList PluginLoader::pluginsExtensionFilters()
{
    QStringList rExtensions;
#ifdef Q_OS_WIN32
    rExtensions.append("*.dll");
#endif
#ifdef Q_OS_MAC
    rExtensions.append("*.lib");
#endif
#ifdef Q_OS_UNIX
    rExtensions.append("*.so");
#endif
    return std::move(rExtensions);
}

QString PluginLoader::defaultPluginDirPath() const
{
#ifdef Q_OS_WIN
    return QString("%1/%2").arg(QCoreApplication::applicationDirPath(), "plugins");
#else
    return QDir::cleanPath(QString("%1/%2").arg(QCoreApplication::applicationDirPath(), "../lib/plugins"));
#endif
}

QString PluginLoader::pluginsExtension()
{
#ifdef Q_OS_WIN32
    return ".dll";
#endif
#ifdef Q_OS_MAC
    return ".lib";
#endif
#ifdef Q_OS_UNIX
    return ".so";
#endif
}

QStringList PluginLoader::pluginIds() const
{
    QDir path(mPluginsFolder);
    QStringList rPluginsIdsList;
    for(const QFileInfo &info: path.entryInfoList(PluginLoader::pluginsExtensionFilters(), QDir::Files | QDir::NoDotAndDotDot))
    {
        rPluginsIdsList.append(info.baseName());
    }
    return std::move(rPluginsIdsList);
}

QObject* PluginLoader::load(const QString &pPluginId)
{
    QObject *rInstance{nullptr};

    QPluginLoader lPluginLoader(libPath(pPluginId));
    if (lPluginLoader.load())
    {
        rInstance = lPluginLoader.instance();
    }
    else
    {
        qDebug(qPrintable(lPluginLoader.errorString()));
    }
    return rInstance;
}

PluginInfo PluginLoader::pluginInfo(const QString &pPluginId) const
{
    QPluginLoader lPluginLoader(libPath(pPluginId));
    QString lVersion = lPluginLoader.metaData().value("MetaData").toObject().value("version").toString();
    QString lDescription = lPluginLoader.metaData().value("MetaData").toObject().value("description").toString();
    QString lCategory = lPluginLoader.metaData().value("MetaData").toObject().value("category").toString();
    QStringList lAdditionalKeys = lPluginLoader.metaData().value("MetaData").toObject().keys();
    QHash<QString, QString> lAdditionalInfo;
    for(const QString &key : lAdditionalKeys)
    {
        if (key != "version" && key != "description" && key != "category")
        {
            lAdditionalInfo[key] = lPluginLoader.metaData().value("MetaData").toObject().value(key).toString();
        }
    }
    return PluginInfo(pPluginId, lVersion, lDescription, lCategory, lAdditionalInfo);
}

QList<PluginInfo> PluginLoader::pluginsInfo() const
{
    QDir path(mPluginsFolder);
    QPluginLoader pluginLoader;
    QList<PluginInfo> rPluginsDescriptions;
    for(const QFileInfo &info: path.entryInfoList(PluginLoader::pluginsExtensionFilters(), QDir::Files | QDir::NoDotAndDotDot))
    {
        pluginLoader.setFileName(info.absoluteFilePath());

        QString lVersion = pluginLoader.metaData().value("MetaData").toObject().value("version").toString();
        QString lDescription = pluginLoader.metaData().value("MetaData").toObject().value("description").toString();
        QString lCategory = pluginLoader.metaData().value("MetaData").toObject().value("category").toString();
        QStringList lAdditionalKeys = pluginLoader.metaData().value("MetaData").toObject().keys();
        QHash<QString, QString> lAdditionalInfo;
        for(const QString &key: lAdditionalKeys)
        {
            if (key != "version" && key != "description" && key != "category")
            {
                lAdditionalInfo[key] = pluginLoader.metaData().value("MetaData").toObject().value(key).toString();
            }
        }
        PluginInfo lPluginInfo(info.baseName(), lVersion, lDescription, lCategory, lAdditionalInfo);
        rPluginsDescriptions.append(lPluginInfo);
    }
    return std::move(rPluginsDescriptions);
}

QString PluginLoader::libPath(const QString &pPluginId) const
{
    QDir lPath(mPluginsFolder);
    return lPath.absoluteFilePath(pPluginId) + pluginsExtension();
}
