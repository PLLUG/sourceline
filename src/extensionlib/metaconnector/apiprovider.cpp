#include "apiprovider.h"
#include "typedgenericargumentholder.h"
#include "typedgenericreturnargumentholder.h"

#include <QMetaMethod>

#include <QDebug>

QHash<int, ArgConverionFunc> ApiProvider::argConvertors;
QHash<int, ReturnArgConverionFunc> ApiProvider::returnArgConvertors;

MC_DECLARE_ARGUMENT_CONVERTORS(QString)
MC_DECLARE_ARGUMENT_CONVERTORS(int)

ApiProvider::ApiProvider(QObject *parent) :
    QObject(parent),
    mApiObj(nullptr),
    mRevision(0)
{
    mcRegisterTypeConvertors(QString);
    mcRegisterTypeConvertors(int);
}

void ApiProvider::attachTo(QObject *apiObj)
{
    mApiObj = apiObj;
    connect(mApiObj, &QObject::destroyed, this, &ApiProvider::cleanApiObj, Qt::UniqueConnection);
    //    const QMetaObject *m = apiObj->metaObject();

    //    for (int methodIndex = 0; methodIndex < m->methodCount(); ++methodIndex)
    //    {
    //        QMetaMethod method = m->method(methodIndex);
    //        if (method.tag() == mApiTag)
    //        {
    //            qDebug() << method.methodSignature();
    //        }

    //    }
}

void ApiProvider::setApiRevision(int revision)
{
    mRevision = revision;
}

void ApiProvider::registerArgConvertor(int type, ArgConverionFunc func)
{
    argConvertors.insert(type, func);
}

void ApiProvider::registerReturnArgConvertor(int type, ReturnArgConverionFunc func)
{
    returnArgConvertors.insert(type, func);
}

QVariant ApiProvider::invokeAndReturn(QByteArray signature, QVariant arg1)
{
    QVariant rResult;

    QMetaMethod method = apiMethod(signature.constData());
    if (method.isValid())
    {
        QScopedPointer<GenericReturnArgumentHolder> returnArgHolder(convertReturnArg(method.returnType()));
        if (returnArgHolder)
        {
            QScopedPointer<GenericArgumentHolder> argHolder1(convertArg(arg1));

            if (argHolder1)
            {
//                 qDebug() << method.invoke(mApiObj, Qt::DirectConnection, returnArgHolder->arg(), argHolder1->arg());
                QGenericReturnArgument a = returnArgHolder->arg();
                int cc;
                QGenericReturnArgument b = Q_RETURN_ARG(int, cc);
                method.invoke(mApiObj, Qt::DirectConnection, a, argHolder1->arg());
            }

            rResult = returnArgHolder->value();
        }
        else
        {
            qDebug("ApiProvider::invokeAndReturn: Could not invoke method with the given return type.");
        }
    }

    qDebug() << "RESULT: " << method.returnType();
    qDebug() << "RESULT: " << rResult;
    return rResult;
}

void ApiProvider::invoke(QByteArray signature, QVariant arg1, QVariant arg2, QVariant arg3,
    QVariant arg4, QVariant arg5)
{
    QMetaMethod method = apiMethod(signature.constData());
    if (method.isValid())
    {
        QScopedPointer<GenericArgumentHolder> argHolder1(convertArg(arg1));
        QScopedPointer<GenericArgumentHolder> argHolder2(convertArg(arg2));
        QScopedPointer<GenericArgumentHolder> argHolder3(convertArg(arg3));
        QScopedPointer<GenericArgumentHolder> argHolder4(convertArg(arg4));
        QScopedPointer<GenericArgumentHolder> argHolder5(convertArg(arg5));

        if(argHolder1 && argHolder2 && argHolder3 && argHolder4 && argHolder5)
        {
            method.invoke(mApiObj, Qt::DirectConnection, argHolder1->arg(),
                argHolder2->arg(), argHolder3->arg(), argHolder4->arg(), argHolder5->arg());
        }
        else if(argHolder1 && argHolder2 && argHolder3 && argHolder4)
        {
            method.invoke(mApiObj, Qt::DirectConnection, argHolder1->arg(),
                argHolder2->arg(), argHolder3->arg(), argHolder4->arg());
        }
        else if(argHolder1 && argHolder2 && argHolder3)
        {
            method.invoke(mApiObj, Qt::DirectConnection, argHolder1->arg(),
                argHolder2->arg(), argHolder3->arg());
        }
        else if(argHolder1 && argHolder2)
        {
            method.invoke(mApiObj, Qt::DirectConnection, argHolder1->arg(),
                argHolder2->arg());
        }
        else if(argHolder1)
        {
            method.invoke(mApiObj, Qt::DirectConnection, argHolder1->arg());
        }
        else
        {
            qDebug("ApiProvider::invoke: Could not invoke method %s with given arguments.", qPrintable(signature.constData()));
        }
    }
}

void ApiProvider::cleanApiObj()
{
    mApiObj = nullptr;
}

QMetaMethod ApiProvider::apiMethod(const char *signature)
{
    QMetaMethod rMetaMethod;

    if (mApiObj)
    {
        const QMetaObject *m = mApiObj->metaObject();

        int index = m->indexOfMethod(signature);

        if (index != -1)
        {
            QMetaMethod method = m->method(index);
            if (method.revision() > 0 && method.revision() <= mRevision)
            {
                rMetaMethod = method;
            }
            qDebug() << "--: " << method.revision();
        }
    }

    return rMetaMethod;
}

GenericArgumentHolder* ApiProvider::convertArg(const QVariant &value) const
{
    ArgConverionFunc f = argConvertors.value(value.type());
    GenericArgumentHolder *rResult{nullptr};
    if (f)
    {
        rResult = f(value);
    }
    return rResult;
}

GenericReturnArgumentHolder *ApiProvider::convertReturnArg(int type) const
{
    ReturnArgConverionFunc f = returnArgConvertors.value(type);
    GenericReturnArgumentHolder *rResult{nullptr};
    if (f)
    {
        rResult = f();
    }
    return rResult;
}
