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
    explicit DialogPlugins(QWidget *parent = nullptr);
    ~DialogPlugins();

    void addPluginInfo(const PluginInfo& pPluginInfo);
    QString requestInfoForPlugin(const QString &pPluginId);
    void setPlugins(const QList<PluginInfo> &pPlugins);

    QStringList activePlugins() const;

    bool isRestartRequstedByUser() const;
    void setActivatedPlugins(const QList<QString> &pActivatedPlugins);

private slots:
    void slotButtonPressed(QString pPluginId);
    void slotApplyAndRestartPressed();

private:
    void createPluginsTree();
    void addCategory(const QString& pCategory, const QString& pPluginId, const QString &pVer, const QString &pDescr);
    void addPluginToCategory(QTreeWidgetItem *pParent, const QString& pPluginId, const QString &pVer, const  QString &pDescr);
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
