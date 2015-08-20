#ifndef GENERICARGUMENT_H
#define GENERICARGUMENT_H
#include "genericargumentholder.h"

template <typename T>
class TypedGenericArgumentHolder : public GenericArgumentHolder
{
public:
    TypedGenericArgumentHolder(const T &pVal):
        mVal(pVal)
    {}
    TypedGenericArgumentHolder(T &&pVal):
        mVal(std::move(pVal))
    {}
    TypedGenericArgumentHolder(const TypedGenericArgumentHolder<T> &pOther):
        mVal(pOther.mVal)
    {}
    TypedGenericArgumentHolder(const TypedGenericArgumentHolder<T> &&pOther):
        mVal(std::move(pOther.mVal))
    {}
    TypedGenericArgumentHolder& operator=(const TypedGenericArgumentHolder<T> &pOther)
    {
        mVal = pOther.mVal;
        return *this;
    }
    TypedGenericArgumentHolder& operator=(const TypedGenericArgumentHolder<T> &&pOther)
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

    QGenericArgument arg() const override
    {
        return Q_ARG(T, mVal);
    }

private:
    T mVal;
};

#endif // GENERICARGUMENT_H
