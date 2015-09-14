#include "gitplugin.h"
#include <QDebug>

// Command to register
#include "clonecommand.h"

GitPlugin::GitPlugin(QObject *pParent) :
    Plugin(pParent)
{
}

void GitPlugin::init(const Aggregator &aggregate)
{
    REGISTER_COMMAND(aggregate, CloneCommand, Commands::InitializeRepository)
}
