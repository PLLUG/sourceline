#ifndef APICLIENT_H
#define APICLIENT_H

#include <QObject>
#include <QVariant>

class ApiClient : public QObject
{
    Q_OBJECT
public:
    explicit ApiClient(QObject *parent = 0);

    void invoke(QByteArray signature, QVariant param1 = QVariant(), QVariant param2 = QVariant(),
        QVariant param3 = QVariant(), QVariant param4 = QVariant(), QVariant param5 = QVariant());

signals:
    void invoked(QByteArray signature, QVariant param1, QVariant param2,
        QVariant param3, QVariant param4, QVariant param5);
};

#endif // APICLIENT_H
