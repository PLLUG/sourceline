#ifndef PLUGINDESCRIPTION_H
#define PLUGINDESCRIPTION_H

#include <QString>
#include <QHash>

class PluginInfo
{
public:
    PluginInfo(QString pPluginId, QString pVer, QString pDescr, QString pCategory, QHash<QString, QString> pAdditionalInfo);
    QString pluginId() const;
    QString ver() const;
    QString description() const;
    QString category() const ;
    QHash<QString, QString> additionalInfo() const;
private:
    QString mPluginId;
    QString mVer;
    QString mDescr;
    QString mCategory;
    QHash<QString, QString> mAdditionalInfo;
};

#endif // PLUGINDESCRIPTION_H
