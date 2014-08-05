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
#include "dialogplugins.h"
#include "ui_dialogplugins.h"
#include <QFile>
#include <QTreeWidgetItem>
#include <QTextStream>
#include <QPushButton>
#include <QSignalMapper>
#include <QDebug>

DialogPlugins::DialogPlugins(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlugins),
    mIsApplyAndRestartPressed(false)
{
   ui->setupUi(this);
}
DialogPlugins::~DialogPlugins()
{
    delete ui;
}
void DialogPlugins::setPlugins(QList<PluginInfo> pPlugins)
{
    mPlugins = pPlugins;
    ui->pluginsTree->clear();
    createPluginsTree();
    connect(ui->applyAndRestartButton, SIGNAL(clicked()), this, SLOT(slotApplyAndRestartPressed()), Qt::UniqueConnection);
//    QTreeWidgetItem* lCategoryIndex = ui->pluginsTree->topLevelItem(i);
//        QTreeWidgetItem *lPluginIndex = lCategoryIndex->child(j);
//       qDebug() << lPluginIndex->text(0);
}

void DialogPlugins::createPluginsTree()
{
    ui->pluginsTree->setColumnCount(4);
    ui->pluginsTree->setHeaderLabels(QStringList()  << tr("Plugin Group/Name^") << tr("Ver") << tr("Short Description") << "");
    mMapper = new QSignalMapper(this);
    foreach (const PluginInfo &lPluginInfo, mPlugins)
    {
       addPluginInfo(lPluginInfo);
    }
    connect(mMapper, SIGNAL(mapped(QString)), this, SLOT(slotButtonPressed(QString)), Qt::UniqueConnection);
}
void DialogPlugins::addPluginInfo(const PluginInfo& pPluginInfo)
{
    QString lCategory = pPluginInfo.category();
    QList<QTreeWidgetItem *> lCategoriesList =  ui->pluginsTree->findItems(lCategory, Qt::MatchFixedString, 0);
    if(lCategoriesList.size() == 0)
    {
        addCategory(lCategory, pPluginInfo.pluginId(), pPluginInfo.ver(), pPluginInfo.description());
    }
    else
    {
        addPluginToCategory(lCategoriesList[0], pPluginInfo.pluginId(), pPluginInfo.ver(), pPluginInfo.description());
    }
}
void DialogPlugins::addCategory(const QString& pCategory, const QString& pPluginId, const QString &pVer, const QString &pDescr)
{
      QTreeWidgetItem *lCategoryItem =new QTreeWidgetItem(ui->pluginsTree);
      ui->pluginsTree->addTopLevelItem(lCategoryItem);
      lCategoryItem->setText(0, pCategory);
      addPluginToCategory(lCategoryItem, pPluginId, pVer, pDescr);
}
void DialogPlugins::addPluginToCategory(QTreeWidgetItem *pParent, const QString& pPluginId, const QString &pVer, const  QString &pDescr)
{
    QTreeWidgetItem *lPluginItem =new QTreeWidgetItem(pParent);
    lPluginItem->setText(0, pPluginId);
    lPluginItem->setText(1, pVer);
    lPluginItem->setText(2, pDescr);
    ui->pluginsTree->setItemWidget(lPluginItem, 3, createButton(lPluginItem));
    lPluginItem->setFlags(lPluginItem->flags() | Qt::ItemIsUserCheckable);
    lPluginItem->setCheckState(0, Qt::Unchecked);
    pParent->addChild(lPluginItem);
}
QWidget* DialogPlugins::createButton(QTreeWidgetItem* pPluginItem)
{
    QSize lSize( 20,20 );
    QPushButton *lPushButton = new QPushButton( QIcon( ":/splash/img/pluginInformation.gif" ), QString::null, this);
    lPushButton->setAutoFillBackground( true );
    lPushButton->setIconSize( lSize );
    lPushButton->setMinimumSize( lSize );
    lPushButton->setMaximumSize( lSize );
    lPushButton->setToolTip( QString( tr("info about plugin %1?") ).arg( pPluginItem->text(0) ) );

    mMapper->setMapping(lPushButton, pPluginItem->text(0));
    connect(lPushButton, SIGNAL(clicked()), mMapper, SLOT(map()), Qt::UniqueConnection);
    return lPushButton;
}
void DialogPlugins::slotButtonPressed(QString pPluginId)
{
    qDebug() << requestInfoForPlugin(pPluginId) << " " << pPluginId;
}
QString DialogPlugins::requestInfoForPlugin(QString pPluginId)
{
    int lCountOfTopLevelItem = ui->pluginsTree->topLevelItemCount();
    for (int i = 0; i < lCountOfTopLevelItem; ++i)
    {
        QTreeWidgetItem* lCategoryIntem = ui->pluginsTree->topLevelItem(i);
        unsigned lCountOfPluginsInCategory = lCategoryIntem->childCount();
        for (unsigned i = 0; i < lCountOfPluginsInCategory; ++i)
        {
            QTreeWidgetItem* lPlugin = lCategoryIntem->child(i);
            if(lPlugin->text(0) == pPluginId)
            {
                return lPlugin->text(2);
            }
        }
    }
    return "";
}
QStringList DialogPlugins::activePlugins()
{
    QList<QTreeWidgetItem *> lSelectedPlugins = ui->pluginsTree->selectedItems();
    QStringList rSelectedPlugins;
    foreach (QTreeWidgetItem* lPlugin, lSelectedPlugins)
    {
        rSelectedPlugins.append(lPlugin->text(0));
    }
    return rSelectedPlugins;
}
void DialogPlugins::slotApplyAndRestartPressed()
{
    mIsApplyAndRestartPressed = true;
    emit accept();
}

bool DialogPlugins::restartApplication()
{
    return mIsApplyAndRestartPressed;
}

void DialogPlugins::setActivatedPlugins(QList<QString> pActivatedPlugins)
{
    int lCountOfTopLevelItem = ui->pluginsTree->topLevelItemCount();
    for (int i = 0; i < lCountOfTopLevelItem; ++i)
    {
        QTreeWidgetItem* lCategoryIndex = ui->pluginsTree->topLevelItem(i);
        int countOfPluginIndex = lCategoryIndex->childCount();
        for (int j = 0; j < countOfPluginIndex; ++j)
        {
            QTreeWidgetItem *lPluginIndex = lCategoryIndex->child(j);
            if (pActivatedPlugins.contains(lPluginIndex->text(0)))
            {
                lPluginIndex->setCheckState(0, Qt::Checked);
            }
        }
    }
}



