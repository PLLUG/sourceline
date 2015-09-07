#ifndef PUBLICTESTINTERFACE_H
#define PUBLICTESTINTERFACE_H

#include <QObject>

class ApiClient;
class ApiProvider;

class PublicTestInterface : public QObject
{
    Q_OBJECT
public:
    explicit PublicTestInterface(ApiProvider &apiProvider, QObject *parent = 0);

public slots:
    void setText(const QString &text);

private:
    ApiClient *mApiClient;
};

#endif // PUBLICTESTINTERFACE_H
