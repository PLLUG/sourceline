#include "commandmanager.h"
#include <QDebug>

CommandManager::CommandManager(QObject *parent) : QObject(parent)
{

}

void CommandManager::slotCommandRegistered(QString pCommandID)
{
    mCommandsAPI = new PublicCommandAPI(pCommandID);
    qDebug() << pCommandID;
    connect(mCommandsAPI, SIGNAL(invokeCommand(QString,QByteArray)), this, SLOT(slotInvoke(QString,QByteArray)));
}

void CommandManager::slotInvokeCommand()
{
    mCommandsAPI->trigger();
}

void CommandManager::slotInvoke(QString pCommandID, QByteArray pSignature)
{
    emit invokeCommand(pCommandID, pSignature);
}

