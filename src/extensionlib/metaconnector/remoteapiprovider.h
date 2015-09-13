#ifndef REMOTEAPIPROVIDER_H
#define REMOTEAPIPROVIDER_H

#include <QString>

#include "remoteapipoint.h"
#include "extensions_global.h"

class QLocalServer;

class EXTENSIONSSHARED_EXPORT RemoteApiProvider : public RemoteApiPoint
{
    Q_OBJECT
public:
    explicit RemoteApiProvider(QObject *parent = 0);

    void listen(const QString &slInstanceId);

private slots:
    void gotConnection();
    void error();

private:
    QLocalServer *mServer;
};

#endif // REMOTEAPIPROVIDER_H
