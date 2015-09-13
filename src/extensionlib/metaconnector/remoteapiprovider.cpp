#include "remoteapiprovider.h"

#include <QLocalServer>
#include <QLocalSocket>

#include "invocationbased.h"

RemoteApiProvider::RemoteApiProvider(QObject *parent)
    : RemoteApiPoint(parent),
      mServer(new QLocalServer(this))
{
    connect(mServer, &QLocalServer::newConnection, this, &RemoteApiProvider::gotConnection, Qt::UniqueConnection);
}

void RemoteApiProvider::listen(const QString &slInstanceId)
{
    mServer->removeServer(slInstanceId);
    if (!mServer->listen(slInstanceId))
    {
        qDebug() << mServer->errorString();
    }
}

void RemoteApiProvider::gotConnection()
{
    if (QLocalSocket *socket = mServer->nextPendingConnection())
    {
        setConnectedSocket(socket);
        qDebug("Got connection!");
    }
}

void RemoteApiProvider::error()
{

}

