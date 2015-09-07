#ifndef GITPLUGIN_H
#define GITPLUGIN_H

#include "plugin.h"
#include "gitplugin_global.h"
#include "commandapi.h"
//#include "clonecommand.h"

class GITPLUGINSHARED_EXPORT GitPlugin :
        public Plugin
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
    Q_PLUGIN_METADATA(IID "org.PLLUG.sl.plugins.git" FILE "GitPlugin.json")
public:
    explicit GitPlugin(QObject *pParent = 0);

    void init(CommandAPI * cAPI);
};

#endif // GITPLUGIN_H
