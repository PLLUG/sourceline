#include <QDebug>

#include "commandmanager.h"
#include "publiccommandapi.h"
#include "pluginapi.h"

CommandManager::CommandManager(QObject *parent) : QObject(parent)
{

}

void CommandManager::slotCommandRegistered(QString pCommandID)
{
    mCommandsAPI = new PublicCommandAPI(pCommandID);
    qDebug() << "Command registered: " << pCommandID;
    connect(mCommandsAPI, SIGNAL(invokeCommand(QString,QByteArray)), this, SLOT(slotInvoke(QString,QByteArray)));
}

void CommandManager::slotInvokeCommand()
{
    qDebug() << "About to invoke command";
    mCommandsAPI->trigger();
}

void CommandManager::slotInvoke(QString pCommandID, QByteArray pSignature)
{
    emit invokeCommand(pCommandID, pSignature);
}

