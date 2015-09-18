#include "publictestinterface.h"

#include "apiclient.h"
#include "apiprovider.h"

#include <QVariant>

PublicTestInterface::PublicTestInterface(ApiProvider &apiProvider, QObject *parent) :
    QObject(parent),
    mApiClient(new ApiClient(this))
{
    connect(mApiClient, &ApiClient::invoked, &apiProvider, &ApiProvider::invoke);
}

void PublicTestInterface::setText(const QString &text)
{
    mApiClient->invoke("setText(QString)", text);
}

