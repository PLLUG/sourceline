#include "remoteapiclient.h"

#include <QLocalSocket>

#include <QDebug>

static const int CONNECTION_TIMEOUT(5000); // 5 sec

RemoteApiClient::RemoteApiClient(QObject *parent)
    : RemoteApiPoint(parent),
      mSocket(new QLocalSocket(this))
{

}

void RemoteApiClient::connectToProvider(const QString &slInstanceId)
{
    mSocket->connectToServer(slInstanceId, QIODevice::WriteOnly|QIODevice::Unbuffered);
    connect(mSocket, &QLocalSocket::connected, this, &RemoteApiClient::connected, Qt::UniqueConnection);
    mSocket->waitForConnected(CONNECTION_TIMEOUT);
    setConnectedSocket(mSocket);

    if (mSocket->state() == QLocalSocket::ConnectedState)
    {
        qDebug("Connected!");
    }
    else
    {
        qDebug() << mSocket->errorString();
    }
}

