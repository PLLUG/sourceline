#include "pluginapi.h"
#include "invocationbased.h"

PluginAPI::PluginAPI(QObject *parent) : QObject(parent)
{

}

void PluginAPI::slotRegisterCommand(TestCommand *pCommand)
{
    InvocationBased *lInvocationBasedCommand = new InvocationBased();
    lInvocationBasedCommand->setTarget(pCommand);

    QString lCommandID = pCommand->name();

    mRegisteredCommands.insert(lCommandID, lInvocationBasedCommand);

    emit newCommandRegistered(lCommandID);
}

void PluginAPI::slotInvokeCommand(QString pCommandID, QByteArray pSignature)
{
    InvocationBased *lInvocationBasedCommand = nullptr;
    if(lInvocationBasedCommand = mRegisteredCommands.value(pCommandID))
    {
        lInvocationBasedCommand->invoke(pSignature);
    }
}

