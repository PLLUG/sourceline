#include "gitplugin.h"
#include <QDebug>

#include "clonecommand.h"
#include "logcommand.h"

GitPlugin::GitPlugin(QObject *pParent) :
    Plugin(pParent)
{
}

void GitPlugin::init(CommandAPI *cAPI)
{
    CloneCommand *cloneCommand = new CloneCommand(this);
    registerCommand(cloneCommand);

    LogCommand *logCommand = new LogCommand(this);
    registerCommand(logCommand);
    // create clone command
    // call CommandAPI->registerCommand(Command *), pass clone command as a parameter
}
