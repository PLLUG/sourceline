#include "pluginapi.h"
#include "invocationbased.h"
#include "command.h"
//#include "testcommand.h"

PluginAPI::PluginAPI(QObject *parent) : IPLuginAPI(parent)
{

}

void PluginAPI::registerCommand(const QMetaObject &metaObj, Commands::CommandKind kind)
{
    if (mCommandMetaObjectByKind.values().contains(&metaObj))
    {
        mCommandMetaObjectByKind.insertMulti(kind, &metaObj);
    }
}

QList<Command *> PluginAPI::commands(Commands::CommandKind kind)
{
    // If commands of that kind was not instantiated yet -
    // create instances for registered command classes of that kind
    // and finalize registratin in SL
    if (!mCommandByKind.contains(kind))
    {
        for (const QMetaObject *metaObj: mCommandMetaObjectByKind.values(kind))
        {
            if (Command *command = qobject_cast<Command *>(metaObj->newInstance(Q_ARG(QObject*, nullptr))))
            {
                // We need InvocationBased for every command - to be able to
                // communicate with SL app. SL app will use Command API to trigger commands.
                InvocationBased *lInvocationBasedCommand = new InvocationBased();
                lInvocationBasedCommand->setTarget(command);

                QString lCommandID = command->name();
                mRegisteredCommands.insert(lCommandID, lInvocationBasedCommand);
                mCommandByKind.insertMulti(kind, command);
                emit newCommandRegistered(lCommandID);
            }
        }
    }

    return mCommandByKind.values(kind);
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

