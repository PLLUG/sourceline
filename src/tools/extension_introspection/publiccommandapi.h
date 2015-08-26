#ifndef PUBLICCOMMANDAPI_H
#define PUBLICCOMMANDAPI_H

#include <QObject>

class PublicCommandAPI : public QObject
{
    Q_OBJECT
public:
    explicit PublicCommandAPI(QString pCommandID, QObject *parent = 0);

    void trigger();

signals:
    void invokeCommand(QString pCommandID, QByteArray pSignature);

public slots:

private:
    QString mCommandID;
};

#endif // PUBLICCOMMANDAPI_H
