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
#include "settings.h"
#include "plugininfodialog.h"
#include <QTreeWidgetItem>
#include <QTextStream>
#include <QPushButton>
#include <QSignalMapper>
#include <QDebug>
#include <QMessageBox>

DialogPlugins::DialogPlugins(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPlugins),
    mMapper{nullptr},
    mIsApplyAndRestartPressed(false)
{
    ui->setupUi(this);
}

DialogPlugins::~DialogPlugins()
{
    delete ui;
}

void DialogPlugins::setPlugins(const QList<PluginInfo> &pPlugins)
{
    mPlugins = pPlugins;
    ui->pluginsTree->clear();
    createPluginsTree();
    connect(ui->applyAndRestartButton, SIGNAL(clicked()), this, SLOT(slotApplyAndRestartPressed()), Qt::UniqueConnection);
}

/*!
 * \brief DialogPlugins::createPluginsTree create Plugins ui
 * \param pPlugins is plugin description
 */
void DialogPlugins::createPluginsTree()
{
    ui->pluginsTree->setColumnCount(4);
    ui->pluginsTree->setHeaderLabels(QStringList()  << tr("Plugin Group/Name^") << tr("Ver") << tr("Short Description") << "");
    mMapper = new QSignalMapper(this);
    for(const PluginInfo &lPluginInfo: mPlugins)
    {
        addPluginInfo(lPluginInfo);
    }
    connect(mMapper, SIGNAL(mapped(QString)), this, SLOT(slotButtonPressed(QString)), Qt::UniqueConnection);
}

/*!
 * \brief DialogPlugins::addPluginInfo Adds plugin to list and all necessary information about it
 * \param pPluginInfo object which include description about plugin
 */
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

/*!
 * \brief DialogPlugins::addCategory add plugin category into Plugins Tree
 * \param pCategory plugin Category. Plugins with the same categories are grouped together.
 * \param pName is plugin unique id
 * \param pVer is plugin version
 * \param pDescr is plugin short description
 */
void DialogPlugins::addCategory(const QString& pCategory, const QString& pPluginId, const QString &pVer, const QString &pDescr)
{
    QTreeWidgetItem *lCategoryItem = new QTreeWidgetItem(ui->pluginsTree);
    ui->pluginsTree->addTopLevelItem(lCategoryItem);
    lCategoryItem->setText(0, pCategory);
    addPluginToCategory(lCategoryItem, pPluginId, pVer, pDescr);
}

/*!
 * \brief add plugin into subtre QTreeWidgetItem which describe just category
 * \param pParent is QTreeWidgetItem which have the same categoty as plugin
 * \param pName is plugin unique id
 * \param pVer is plugin version
 * \param pDescr is plugin short description
 */
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

/*!
 * \brief function creates button for ui part.
 * \param pPluginItem is QTreeWidgetItem which include info about plugin in row in Plugin tree
 * \return pointer to button widget which will be in row with plugin description
 */
QWidget* DialogPlugins::createButton(QTreeWidgetItem* pPluginItem)
{
    QSize lSize( 20,20 );
    QPushButton *rPushButton = new QPushButton( QIcon( ":/splash/img/pluginInformation.gif" ), QString::null, this);
    rPushButton->setAutoFillBackground( true );
    rPushButton->setIconSize( lSize );
    rPushButton->setMinimumSize( lSize );
    rPushButton->setMaximumSize( lSize );
    rPushButton->setToolTip( QString( tr("info about plugin %1?") ).arg( pPluginItem->text(0) ) );

    mMapper->setMapping(rPushButton, pPluginItem->text(0));
    connect(rPushButton, SIGNAL(clicked()), mMapper, SLOT(map()), Qt::UniqueConnection);
    return rPushButton;
}

/*!
 * \brief DialogPlugins::slotButtonPressed Shows plugins when when user clicks on info button in row with plugin description
 * \param pluginId Plugin identifier, for which info button was pressed.
 */
void DialogPlugins::slotButtonPressed(QString pPluginId)
{
    for(const PluginInfo& lPluginInfo: mPlugins)
    {
        if (lPluginInfo.pluginId() == pPluginId)
        {
            //TODO: fix memory leak
            PluginInfoDialog *lPluginInfoDialog = new PluginInfoDialog(this);
            lPluginInfoDialog->setPluginName(pPluginId);
            lPluginInfoDialog->setPluginInfo(lPluginInfo.additionalInfo());
            lPluginInfoDialog->show();
            return;
        }
    }
    QMessageBox::critical(this, tr("Error"), tr("No additional info available"));
}

/*!
 * \brief DialogPlugins::requestInfoForPlugin Returns plugins description(used when user clicks on info button in row with plugin description).
 * \param pPluginId Plugin identifier, for which info button was pressed.
 * \return Plugins description(used when user clicks on info button in row with plugin description).
 */
QString DialogPlugins::requestInfoForPlugin(const QString &pPluginId)
{
    int lCountOfTopLevelItem = ui->pluginsTree->topLevelItemCount();
    for (int i = 0; i < lCountOfTopLevelItem; ++i)
    {
        QTreeWidgetItem* lCategoryItem = ui->pluginsTree->topLevelItem(i);
        unsigned lCountOfPluginsInCategory = lCategoryItem->childCount();
        for (unsigned i = 0; i < lCountOfPluginsInCategory; ++i)
        {
            QTreeWidgetItem* lPlugin = lCategoryItem->child(i);
            if(lPlugin->text(0) == pPluginId)
            {
                return lPlugin->text(2);
            }
        }
    }
    return tr("");
}

/*!
 * \brief DialogPlugins::activePlugins Returns plugins that was enabled by user. Returns valid value after dialog execution.
 * \return List of active plugin identifiers.
 */
QStringList DialogPlugins::activePlugins() const
{
    QStringList rSelectedPlugins;
    for(const QTreeWidgetItem* lPlugin: ui->pluginsTree->selectedItems())
    {
        if(lPlugin->columnCount())
            rSelectedPlugins.append(lPlugin->text(0));
    }
    return std::move(rSelectedPlugins);
}

/*!
 * \brief DialogPlugins::slotApplyAndRestartPressed Change mIsApplyAndRestartPressed to true.
 */
void DialogPlugins::slotApplyAndRestartPressed()
{
    mIsApplyAndRestartPressed = true;
    emit accept();
}

/*!
 * \brief DialogPlugins::isRestartRequstedByUser Shows when user wants to restart application to immediately appy all changes.
 * \return Returns True if restart is requested, false otherwise.
 */
bool DialogPlugins::isRestartRequstedByUser() const
{
    return mIsApplyAndRestartPressed;
}

void DialogPlugins::setActivatedPlugins(const QList<QString> &pActivatedPlugins)
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
