#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QStringList>

class PluginLoader;
class PluginInfo;
class PluginManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList activePlugins READ activePlugins WRITE slotSetActivePlugins NOTIFY activePluginsChanged)
public:
    explicit PluginManager(QObject *parent = 0);

    void setPluginLoader(PluginLoader *pPluginLoader);

    QList<PluginInfo> pluginsInfo();

    QStringList activePlugins();

signals:
    void activePluginsChanged(QStringList);

public slots:
    void slotSetActivePlugins(const QStringList &pActivePlugins);

private:
    PluginLoader *mPluginLoader;
    QStringList mActivePlugins;
};

#endif // PLUGINMANAGER_H
