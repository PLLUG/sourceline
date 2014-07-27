#ifndef PLUGINLOADER_H
#define PLUGINLOADER_H

#include <QObject>
#include <QHash>
#include <QDir>
#include <QList>
#include <QStringList>
#include "plugininfo.h"


class PluginLoader : public QObject
{
    Q_OBJECT
public:
    explicit PluginLoader(QObject *parent = 0);
    void setPluginsFolder(QDir);
    QStringList pluginIds();
    QObject* plugin(QString);
    QList<QObject*> allPlugins();
    QList<PluginInfo> pluginsInfo();
    static QStringList pluginsExtension();
signals:

public slots:
private:
    QDir mPluginsFolder;

};

#endif // PLUGINLOADER_H
