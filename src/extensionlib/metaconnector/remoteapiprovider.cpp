#include "remoteapiprovider.h"

#include <QLocalServer>
#include <QLocalSocket>

#include <QDataStream>

#include "invocationbased.h"

RemoteApiProvider::RemoteApiProvider(QObject *parent)
    : QObject(parent),
      mServer(new QLocalServer(this))
{
    connect(mServer, &QLocalServer::newConnection, this, &RemoteApiProvider::gotConnection, Qt::UniqueConnection);
}

void RemoteApiProvider::listen(const QString &slInstanceId)
{
;    mServer->removeServer(slInstanceId);
    if (!mServer->listen(slInstanceId))
    {
        qDebug() << mServer->errorString();
    }
}

void RemoteApiProvider::addApiProvider(InvocationBased *apiProvider)
{
    Q_CHECK_PTR(apiProvider);
    if (!apiProvider)
    {
        return;
    }

    if (QObject *target = apiProvider->target())
    {
        const QMetaObject *metaObj = target->metaObject();
        QByteArray slInterfaceId = metaObj->className();

//        mApiProviderByInterfaceId.insert(slInterfaceId, apiProvider);
        mApiProviderByInterfaceId.insert(QByteArray("ClientExplorer"), apiProvider);
    }
}

void RemoteApiProvider::gotConnection()
{
    if ((mSocket = mServer->nextPendingConnection()))
    {
        connect(mSocket, &QLocalSocket::readyRead, this, &RemoteApiProvider::readyRead, Qt::UniqueConnection);
        qDebug("Got connection!");
    }
}

void RemoteApiProvider::readyRead()
{
    if (mSocket)
    {
        QByteArray data = mSocket->readAll();
        if (data.isEmpty())
        {
            qDebug("Empty!!!!!!");
        }
        QDataStream stream(&data, QIODevice::ReadOnly|QIODevice::Unbuffered);
//        stream.setVersion(QDataStream::Qt_5_5);

        QByteArray slInterfaceId;
        stream >> slInterfaceId;
        qDebug() << slInterfaceId;
        QByteArray signature;
        stream >> signature;
        qDebug() << signature;
        QVariant param1;
        stream >> param1;
        QVariant param2;
        stream >> param2;
        QVariant param3;
        stream >> param3;
        QVariant param4;
        stream >> param4;
        QVariant param5;
        stream >> param5;

        qDebug() << "Reading: ";
        qDebug() << slInterfaceId << signature << param1 << param2 << param3 << param4 << param5;

//        emit invoked(slInterfaceId, signature, param1, param2, param3, param4, param5);
        invokeApiMethod(slInterfaceId, signature, param1, param2, param3, param4, param5);
    }
}

void RemoteApiProvider::error()
{

}

void RemoteApiProvider::invokeApiMethod(QByteArray slInterfaceId, QByteArray signature, QVariant param1, QVariant param2, QVariant param3, QVariant param4, QVariant param5)
{
    if (InvocationBased *invocationBased = mApiProviderByInterfaceId.value(slInterfaceId))
    {
        invocationBased->invoke(signature, param1, param2, param3, param4, param5);
    }
}

