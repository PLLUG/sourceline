#ifndef DIALOGPLUGINS_H
#define DIALOGPLUGINS_H
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
#include "plugininfo.h"
#include <QList>
#include <QString>
#include <QDialog>
#include <QStringList>

class QSignalMapper;

class QTreeWidgetItem;
class Settings;

namespace Ui {
    class DialogPlugins;
}

class DialogPlugins : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPlugins(QWidget *parent = 0);
    ~DialogPlugins();
    /*!
     * \brief Adds plugin to list and all necessary information about it
     * \param pPluginInfo object which include description about plugin
     */
    void addPluginInfo(const PluginInfo& pPluginInfo);
    /*!
     * \brief Returns plugins description(used when user clicks on info button in row with plugin description).
     * \param pluginId Plugin identifier, for which info button was pressed.
     */
    QString requestInfoForPlugin(QString pPluginId);
    /*!
     * \brief  get information about plugins from files
     * \return dictionary where key word is plugin category and value is object which include description about plugin
     */
    void setPlugins(QList<PluginInfo> pPlugins);
    /*!
     * \brief Returns plugins that was enabled by user. Returns valid value after dialog execution.
     * \return List of active plugin identifiers.
     */
    QStringList activePlugins();
    /*!
     * \brief Shows when user wants to restart application to immediately appy all changes.
     *  Returns valid value after dialog execution.
     * \
     * return True if restart; false otherwise
     */
    bool restartApplication();
    void setActivatedPlugins(QList<QString> pActivatedPlugins);

private slots:
    /*!
     * \brief Shows plugins when when user clicks on info button in row with plugin description
     * \param pluginId Plugin identifier, for which info button was pressed.
     */
    void slotButtonPressed(QString pPluginId);
    /*!
     * \brief Change mIsApplyAndRestartPressed to true.
     */
    void slotApplyAndRestartPressed();
private:
    /*!
     * \brief create Plugins ui
     * \param pPlugins is plugin description
     */
    void createPluginsTree();
    /*!
     * \brief add plugin category into Plugins Tree
     * \param pCategory plugin Category. Plugins with the same categories are grouped together.
     * \param pName is plugin unique id
     * \param pVer is plugin version
     * \param pDescr is plugin short description
     */
    void addCategory(const QString& pCategory, const QString& pPluginId, const QString &pVer, const QString &pDescr);
    /*!
     * \brief add plugin into subtre QTreeWidgetItem which describe just category
     * \param pParent is QTreeWidgetItem which have the same categoty as plugin
     * \param pName is plugin unique id
     * \param pVer is plugin version
     * \param pDescr is plugin short description
     */
    void addPluginToCategory(QTreeWidgetItem *pParent, const QString& pPluginId, const QString &pVer, const  QString &pDescr);
    /*!
     * \brief function creates button for ui part.
     * \param pPluginItem is QTreeWidgetItem which include info about plugin in row in Plugin tree
     * \return pointer to button widget which will be in row with plugin description
     */
    QWidget* createButton(QTreeWidgetItem* pPluginItem);

signals:
    void signalStateChanged();

private:
    Ui::DialogPlugins *ui;
    QSignalMapper *mMapper;
    bool mIsApplyAndRestartPressed;
    QList<PluginInfo> mPlugins;
};

#endif // DIALOGPLUGINS_H
