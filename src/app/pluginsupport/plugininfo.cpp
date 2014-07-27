#include "plugininfo.h"



PluginInfo::PluginInfo(QString pPluginId, QString pVer, QString pDescr, QString pCategory, QHash<QString, QString> pAdditionalInfo):
    mPluginId(pPluginId),
    mVer(pVer),
    mDescr(pDescr),
    mCategory(pCategory),
    mAdditionalInfo(pAdditionalInfo)
{
}
QString PluginInfo::pluginId() const
{
    return mPluginId;
}

QString PluginInfo::ver() const
{
    return mVer;
}
QString PluginInfo::description() const
{
    return mDescr;
}
QString PluginInfo::category() const
{
    return mCategory;
}
QHash<QString, QString> PluginInfo::additionalInfo() const
{
    return mAdditionalInfo;
}

