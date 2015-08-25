#ifndef APIPROVIDER_H
#define APIPROVIDER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <QGenericArgument>

#include "genericargumentholder.h"
#include "genericreturnargumentholder.h"

typedef GenericArgumentHolder* (*ArgConverionFunc)(const QVariant &);
typedef GenericReturnArgumentHolder* (*ReturnArgConverionFunc)();

#define MC_DECLARE_ARGUMENT_CONVERTORS(Type) __MC_DECLARE_ARGUMENT_CONVERTORS(Type)
#define __MC_DECLARE_ARGUMENT_CONVERTORS(Type) \
    GenericArgumentHolder* Type##__arg(const QVariant &value) \
    { \
        return new TypedGenericArgumentHolder<Type>(value.value<Type>()); \
    } \
    GenericReturnArgumentHolder* Type##__returnArg() \
    { \
        return new TypedGenericReturnArgumentHolder<Type>(); \
    }

#define mcRegisterTypeConvertors(Type) __mcRegisterTypeConvertors(Type)
#define __mcRegisterTypeConvertors(Type) \
    ApiProvider::registerArgConvertor(qMetaTypeId<Type>(), &Type##__arg); \
    ApiProvider::registerReturnArgConvertor(qMetaTypeId<Type>(), &Type##__returnArg);

class ApiProvider : public QObject
{
    Q_OBJECT
public:
    ApiProvider(QObject *parent = nullptr);

    void attachTo(QObject *apiObj);
    void setApiRevision(int revision);

    static void registerArgConvertor(int type, ArgConverionFunc func);
    static void registerReturnArgConvertor(int type, ReturnArgConverionFunc func);

    QVariant invokeAndReturn(QByteArray signature, QVariant arg1 = QVariant());

public slots:
    void invoke(QByteArray signature,
        QVariant arg1 = QVariant(),
        QVariant arg2 = QVariant(),
        QVariant arg3 = QVariant(),
        QVariant arg4 = QVariant(),
        QVariant arg5 = QVariant());


private:
    QMetaMethod apiMethod(const char *signature);
    GenericArgumentHolder *convertArg(const QVariant &value) const;
    GenericReturnArgumentHolder *convertReturnArg(int type) const;

private slots:
    void cleanApiObj();

private:
    QObject *mApiObj;
    int mRevision;
    static QHash<int, ArgConverionFunc> argConvertors;
    static QHash<int, ReturnArgConverionFunc> returnArgConvertors;
};

#endif // APIPROVIDER_H
