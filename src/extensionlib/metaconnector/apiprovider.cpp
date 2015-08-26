#include "apiprovider.h"

ApiProvider::ApiProvider(QObject *parent) :
    InvocationBased(parent),
    mRevision(0)
{ }

void ApiProvider::setApiRevision(int revision)
{
    mRevision = revision;
}

bool ApiProvider::isMetaMethodCouldBeCalled(const QMetaMethod &method)
{
    return method.revision() > 0 && method.revision() <= mRevision;
}



