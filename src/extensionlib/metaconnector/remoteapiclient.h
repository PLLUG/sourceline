#ifndef REMOTEAPICLIENT_H
#define REMOTEAPICLIENT_H

#include <QObject>
#include <QByteArray>
#include <QVariant>

#include "extensions_global.h"

class QLocalSocket;

class EXTENSIONSSHARED_EXPORT RemoteApiClient : public QObject
{
    Q_OBJECT
public:
    explicit RemoteApiClient(QObject *parent = 0);

    void connectToProvider(const QString &slInstanceId);

signals:
    void connected();

public slots:
    void slotInvoke(QByteArray slInterfaceId, QByteArray signature,
                     QVariant param1,
                     QVariant param2,
                     QVariant param3,
                     QVariant param4,
                     QVariant param5);

private:
    QLocalSocket *mSocket;
};

#endif // REMOTEAPICLIENT_H
