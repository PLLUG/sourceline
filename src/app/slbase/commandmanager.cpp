#include <QDebug>

#include "commandmanager.h"
#include "comamndinterface.h"
#include "pluginapi.h"

CommandManager::CommandManager(QObject *parent) : QObject(parent)
{

}

CommandInterface *CommandManager::command(QString pCommandID)
{
    return mCommandsAPI.value(pCommandID);
}

void CommandManager::slotCommandRegistered(QString pCommandID)
{
    CommandInterface *lCommandAPI = new CommandInterface(/*pCommandID*/);
    mCommandsAPI.insert(pCommandID, lCommandAPI);
    qDebug() << "Command registered: " << pCommandID;
//    connect(lCommandAPI, &CommandInterface::invokeCommand, this, &CommandManager::slotInvoke, Qt::UniqueConnection);
}

void CommandManager::slotInvokeCommand(QString pCommandID)
{
    qDebug() << "About to invoke command";
    CommandInterface *lCommandAPI = mCommandsAPI.value(pCommandID);
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
