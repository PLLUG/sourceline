#include <QDebug>

#include "commandmanager.h"
#include "publiccommandapi.h"
#include "pluginapi.h"

CommandManager::CommandManager(QObject *parent) : QObject(parent)
{

}

PublicCommandAPI *CommandManager::command(QString pCommandID)
{
    return mCommandsAPI.value(pCommandID);
}

void CommandManager::slotCommandRegistered(QString pCommandID)
{
    PublicCommandAPI *lCommandAPI = new PublicCommandAPI(pCommandID);
    mCommandsAPI.insert(pCommandID, lCommandAPI);
    qDebug() << "Command registered: " << pCommandID;
    connect(lCommandAPI, &PublicCommandAPI::invokeCommand, this, &CommandManager::slotInvoke, Qt::UniqueConnection);
}

void CommandManager::slotInvokeCommand(QString pCommandID)
{
    qDebug() << "About to invoke command";
    PublicCommandAPI *lCommandAPI = mCommandsAPI.value(pCommandID);
    if(lCommandAPI)
    {
        qDebug() << "PluginAPI::slotInvokeCommand";
        lCommandAPI->trigger();
    }
}

void CommandManager::slotInvoke(QString pCommandID, QByteArray pSignature)
{
    qDebug() << "CommandManager::slotInvoke" << pCommandID << pSignature;
    emit invokeCommand(pCommandID, pSignature);
}
