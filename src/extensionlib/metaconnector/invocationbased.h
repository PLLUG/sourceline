/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Alex Chmykhalo (alex18cas@gmail.com)                          ***
***                                                                          ***
***    This file is part of SourceLine Project.                              ***
***                                                                          ***
***    SourceLine is free software: you can redistribute it and/or modify    ***
***    it under the terms of the GNU General Public License as published by  ***
***    the Free Software Foundation, either version 3 of the License, or     ***
***    (at your option) any later version.                                   ***
***                                                                          ***
***    SourceLine is distributed in the hope that it will be useful,         ***
***    but WITHOUT ANY WARRANTY; without even the implied warranty of        ***
***    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         ***
***    GNU General Public License for more details.                          ***
***                                                                          ***
***    You should have received a copy of the GNU General Public License     ***
***    along with this program.  If not, see <http://www.gnu.org/licenses/>. ***
***                                                                          ***
*******************************************************************************/

#ifndef INVOCATIONBASED_H
#define INVOCATIONBASED_H

#include <QObject>

#include <QPointer>
#include <QVariant>
#include <QMetaMethod>

#include "typedgenericargumentholder.h"
#include "typedgenericreturnargumentholder.h"

#include "extensions_global.h"

class GenericArgumentHolder;
class GenericReturnArgumentHolder;

typedef GenericArgumentHolder* (*ArgConverionFunc)(const QVariant &);
typedef GenericReturnArgumentHolder* (*ReturnArgConverionFunc)();

/*!
  IB_DECLARE_ARGUMENT_CONVERTORS (Type) is used to create special conversion functions
  for arguments of given type. To use any type with InvocationBased class call (as
  a type of parameter or method return value) it should be registered as Qt metatype
  and IB_DECLARE_ARGUMENT_CONVERTORS should be placed once (in separate compilation unit)
  somewhere outside function/method body and before call will be performed. After that
  convertion functions should be registered with ibRegisterTypeConvertors(Type) macros.
  */
#define IB_DECLARE_ARGUMENT_CONVERTORS(Type) __IB_DECLARE_ARGUMENT_CONVERTORS(Type)
#define __IB_DECLARE_ARGUMENT_CONVERTORS(Type) \
    GenericArgumentHolder* Type##__arg(const QVariant &value) \
    { \
        return new TypedGenericArgumentHolder<Type>(value.value<Type>()); \
    } \
    GenericReturnArgumentHolder* Type##__returnArg() \
    { \
        return new TypedGenericReturnArgumentHolder<Type>(); \
    }

/*!
  ibRegisterTypeConvertors(Type) registers special conversion functions within all
  InvocationBased classes. To do that ibRegisterTypeConvertors should be called
  from function/method only once before any invocation that uses given Type
  as a type of parameter or method return value.

  Type should be registered as Qt metatype and IB_DECLARE_ARGUMENT_CONVERTORS(Type)
  macro should be placed in the same compilation unit before using this macro.
  */
#define ibRegisterTypeConvertors(Type) __ibRegisterTypeConvertors(Type)
#define __ibRegisterTypeConvertors(Type) \
    InvocationBased::registerArgConvertor(qMetaTypeId<Type>(), &Type##__arg); \
    InvocationBased::registerReturnArgConvertor(qMetaTypeId<Type>(), &Type##__returnArg);

/*!
 * \brief Should be called to register basic types for arguments.
 */
extern EXTENSIONSSHARED_EXPORT void initInvocationBasedClasses();

/*!
 * \brief The InvocationBased class is the base class for all classes that should perform
 * invocation of methods of other QObject based on Qt metaobject system capabilities.
 *
 * Invocation is performed dynamically, this means that parameter types and count could not be
 * known at compile time, but are determined during programm runtime.
 *
 * All calls are direct (Qt::DirectConnection) and syncronious, that means that call performed
 * immediately in the point where invoke() or invokeAndReturn() methods are called. This also
 * means that target object which methods will be called should reside in the same thread.
 */
class EXTENSIONSSHARED_EXPORT InvocationBased : public QObject
{
    Q_OBJECT
public:
    InvocationBased(QObject *parent = nullptr);

    QObject *target() const;
    void setTarget(QObject *target);

    QVariant invokeAndReturn(QByteArray signature, QVariant arg1 = QVariant());

    static void registerArgConvertor(int type, ArgConverionFunc func);
    static void registerReturnArgConvertor(int type, ReturnArgConverionFunc func);

public slots:
    void invoke(QByteArray signature,
        QVariant arg1 = QVariant(),
        QVariant arg2 = QVariant(),
        QVariant arg3 = QVariant(),
        QVariant arg4 = QVariant(),
        QVariant arg5 = QVariant());

protected:
    virtual bool isMetaMethodCouldBeCalled(const QMetaMethod &method);

private:
    QMetaMethod apiMethod(const char *signature);

    GenericArgumentHolder *convertArg(const QVariant &value) const;
    GenericReturnArgumentHolder *convertReturnArg(int type) const;

private:
    QPointer<QObject> mTarget;

    static QHash<int, ArgConverionFunc> argConvertors;
    static QHash<int, ReturnArgConverionFunc> returnArgConvertors;
};

#endif // INVOCATIONBASED_H
