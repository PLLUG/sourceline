#ifndef IPLUGININTERFACEADAPTER_H
#define IPLUGININTERFACEADAPTER_H

#include <QString>

/*!
 * \brief The IPluginInterfaceAdapter class declares interface that could be
 * used by remote Plugin API provider.
 */
class IPluginInterfaceAdapter
{
    virtual void registerCommandId(QString commandId) = 0;
};

#endif // IPLUGININTERFACEADAPTER_H

