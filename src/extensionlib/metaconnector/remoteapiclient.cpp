#include "remoteapiclient.h"

#include <QDataStream>
#include <QLocalSocket>

#include <QDebug>

static const int CONNECTION_TIMEOUT(5000); // 5 sec

RemoteApiClient::RemoteApiClient(QObject *parent)
    : QObject(parent),
      mSocket(new QLocalSocket(this))
{
    connect(mSocket, &QLocalSocket::connected, this, &RemoteApiClient::connected, Qt::UniqueConnection);
}

void RemoteApiClient::connectToProvider(const QString &slInstanceId)
{
    mSocket->connectToServer(slInstanceId, QIODevice::WriteOnly|QIODevice::Unbuffered);
    mSocket->waitForConnected(CONNECTION_TIMEOUT);

    if (mSocket->state() == QLocalSocket::ConnectedState)
    {
        qDebug("Connected!");
    }
    else
    {
        qDebug() << mSocket->errorString();
    }
}

void RemoteApiClient::slotInvoke(QByteArray slInterfaceId, QByteArray signature, QVariant param1, QVariant param2,
    QVariant param3, QVariant param4, QVariant param5)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly|QIODevice::Unbuffered);
//    stream.setVersion(QDataStream::Qt_5_5);

    stream << slInterfaceId;
    stream << signature;
    stream << param1;
    stream << param2;
    stream << param3;
    stream << param4;
    stream << param5;

    mSocket->write(data);
    mSocket->flush();

    qDebug() << "Writing : ";
    qDebug() << slInterfaceId << signature << param1 << param2 << param3 << param4 << param5;
}

