#ifndef PLUGINSETTINGSMEDIATOR_H
#define PLUGINSETTINGSMEDIATOR_H
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
#include <QObject>

class PluginManager;
class DialogPlugins;
class PropertyInfoDialog;

class PluginSettingsMediator : public QObject
{
    Q_OBJECT
public:
    explicit PluginSettingsMediator(QObject *parent = 0);

    /*!
     * \brief Sets plugin manager instance,
     * \param pManager Pointer to PluginManager.
     */
    void setPluginManager(PluginManager *pManager);

    /*!
     * \brief Sets PluginDialog instance (class that implements dialog for plugin settings.)
     *  Dialog will be shown by calling PluginSettingsMediator::slotExecPluginSettings method.
     * \param pDialog Pointer to PluginDialog.
     */
    void setPluginDialog(DialogPlugins *pDialog);

    /*!
     * \brief Sets PropertyInfoDialog instance that will be used for displaying info about plugin
     *  (will appear after pressing info (i) button in a row of certain plugin description).
     */
    void setPluginInfoDialog(PropertyInfoDialog *pDialog);

signals:
    /*!
     * \brief Will be emited if after setting plugins user wants to restart applicaiton to immediately
     *  apply all changes.
     */
    void programRestartNeeded();

public slots:
    /*!
     * \brief Will populate PluginDialog with list of avilable plugins. After that
     *  method will executes dialog for user. If user will apply settings,
     *  PluginSettingsMediator will configure plugins using PluginManager.
     */
    void slotExecPluginSettings();

private slots:

    /*!
     * \brief Shows additional info about plugin. Information will be shown using PropertyInfoDialog.
     */
    void slotShowPluginInfo(const QString &pPluginID);

private:
    DialogPlugins *mDialog;
    PluginManager *mManager;
    PropertyInfoDialog *mInfoDialog;
};

#endif // PLUGINSETTINGSMEDIATOR_H
