#ifndef PLUGINSETTINGS_H
#define PLUGINSETTINGS_H

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


#include <QObject>
#include <QMultiMap>
#include <QVariant>
#include <QMetaProperty>
#include <QDebug>

#include <QSignalMapper>

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    QString settingsPath() const;
    void setSettingsPath(const QString& pSettingsPath);
    bool add(const QString& pName, QObject *pObject,
            const QString& pProperty);
    bool subscribe(const QString& pName, QObject *pObject,
            const QByteArray &pSignature);
    void commit();
    void revert();
    bool isPropertyCouldBeAttached(QObject *pObject,
            const QString& pProperty);
    bool isMethodCouldBeSubscribed(QObject *pObject,
            const QString &pSignature);

signals:
    void settingsChanged(QMap<QString, QVariant>);

public slots:
    void slotSetSettings(QMap<QString, QVariant> pMap);

private:
    QVariant value(const QString &pSetting) const;
    void setValue(const QString &pSetting, const QVariant &pValue);
    void notifySubscribers(const QString &pName, const QVariant &pValue);
    QMetaProperty metaProperty(QObject *pObject, const QString& pProperty);
    QMetaMethod metaMethod(QObject *pObject, const QByteArray &pSignature);
    void invoke(QObject *pObject, const QByteArray& pSignature, const QVariant &pValue);

private:
    QString mSettingsPath;
    QMap<QString, QObject*> mObjectBySetting;
    QMap<QString, QByteArray> mPropertyBySetting;
    QMap<QString, QObject*> mSubscribedObjectsBySetting;
    QMap<QString, QByteArray> mSubscribedMethodBySetting;
    QMap<QString, QVariant> mSettingValueByName;
    QMap<QString, QVariant> mModifiedSettingsByName;
    QSignalMapper *mPropertyMapper;

private slots:
    void propertyChanged(QString pName);

};

#endif // PLUGINSETTINGS_H
