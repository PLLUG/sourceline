#include "apiclient.h"

ApiClient::ApiClient(QObject *parent) : QObject(parent)
{

}

void ApiClient::invoke(QByteArray signature, QVariant param1, QVariant param2,
                       QVariant param3, QVariant param4, QVariant param5)
{
    emit invoked(signature, param1, param2, param3, param4, param5);
}

