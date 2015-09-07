#include "gitplugin.h"
#include <QDebug>

#include "clonecommand.h"

GitPlugin::GitPlugin(QObject *pParent) :
    Plugin(pParent)
{
}


void GitPlugin::init(CommandAPI *cAPI)
{
    CloneCommand *cloneCommand = new CloneCommand(this);
    registerCommand(cloneCommand);
    // create clone command
    // call CommandAPI->registerCommand(Command *), pass clone command as a parameter
}
