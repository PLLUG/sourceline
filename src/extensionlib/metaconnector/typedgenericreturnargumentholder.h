#ifndef TYPEDGENERICRETURNARGUMENTHOLDER_H
#define TYPEDGENERICRETURNARGUMENTHOLDER_H

#include "genericreturnargumentholder.h"

template <typename T>
class TypedGenericReturnArgumentHolder : public GenericReturnArgumentHolder
{
public:
    TypedGenericReturnArgumentHolder():
        mVal()
    {}
    TypedGenericReturnArgumentHolder(const TypedGenericReturnArgumentHolder<T> &pOther):
        mVal(pOther.mVal)
    {}
    TypedGenericReturnArgumentHolder(const TypedGenericReturnArgumentHolder<T> &&pOther):
        mVal(std::move(pOther.mVal))
    {}
    TypedGenericReturnArgumentHolder& operator=(const TypedGenericReturnArgumentHolder<T> &pOther)
    {
        mVal = pOther.mVal;
        return *this;
    }
    TypedGenericReturnArgumentHolder& operator=(const TypedGenericReturnArgumentHolder<T> &&pOther)
    {
        mVal = std::move(pOther.mVal);
        return *this;
    }

public:
    void setValue(const T &pVal)
    {
        mVal = pVal;
    }
    void setValue(T &&pVal)
    {
        mVal = std::move(pVal);
    }

    QGenericReturnArgument arg() override
    {
        const char *typeName = QMetaType::typeName(qMetaTypeId<T>());
        return QReturnArgument<T>(typeName, mVal);
    }

    QVariant value() override
    {
        return mVal;
    }

private:
    T mVal;
};

#endif // TYPEDGENERICRETURNARGUMENTHOLDER_H

