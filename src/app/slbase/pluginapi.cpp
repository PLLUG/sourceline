#include "pluginapi.h"
#include "invocationbased.h"
#include "command.h"
//#include "testcommand.h"

PluginAPI::PluginAPI(QObject *parent) : IPLuginAPI(parent)
{

}

void PluginAPI::registerCommand(Command *command)
{
    InvocationBased *lInvocationBasedCommand = new InvocationBased();
    lInvocationBasedCommand->setTarget(command);

    QString lCommandID = command->name();

    mRegisteredCommands.insert(lCommandID, lInvocationBasedCommand);

    emit newCommandRegistered(lCommandID);
}

#include <QDebug>
void PluginAPI::slotInvokeCommand(QString pCommandID, QByteArray pSignature)
{
    InvocationBased *lInvocationBasedCommand = nullptr;
    if((lInvocationBasedCommand = mRegisteredCommands.value(pCommandID)))
    {
        qDebug() << "PluginAPI::slotInvokeCommand";
        lInvocationBasedCommand->invoke(pSignature);
    }
}

