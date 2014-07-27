#include "pluginsettingsmediator.h"
#include "pluginmanager.h"
#include "../ui/dialogplugins.h"

PluginSettingsMediator::PluginSettingsMediator(QObject *parent) :
    QObject(parent),
    mDialog(NULL),
    mManager(NULL),
    mInfoDialog(NULL)
{
}

void PluginSettingsMediator::setPluginManager(PluginManager *pManager)
{
    mManager = pManager;
}

void PluginSettingsMediator::setPluginDialog(DialogPlugins *pDialog)
{
    mDialog = pDialog;
}

void PluginSettingsMediator::setPluginInfoDialog(PropertyInfoDialog *pDialog)
{

}

void PluginSettingsMediator::slotExecPluginSettings()
{
    QList<PluginInfo> lPluginsInfo = mManager->pluginsInfo();
    mDialog->setPlugins(lPluginsInfo);
    QList<QString> lActivatedPlugins = mManager->activePlugins();
    mDialog->setActivatedPlugins(lActivatedPlugins);
    int lResult = mDialog->exec();
    if (QDialog::Accepted == lResult)
    {
        QStringList lActivePluginsList = mDialog->activePlugins();
        // Init plugins ....

        if (mDialog->restartApplication())
        {
            // Notify application - restart needed
        }
    }
}

void PluginSettingsMediator::slotShowPluginInfo(const QString &pPluginID)
{

}
