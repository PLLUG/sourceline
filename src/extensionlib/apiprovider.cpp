#include "apiprovider.h"
#include "typedgenericargumentholder.h"

#include <QMetaMethod>

#include <QDebug>

QHash<int, ArgConverionFunc> ApiProvider::argConvertors;
//QHash<int, ReturnArgConverionFunc> ApiProvider::returnArgConvertors;

MC_DECLARE_ARGUMENT_CONVEROTRS(QString)

ApiProvider::ApiProvider(QObject *parent) :
    QObject(parent)
{
        mcRegisterTypeConvertors(QString);
    //    ArgConverionFunc func = &QString__arg;
    //    ApiProvider::registerArgConvertor(qMetaTypeId<QString>(), func);
}

void ApiProvider::setApiTag(const QString &tag)
{
    mApiTag = tag;
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

void ApiProvider::registerArgConvertor(int type, ArgConverionFunc func)
{
    argConvertors.insert(type, func);
}

//void ApiProvider::registerReturnArgConvertor(int type, ReturnArgConverionFunc func)
//{
//    returnArgConvertors.insert(type, func);
//}

void ApiProvider::invoke(QByteArray signature, QVariant arg1)
{
    QMetaMethod method = apiMethod(signature.constData());
    if (method.isValid())
    {
        QScopedPointer<GenericArgumentHolder> argHolder1(convertArg(arg1));
        if(argHolder1)
            method.invoke(mApiObj, argHolder1->arg());
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
            if (method.tag() == mApiTag)
            {
                rMetaMethod = method;
            }
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

//QGenericReturnArgument ApiProvider::convertReturnArg(const QVariant &value) const
//{
//    ReturnArgConverionFunc f = returnArgConvertors.value(value.type());
//    QGenericReturnArgument rResult;
//    if (f)
//    {
//        rResult = f(value);
//    }
//    return rResult;
//}

