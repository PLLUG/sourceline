#include "pluginapiinterface.h"
#include "command.h"
#include "invocationbased.h"

void PluginApiInterface::registerCommand(const QMetaObject &metaObj, Commands::CommandKind kind)
{
    if (!mCommandMetaObjectByKind.values().contains(&metaObj))
    {
        mCommandMetaObjectByKind.insertMulti(kind, &metaObj);
    }
}

QList<Command *> PluginApiInterface::commands(Commands::CommandKind kind)
{
    // If commands of that kind was not instantiated yet -
    // create instances for registered command classes of that kind
    // and finalize registratin in SL
    if (!mCommandByKind.contains(kind))
    {
        for (const QMetaObject *metaObj: mCommandMetaObjectByKind.values(kind))
        {
            QObject *instance = metaObj->newInstance();
            if (Command *command = dynamic_cast<Command *>(instance))
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
void PluginApiInterface::slotInvokeCommand(QString pCommandID, QByteArray pSignature)
{
    InvocationBased *lInvocationBasedCommand = nullptr;
    if((lInvocationBasedCommand = mRegisteredCommands.value(pCommandID)))
    {
        qDebug() << "PluginApiInterface::slotInvokeCommand";
        lInvocationBasedCommand->invoke(pSignature);
    }
}
