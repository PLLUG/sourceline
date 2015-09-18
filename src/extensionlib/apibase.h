#ifndef APIBASE
#define APIBASE
#include <QObject>
#include <QVariant>

class ApiBase : public QObject
{
    Q_OBJECT
public:
    explicit ApiBase(QObject *parent = nullptr);
    virtual ~ApiBase() = 0;

signals:
    void invokeCommand(QByteArray pSignature, QVariant=QVariant{},QVariant=QVariant{},QVariant=QVariant{});
};

#endif // APIBASE

