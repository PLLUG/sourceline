#include "settingsmanager.h"

#include "settings.h"
#include "settingstorage.h"

SettingsManager::SettingsManager(QObject *parent) :
    QObject(parent),
    mStorage(0)
{
}

void SettingsManager::setStorage(SettingStorage *pStorage)
{
    mStorage = pStorage;
}

QString SettingsManager::pathBySettings(Settings *pSettings)
{
    return mPathBySettings.value(pSettings);
}

void SettingsManager::addSettings(const QString &pPluginId, const QString &pSettingsPageName, Settings *pSettings)
{
    mPluginIdBySettings.insert(pSettings, pPluginId);
    mPageNameBySettings.insert(pSettings, pSettingsPageName);
    QString lFullSettingsPath = QString("%1/%2/%3").arg(pPluginId).arg(pSettingsPageName).arg(pSettings->settingsPath());
    qDebug() << lFullSettingsPath;

    mPathBySettings.insert(pSettings, lFullSettingsPath);
}

void SettingsManager::slotWriteSettings(QMap<QString, QVariant> pMap)
{
    if (mStorage)
    {
        QString lPluginId = mPluginIdBySettings.value(sender());
        if (lPluginId.isEmpty())
        {
            qDebug("SettingsManager::slotWriteSettings: could not find plugin id for settings!");
            return;
        }

        QString lSettingsPageName = mPageNameBySettings.value(sender());
        if (lSettingsPageName.isEmpty())
        {
            qDebug("SettingsManager::slotWriteSettings: could not find settings page name for settings!");
            return;
        }

        QString lPath = mPathBySettings.value(sender());
        qDebug() << lPath;
        mStorage->slotSaveSettings(lPath, pMap);
    }
    else
    {
        qDebug("SettingsManager::slotWriteSettings: storage not set!");
    }
}
