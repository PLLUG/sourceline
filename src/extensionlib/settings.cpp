/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Alex Chmykhalo (alex.chmykhalo@users.sourceforge.net)         ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
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

#include "settings.h"

Settings::Settings(QObject *parent) :
    QObject(parent),
    mPropertyMapper(new QSignalMapper(this)),
    mAutoCommit(false),
    mAutoNotify(false)
{
    connect(mPropertyMapper, SIGNAL(mapped(QString)),
            this, SLOT(propertyChanged(QString)), Qt::UniqueConnection);
}

QString Settings::settingsPath() const
{
    return mSettingsPath;
}

bool Settings::add(const QString &pName, QObject *pObject, const QString &pProperty)
{
    bool lSuccess = false;
    if (pName.isEmpty() || !pObject || pProperty.isEmpty())
    {
        qDebug("Settings: could not add setting - invalid parameter value");
    }
    if ((lSuccess = isPropertyCouldBeAttached(pObject, pProperty)))
    {
        mObjectBySetting.insert(pName, pObject);
        mPropertyBySetting.insert(pName, pProperty.toUtf8());
        mPropertyMapper->setMapping(pObject, pName);
        QMetaProperty lMetaProperty = metaProperty(pObject, pProperty);
        QMetaMethod lPropertySignal = lMetaProperty.notifySignal();
        QMetaMethod lMapMethod = metaMethod(mPropertyMapper, "map()");
        connect(pObject, lPropertySignal, mPropertyMapper, lMapMethod, Qt::UniqueConnection);
        mSettingValueByName.insert(pName, value(pName));
    }
    return lSuccess;
}

bool Settings::subscribe(const QString &pName, QObject *pObject, const QByteArray &pSignature)
{
    bool lResult = false;

    if (!pObject || pSignature.isEmpty())
    {
        qDebug("Settings: could not subscribe - invalid parameter value");
        return lResult;
    }

    if ((lResult = isMethodCouldBeSubscribed(pObject, pSignature)))
    {
        QMetaMethod lMetaMethod = metaMethod(pObject, pSignature);
        mSubscribedObjectsBySetting.insert(pName, pObject);
        mSubscribedMethodBySetting.insert(pName, lMetaMethod.name());
    }
    return lResult;
}

void Settings::commit()
{
    if (!isModified())
    {
        return;
    }

    QMap<QString, QVariant>::const_iterator it;
    for (it = mModifiedSettingsByName.begin();
         it != mModifiedSettingsByName.end();
         it++)
    {
        mSettingValueByName.insert(it.key(), it.value());
        notifySubscribers(it.key(), it.value());
    }
    emit settingsChanged(mModifiedSettingsByName);
    mModifiedSettingsByName.clear();
}

void Settings::revert()
{
    if (!isModified())
    {
        return;
    }

    foreach (QString lName, mModifiedSettingsByName.keys())
    {
        QVariant lOldValue = mSettingValueByName.value(lName);
        setValue(lName, lOldValue);

        if (mAutoNotify)
        {
            notifySubscribers(lName, lOldValue);
        }
    }
    mModifiedSettingsByName.clear();
}

bool Settings::isPropertyCouldBeAttached(QObject *pObject, const QString &pProperty)
{
    bool lResult = false;
    QMetaProperty lMetaProperty = metaProperty(pObject, pProperty);
    if (lMetaProperty.isValid())
    {
        lResult = lMetaProperty.isValid()
            && lMetaProperty.isWritable()
            && lMetaProperty.isReadable()
            && lMetaProperty.hasNotifySignal();
    }
    return lResult;
}

bool Settings::isMethodCouldBeSubscribed(QObject *pObject, const QString &pSignature)
{
    bool rResult = false;

    QMetaMethod lMethod = metaMethod(pObject, pSignature);

    if (lMethod.isValid())
    {
        rResult = (lMethod.parameterCount() == 1)
            && (lMethod.parameterType(0) == QMetaType::QVariant);
    }

    return rResult;
}

void Settings::setAutoCommit(bool pAutoCommit)
{
    mAutoCommit = pAutoCommit;
}

void Settings::setAutoNotify(bool pAutoNotify)
{
    mAutoNotify = pAutoNotify;
}

bool Settings::isModified() const
{
    return !mModifiedSettingsByName.isEmpty();
}

void Settings::slotSetSettings(QMap<QString, QVariant> pMap)
{
    QMap<QString, QVariant>::const_iterator it;
    for (it = pMap.begin();
         it != pMap.end();
         it++)
    {
        mSettingValueByName.insert(it.key(), it.value());
        setValue(it.key(), it.value());
        notifySubscribers(it.key(), it.value());
    }
}

void Settings::setSettingsPath(const QString &pSettingsPath)
{
    mSettingsPath = pSettingsPath;
}

QVariant Settings::value(const QString &pSetting) const
{
    QVariant lResult;
    QObject *pObject = mObjectBySetting.value(pSetting);
    if (pObject && mPropertyBySetting.contains(pSetting))
    {
        lResult = pObject->property(mPropertyBySetting[pSetting].constData());
    }
    return lResult;
}

void Settings::setValue(const QString &pSetting, const QVariant &pValue)
{
    QObject *pObject = mObjectBySetting.value(pSetting);
    QByteArray pProperty = mPropertyBySetting.value(pSetting);
    if (pObject && !pProperty.isEmpty())
    {
        pObject->setProperty(pProperty.constData(), pValue);
    }
}

void Settings::notifySubscribers(const QString &pName, const QVariant &pValue)
{
    QObject *lObject = mSubscribedObjectsBySetting.value(pName);
    QByteArray lSignature = mSubscribedMethodBySetting.value(pName);
    invoke(lObject, lSignature, pValue);
}

QMetaProperty Settings::metaProperty(QObject *pObject, const QString &pProperty)
{
    QMetaProperty rMetaProperty;
    if (pObject)
    {
        if (const QMetaObject *lMetaObject = pObject->metaObject())
        {
            QByteArray data = pProperty.toUtf8();

            int lPropertyIndex = lMetaObject->indexOfProperty(data.constData());
            if (lPropertyIndex >= 0)
            {
                rMetaProperty = lMetaObject->property(lPropertyIndex);
            }
        }
    }
    else
    {
        qDebug("Settings::metaProperty: object is null");
    }
    return rMetaProperty;
}

QMetaMethod Settings::metaMethod(QObject *pObject, const QString &pSignature)
{
    QByteArray data = pSignature.toUtf8();
    if (QChar(data[0]).isDigit())
    {
        // First symbol of signature could be a number
        // in a case when SLOT() or METHOD() macro used for
        // passing signature. That number in Qt 5 user to determine
        // method type (signal, slot, method). In that case we will remove
        // first symbol to get a clean signature.
        data.remove(0, 1);
    }

    QByteArray lSignature = QMetaObject::normalizedSignature(data);

    if (pObject)
    {
        int lMethodIndex = pObject->metaObject()->indexOfMethod(lSignature);
        return pObject->metaObject()->method(lMethodIndex);
    }
    else
    {
        qDebug("Settings::metaMethod: object is null");
    }

    return QMetaMethod();
}

void Settings::invoke(QObject *pObject, const QByteArray &pSignature, const QVariant &pValue)
{
    if (pObject)
    {
        pObject->metaObject()->invokeMethod(pObject, pSignature.constData(),
                                            Qt::QueuedConnection, Q_ARG(QVariant, pValue));
    }
    else
    {
        qDebug("Settings::invoke: object is null");
    }
}

void Settings::propertyChanged(QString pName)
{
    QVariant settingValue = value(pName);
    if (mSettingValueByName.value(pName) != settingValue)
    {
        mModifiedSettingsByName.insert(pName, settingValue);
    }
    else
    {
        mModifiedSettingsByName.remove(pName);
    }

    if (mAutoCommit)
    {
        commit();
    }
    else
    {
        if (mAutoNotify)
        {
            notifySubscribers(pName, settingValue);
        }
    }
}
