/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
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

#include "pluginsettings.h"

PluginSettings::PluginSettings(QObject *parent) :
    QObject(parent),
    mPropertyMapper(new QSignalMapper(this))
{
    connect(mPropertyMapper, SIGNAL(mapped(QString)),
            this, SLOT(propertyChanged(QString)), Qt::UniqueConnection);
}

QString PluginSettings::settingsPath() const
{
    return mSettingsPath;
}

bool PluginSettings::add(const QString &pName, QObject *pObject, const QString &pProperty)
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

bool PluginSettings::subscribe(const QString &pName, QObject *pObject, const QByteArray &pSignature)
{
    bool lResult = false;
    if (!pObject || pSignature.isEmpty())
    {
        qDebug("Settings: could not subscribe - invalid parameter value");
    }
    if ((lResult = isMethodCouldBeSubscribed(pObject, pSignature)))
    {
        mSubscribedObjectsBySetting.insert(pName, pObject);
        mSubscribedMethodBySetting.insert(pName, pSignature);
    }
    return lResult;
}

void PluginSettings::commit()
{
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

void PluginSettings::revert()
{
    foreach (QString lName, mModifiedSettingsByName.keys())
    {
        QVariant oldValue = mSettingValueByName.value(lName);
        setValue(lName, oldValue);
    }
    mModifiedSettingsByName.clear();
}

bool PluginSettings::isPropertyCouldBeAttached(QObject *pObject, const QString &pProperty)
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

bool PluginSettings::isMethodCouldBeSubscribed(QObject *pObject, const QString &pSignature)
{
    //.........
    return true;
}

void PluginSettings::slotSetSettings(QMap<QString, QVariant> pMap)
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

void PluginSettings::setSettingsPath(const QString &pSettingsPath)
{
    mSettingsPath = pSettingsPath;
}

QVariant PluginSettings::value(const QString &pSetting) const
{
    QVariant lResult;
    QObject *pObject = mObjectBySetting.value(pSetting);
    if (pObject && mPropertyBySetting.contains(pSetting))
    {
        lResult = pObject->property(mPropertyBySetting[pSetting].constData());
    }
    return lResult;
}

void PluginSettings::setValue(const QString &pSetting, const QVariant &pValue)
{
    QObject *pObject = mObjectBySetting.value(pSetting);
    QByteArray pProperty = mPropertyBySetting.value(pSetting);
    if (pObject && !pProperty.isEmpty())
    {
        pObject->setProperty(pProperty.constData(), pValue);
    }
}

void PluginSettings::notifySubscribers(const QString &pName, const QVariant &pValue)
{
    QObject *lObject = mSubscribedObjectsBySetting.value(pName);
    QByteArray lSignature = mSubscribedMethodBySetting.value(pName);
    invoke(lObject, lSignature, pValue);
}

QMetaProperty PluginSettings::metaProperty(QObject *pObject, const QString &pProperty)
{
    QMetaProperty rMetaProperty;
    if (const QMetaObject *lMetaObject = pObject->metaObject())
    {
        QByteArray data = pProperty.toUtf8();
        int lPropertyIndex = lMetaObject->indexOfProperty(data.constData());
        if (lPropertyIndex >= 0)
        {
            rMetaProperty = lMetaObject->property(lPropertyIndex);
        }
    }
    return rMetaProperty;
}

QMetaMethod PluginSettings::metaMethod(QObject *pObject, const QByteArray &pSignature)
{
    QByteArray lSignature = QMetaObject::normalizedSignature(pSignature.constData());
    int lMethodIndex = pObject->metaObject()->indexOfSlot(lSignature);
    return mPropertyMapper->metaObject()->method(lMethodIndex);
}

void PluginSettings::invoke(QObject *pObject, const QByteArray &pSignature, const QVariant &pValue)
{
    pObject->metaObject()->invokeMethod(pObject, pSignature.constData(),
                                        Qt::QueuedConnection, Q_ARG(QVariant, pValue));
}

void PluginSettings::propertyChanged(QString pName)
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
}
