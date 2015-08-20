#include "gitplugin.h"
#include "testcommand.h"
#include <QDebug>


GitPlugin::GitPlugin(QObject *pParent) :
    Plugin(pParent)
{
    TestCommand testcommand("clone", "username", "password");
    qDebug() << testcommand.commandString();
    qDebug() << testcommand.parametersList();
}

void GitPlugin::Clone()
{
    qDebug() << "Clonning...";
}

