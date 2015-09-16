#include "remoteapipoint.h"

#include <QLocalSocket>
#include <QDataStream>

#include "invocationbased.h"

/*!
 * \brief Public constructor.
 * \param parent Pointer to parent object.
 */
RemoteApiPoint::RemoteApiPoint(QObject *parent)
    : QObject(parent)
    , mSocket{nullptr}
{

}

/*!
 * \brief Sets socket that will be used for communication to other API points.
 * Socket should be connected, open and available for read/write.
 * \param socket Pointer to QLocalSocket.
 */
void RemoteApiPoint::setConnectedSocket(QLocalSocket *socket)
{
    // Disconnect previous socket signal/slot connections
    if (mSocket)
    {
        mSocket->disconnect(this);
    }

    mSocket = socket;

    // Connect new socket to all necessary signals/slots
    if (mSocket)
    {
        connect(mSocket, &QLocalSocket::readyRead, this, &RemoteApiPoint::readyRead, Qt::UniqueConnection);
    }
}

void RemoteApiPoint::addApiProvider(InvocationBased *apiProvider)
{
    Q_CHECK_PTR(apiProvider);
    if (!apiProvider)
    {
        return;
    }

    if (QObject *target = apiProvider->target())
    {
        const QMetaObject *metaObj = target->metaObject();
        QByteArray slInterfaceId = metaObj->superClass()->className();

        qDebug() << "ADDED API PROVIDER:" << slInterfaceId;
        mApiProviderByInterfaceId.insert(slInterfaceId, apiProvider);
    }
}

/*!
 * \brief Returns socket used for communication to other API points.
 * \return Pointer to QLocalSocket.
 */
QLocalSocket *RemoteApiPoint::connectedSocket() const
{
    return mSocket;
}

void RemoteApiPoint::readyRead()
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

void RemoteApiPoint::invokeApiMethod(QByteArray slInterfaceId, QByteArray signature, QVariant param1,
                                     QVariant param2, QVariant param3, QVariant param4, QVariant param5)
{
    if (InvocationBased *invocationBased = mApiProviderByInterfaceId.value(slInterfaceId))
    {
        invocationBased->invoke(signature, param1, param2, param3, param4, param5);
    }
}

void RemoteApiPoint::slotInvoke(QByteArray slInterfaceId, QByteArray signature, QVariant param1, QVariant param2,
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
