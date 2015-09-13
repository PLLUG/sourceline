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
//    CloneCommand *cloneCommand = new CloneCommand(this);
//    registerCommand(cloneCommand);
    // create clone command
    // call CommandAPI->registerCommand(Command *), pass clone command as a parameter
}
