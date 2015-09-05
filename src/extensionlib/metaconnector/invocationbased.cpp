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

#include "invocationbased.h"

QHash<int, ArgConverionFunc> InvocationBased::argConvertors;
QHash<int, ReturnArgConverionFunc> InvocationBased::returnArgConvertors;

IB_DECLARE_ARGUMENT_CONVERTORS(QString)
IB_DECLARE_ARGUMENT_CONVERTORS(int)
IB_DECLARE_ARGUMENT_CONVERTORS(double)

void initInvocationBasedClasses()
{
    ibRegisterTypeConvertors(QString);
    ibRegisterTypeConvertors(int);
    ibRegisterTypeConvertors(double);
}

/*!
 * \brief Public constructor.
 * \param parent Pointer to parent object.
 */
InvocationBased::InvocationBased(QObject *parent)
    : QObject(parent),
      mTarget{nullptr}
{

}

/*!
 * \brief Returns target object, on which method invocation will be performed.
 * \return Pointer to target object.
 */
QObject *InvocationBased::target() const
{
    return mTarget;
}

/*!
 * \brief Sets target object, on which method invocation will be performed.
 * \param target Pointer to target object.
 */
void InvocationBased::setTarget(QObject *target)
{
    mTarget = target;
}

/*!
 * \brief Invokes method that returns value.
 * \param signature Method signature.
 * \param arg1 Optional argument 1.
 * \param arg2 Optional argument 2.
 * \param arg3 Optional argument 3.
 * \param arg4 Optional argument 4.
 * \param arg5 Optional argument 5.
 */
QVariant InvocationBased::invokeAndReturn(QByteArray signature, QVariant arg1)
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
                method.invoke(mTarget, Qt::DirectConnection, returnArgHolder->arg(), argHolder1->arg());
            }

            rResult = returnArgHolder->value();
        }
        else
        {
            qDebug("InvocationBased::invokeAndReturn: Could not invoke method with the given return type.");
        }
    }

    return rResult;
}

/*!
 * \brief Special static method for regidtering argument conversion function.
 * You dont need to call it. Use IB_DECLARE_ARGUMENT_CONVERTORS(Type) and
 * ibRegisterTypeConvertors(Type) macroses instead.
 * \param type Meta type id of converted type.
 * \param func Argument conversion function.
 */
void InvocationBased::registerArgConvertor(int type, ArgConverionFunc func)
{
    argConvertors.insert(type, func);
}

/*!
 * \brief Special static method for regidtering return argument conversion function.
 * You dont need to call it. Use IB_DECLARE_ARGUMENT_CONVERTORS(Type) and
 * ibRegisterTypeConvertors(Type) macroses instead.
 * \param type Meta type id of converted type.
 * \param func Return argument conversion function.
 */
void InvocationBased::registerReturnArgConvertor(int type, ReturnArgConverionFunc func)
{
    returnArgConvertors.insert(type, func);
}

/*!
 * \brief Invokes method with the ginen signature and arguments.
 * \param signature Method signature.
 * \param arg1 Optional argument 1.
 * \param arg2 Optional argument 2.
 * \param arg3 Optional argument 3.
 * \param arg4 Optional argument 4.
 * \param arg5 Optional argument 5.
 */
void InvocationBased::invoke(QByteArray signature, QVariant arg1, QVariant arg2, QVariant arg3,
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

        bool wasInvoked = false;
        switch (method.parameterCount())
        {
        case 0:
            wasInvoked = method.invoke(mTarget, Qt::DirectConnection);
            break;
        case 1:
            if(argHolder1)
            {
                wasInvoked = method.invoke(mTarget, Qt::DirectConnection, argHolder1->arg());
            }
            break;
        case 2:
            if(argHolder1 && argHolder2)
            {
                wasInvoked = method.invoke(mTarget, Qt::DirectConnection, argHolder1->arg(),
                    argHolder2->arg());
            }
            break;
        case 3:
            if(argHolder1 && argHolder2 && argHolder3)
            {
                wasInvoked = method.invoke(mTarget, Qt::DirectConnection, argHolder1->arg(),
                    argHolder2->arg(), argHolder3->arg());
            }
            break;
        case 4:
            if(argHolder1 && argHolder2 && argHolder3 && argHolder4)
            {
                wasInvoked = method.invoke(mTarget, Qt::DirectConnection, argHolder1->arg(),
                    argHolder2->arg(), argHolder3->arg(), argHolder4->arg());
            }
            break;
        case 5:
            if(argHolder1 && argHolder2 && argHolder3 && argHolder4 && argHolder5)
            {
                wasInvoked = method.invoke(mTarget, Qt::DirectConnection, argHolder1->arg(),
                    argHolder2->arg(), argHolder3->arg(), argHolder4->arg(), argHolder5->arg());
            }
            break;
        default:
            qDebug("InvocationBased::invoke: Could not invoke method %s with more than 5 arguments.",
                qPrintable(signature.constData()));
            break;
        }

        if (!wasInvoked)
        {
            qDebug("InvocationBased::invoke: Could not invoke method %s with given arguments.",
                qPrintable(signature.constData()));
        }
    }
}

/*!
 * \brief Allows to perform parameter type / count and other metainformation checks before
 * invocation of meta method. Could be reimplemented by derived class. Default implementation
 * always returns True.
 * \param method Method that is about to be invoked.
 * \return True if method should be invoked; false otherwise.
 */
bool InvocationBased::isMetaMethodCouldBeCalled(const QMetaMethod &method)
{
    return true; // Default implementation.
}

/*!
 * \brief Returns meta method on its signature. If thethod could not be called
 * by some reason - returns invalid QMetaMethod instance.
 * \param signature Method signature (as in Qt signal/slot conneciton).
 * \return Valid QMetaMethod instance if method with the given signature could be called.
 */
QMetaMethod InvocationBased::apiMethod(const char *signature)
{
    QMetaMethod rMetaMethod;

    if (mTarget)
    {
        const QMetaObject *metaObj = mTarget->metaObject();
        int index = metaObj->indexOfMethod(signature);

        if (index != -1)
        {
            QMetaMethod method = metaObj->method(index);
            if (isMetaMethodCouldBeCalled(method))
            {
                rMetaMethod = method;
            }
        }
    }

    return rMetaMethod;
}

/*!
 * \brief Instantiates GenericArgumentHolder instance for given argument. Argument type
 * is determined by QVariant::type value.
 * \param value Argument value.
 * \return Pointer to created GenericArgumentHolder instance.
 */
GenericArgumentHolder* InvocationBased::convertArg(const QVariant &value) const
{
    GenericArgumentHolder *rResult{nullptr};

    ArgConverionFunc f = argConvertors.value(value.type());
    if (f)
    {
        rResult = f(value);
    }

    return rResult;
}

/*!
 * \brief Instantiates GenericReturnArgumentHolder instance for given return argument. Argument type
 * is determined by meta type id.
 * \param type Argument meta type id.
 * \return Pointer to created GenericReturnArgumentHolder instance.
 */
GenericReturnArgumentHolder *InvocationBased::convertReturnArg(int type) const
{
    GenericReturnArgumentHolder *rResult{nullptr};

    ReturnArgConverionFunc f = returnArgConvertors.value(type);
    if (f)
    {
        rResult = f();
    }

    return rResult;
}
