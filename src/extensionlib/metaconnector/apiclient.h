#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QVariant>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = 0);

    void invoke(QByteArray signature, QVariant param1);

signals:
    void invoked(QByteArray signature, QVariant param1);
};

#endif // APICLIENT_H
