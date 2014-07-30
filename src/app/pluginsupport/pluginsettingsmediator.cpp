/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Priyma Yuriy (priymayuriy@gmail.com)                          ***
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
