#ifndef APIPROVIDER_H
#define APIPROVIDER_H

#include "invocationbased.h"

class ApiProvider : public InvocationBased
{
    Q_OBJECT
public:
    ApiProvider(QObject *parent = nullptr);

    void setApiRevision(int revision);

protected:
    bool isMetaMethodCouldBeCalled(const QMetaMethod &method) override;

private:
    int mRevision;
};

#endif // APIPROVIDER_H
