#ifndef REMOTEAPIPOINT_H
#define REMOTEAPIPOINT_H

#include <QObject>
#include <QHash>
#include <QByteArray>
#include <QVariant>

#include "extensions_global.h"

class QLocalSocket;
class InvocationBased;

class EXTENSIONSSHARED_EXPORT RemoteApiPoint : public QObject
{
    Q_OBJECT
public:
    explicit RemoteApiPoint(QObject *parent = 0);

    void addApiProvider(InvocationBased *apiProvider);

signals:

public slots:
    void slotInvoke(QByteArray slInterfaceId, QByteArray signature, QVariant param1,
                    QVariant param2, QVariant param3, QVariant param4, QVariant param5);

protected:
    QLocalSocket *connectedSocket() const;
    void setConnectedSocket(QLocalSocket *socket);

private slots:
    void readyRead();

private:
    void invokeApiMethod(QByteArray slInterfaceId, QByteArray signature, QVariant param1,
                         QVariant param2, QVariant param3, QVariant param4, QVariant param5);

private:
    QLocalSocket *mSocket;
    QHash<QByteArray, InvocationBased *> mApiProviderByInterfaceId;
};

#endif // REMOTEAPIPOINT_H
