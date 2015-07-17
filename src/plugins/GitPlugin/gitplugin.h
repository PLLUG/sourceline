#ifndef GITPLUGIN_H
#define GITPLUGIN_H

#include "plugin.h"
#include "gitplugin_global.h"

class GITPLUGINSHARED_EXPORT GitPlugin :
        public Plugin
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID "GitPlugin" FILE "GitPlugin.json")
public:
    explicit GitPlugin(QObject *pParent = 0);
};

#endif // GITPLUGIN_H
