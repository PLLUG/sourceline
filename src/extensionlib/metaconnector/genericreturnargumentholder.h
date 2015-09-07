#ifndef GENERICRETURNARGUMENTHOLDER_H
#define GENERICRETURNARGUMENTHOLDER_H

#include <QGenericReturnArgument>
#include <QVariant>

class GenericReturnArgumentHolder
{
public:
    virtual ~GenericReturnArgumentHolder() = default;
    virtual QGenericReturnArgument arg() = 0;
    virtual QVariant value() = 0;
};

#endif // GENERICRETURNARGUMENTHOLDER_H

