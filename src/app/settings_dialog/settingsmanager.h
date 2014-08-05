#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QObject>
#include <QMap>
#include <QVariant>

class Settings;
class SettingStorage;

class SettingsManager : public QObject
{
    Q_OBJECT
public:
    explicit SettingsManager(QObject *parent = 0);

    void setStorage(SettingStorage *);
    QString pathBySettings(Settings *pSettings);

    void addSettings(const QString &pPluginId, const QString &pSettingsPageName, Settings *pSettings);

signals:

public slots:
    void slotWriteSettings(QMap<QString, QVariant> pMap);

private:
    QMap<QObject *, QString> mPluginIdBySettings;
    QMap<QObject *, QString> mPageNameBySettings;
    QMap<QObject *, QString> mPathBySettings;

    SettingStorage *mStorage;
};

#endif // SETTINGSMANAGER_H
