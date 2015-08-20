#include "gitplugin.h"
#include <QDebug>


GitPlugin::GitPlugin(QObject *pParent) :
    Plugin(pParent)
{
}


void GitPlugin::init(CommandAPI *cAPI)
{
    // create clone command
    // call CommandAPI->registerCommand(Command *), pass clone command as a parameter
}
