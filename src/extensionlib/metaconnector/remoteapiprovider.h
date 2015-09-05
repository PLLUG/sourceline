#ifndef REMOTEAPIPROVIDER_H
#define REMOTEAPIPROVIDER_H

#include <QObject>
#include <QByteArray>
#include <QVariant>

#include "extensions_global.h"

class QLocalServer;
class QLocalSocket;
class InvocationBased;

class EXTENSIONSSHARED_EXPORT RemoteApiProvider : public QObject
{
    Q_OBJECT
public:
    explicit RemoteApiProvider(QObject *parent = 0);

    void listen(const QString &slInstanceId);

    void addApiProvider(InvocationBased * apiProvider);

//signals:
//    void invoked(QByteArray, QByteArray, QVariant, QVariant, QVariant, QVariant, QVariant);

private slots:
    void gotConnection();
    void readyRead();
    void error();

private:
    void invokeApiMethod(QByteArray slInterfaceId, QByteArray signature, QVariant param1,
        QVariant param2, QVariant param3, QVariant param4, QVariant param5);

private:
    QLocalServer *mServer;
    QLocalSocket *mSocket;
    QHash<QByteArray, InvocationBased *> mApiProviderByInterfaceId;
};

#endif // REMOTEAPIPROVIDER_H
