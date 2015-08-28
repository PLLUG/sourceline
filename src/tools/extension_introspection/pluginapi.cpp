#include "pluginapi.h"
#include "invocationbased.h"
#include "testcommand.h"

PluginAPI::PluginAPI(QObject *parent) : QObject(parent)
{

}

void PluginAPI::slotRegisterCommand(Command *pCommand)
{
    InvocationBased *lInvocationBasedCommand = new InvocationBased();
    lInvocationBasedCommand->setTarget(pCommand);

    QString lCommandID = pCommand->name();

    mRegisteredCommands.insert(lCommandID, lInvocationBasedCommand);

    emit newCommandRegistered(lCommandID);
}

#include <QDebug>
void PluginAPI::slotInvokeCommand(QString pCommandID, QByteArray pSignature)
{
    InvocationBased *lInvocationBasedCommand = nullptr;
    if(lInvocationBasedCommand = mRegisteredCommands.value(pCommandID))
    {
        qDebug() << "PluginAPI::slotInvokeCommand";
        lInvocationBasedCommand->invoke(pSignature);
    }
}

