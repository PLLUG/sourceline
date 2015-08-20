#include "apiclient.h"

ApiClient::ApiClient(QObject *parent) : QObject(parent)
{

}

void ApiClient::invoke(QByteArray signature, QVariant param1)
{
    emit invoked(signature, param1);
}

