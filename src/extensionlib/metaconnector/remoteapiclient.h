#ifndef REMOTEAPICLIENT_H
#define REMOTEAPICLIENT_H


#include "remoteapipoint.h"
#include "extensions_global.h"

class QLocalSocket;

class EXTENSIONSSHARED_EXPORT RemoteApiClient : public RemoteApiPoint
{
    Q_OBJECT
public:
    explicit RemoteApiClient(QObject *parent = 0);

    void connectToProvider(const QString &slInstanceId);

signals:
    void connected();

private:
    QLocalSocket *mSocket;
};

#endif // REMOTEAPICLIENT_H
