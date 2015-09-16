#ifndef PLUGINAPI_H
#define PLUGINAPI_H

#include "iplugininterfaceadapter.h"
#include "defs.h"

#include <QObject>
#include <QHash>
#include <QString>

class TestCommand;
class InvocationBased;
class Command;

/*!
 * \brief The PluginAPI class implements plugin initialization and plugin information API.
 */
class PluginAPI : public QObject, public IPluginInterfaceAdapter
{
    Q_OBJECT
public:
    explicit PluginAPI(QObject *parent = 0);

    void registerCommandId(QString commandId) final;

private:
};

#endif // PLUGINAPI_H
