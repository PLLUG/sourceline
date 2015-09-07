#ifndef GENERICARGUMENTHOLDER_H
#define GENERICARGUMENTHOLDER_H
#include <QGenericArgument>

class GenericArgumentHolder
{
public:
    virtual ~GenericArgumentHolder() = default;
    virtual QGenericArgument arg() const = 0;
};

#endif // GENERICARGUMENTHOLDER_H
