#ifndef APIPROVIDER_H
#define APIPROVIDER_H

#include <QObject>
#include <QList>
#include <QVariant>
#include <QGenericArgument>
#include "genericargumentholder.h"

typedef GenericArgumentHolder* (*ArgConverionFunc)(const QVariant &);
//typedef QGenericReturnArgument (*ReturnArgConverionFunc)(const QVariant &);

#define MC_DECLARE_ARGUMENT_CONVEROTRS(Type) __MC_DECLARE_ARGUMENT_CONVEROTRS(Type)
#define __MC_DECLARE_ARGUMENT_CONVEROTRS(Type) \
    GenericArgumentHolder* Type##__arg(const QVariant &value) \
    { \
        return new TypedGenericArgumentHolder<Type>(value.value<Type>()); \
    } //\
//    QGenericReturnArgument Type##__returnArg(const QVariant &value) \
//    { \
//        return Q_RETURN_ARG(Type, value.value<Type>()); \
//    } \

//GenericArgumentHolder* QString__arg(QVariant value)
//{
//    GenericArgumentHolder *h = new TypedGenericArgumentHolder<QString>(value.value<QString>());
//    return h;
//}


#define mcRegisterTypeConvertors(Type) __mcRegisterTypeConvertors(Type)
#define __mcRegisterTypeConvertors(Type) \
    ApiProvider::registerArgConvertor(qMetaTypeId<Type>(), &Type##__arg); //\
//    ApiProvider::registerReturnArgConvertor(qMetaTypeId<Type>(), &Type##__returnArg);

class ApiProvider : public QObject
{
    Q_OBJECT
public:
    ApiProvider(QObject *parent = nullptr);

    void setApiTag(const QString &tag);

    void attachTo(QObject *apiObj);

    static void registerArgConvertor(int type, ArgConverionFunc func);
//    static void registerReturnArgConvertor(int type, ReturnArgConverionFunc func);

signals:

public slots:
    void invoke(QByteArray signature,
        QVariant arg1 = QVariant());

private:
    QMetaMethod apiMethod(const char *signature);
    GenericArgumentHolder *convertArg(const QVariant &value) const;
//    QGenericReturnArgument convertReturnArg(const QVariant &value) const;

private slots:
    void cleanApiObj();

private:
    QString mApiTag;

    QObject *mApiObj;
    static QHash<int, ArgConverionFunc> argConvertors;
//    static QHash<int, ReturnArgConverionFunc> returnArgConvertors;
};

#endif // APIPROVIDER_H
