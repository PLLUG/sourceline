/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Mykola Molochiy (molochiy@gmail.com)                          ***
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

#include "customtabbar.h"
#include "ui_customtabbar.h"
#include "settings.h"
#include "settings_dialog/settingstorage.h"
#include "contentfortab.h"

#include <QDebug>
#include <QWidget>

CustomTabBar::CustomTabBar(SettingsManager *pSettingsManager, SettingStorage *pStorage, QWidget *parent) :
    QTabWidget(parent)
  ,ui(new Ui::CustomTabBar)
  ,mSettings{new Settings(this)}
  ,mStorage{pStorage}
  ,mSettingsManager{pSettingsManager}
{
    ui->setupUi(this);
    connect(this, SIGNAL(currentChanged(int)),this,SLOT(setAllTabsInvisibleExceptCurrentTab(int)));
    mSettings->setAutoCommit(true);
    mSettingsManager->addSettings("settingsTabs", "tab", mSettings);

    setTabsClosable(true);
    setMovable(true);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, &CustomTabBar::tabCloseRequested, this, &CustomTabBar::slotCloseWorkplace);
}

CustomTabBar::~CustomTabBar()
{
    delete ui;
}

void CustomTabBar::loadSettingsForTabs()
{
    mStorage->slotLoadSettings(mSettingsManager->pathBySettings(mSettings));
}

void CustomTabBar::slotAddNewWorkplace(const QString &pName)
{
    QTabWidget::addTab(new ContentForTab(this, pName), pName);
    setCurrentIndex(count()-1);
    mSettings->add(pName, getWidget(currentIndex()), "tabState");
    mSettings->subscribe(pName, getWidget(currentIndex()), SLOT(setTabState(QVariant)));
}

void CustomTabBar::slotCloseWorkplace(int pIndex)
{
    //TODO:check
    getWidget(pIndex)->close();
    getWidget(pIndex)->deleteLater();
}

void CustomTabBar::setAllTabsInvisibleExceptCurrentTab(int pIndex)
{   
    /*for(int i = 0; i < count(); i++)
    {

        if(i == pIndex)
        {
            getWidget(pIndex)->setVisibleForContent(true);
            //dynamic_cast<ContentForTabWorkplace*>(widget(pIndex))->restoreSettings();
            mStorage->slotLoadSettings(mSettingsManager->pathBySettings(mSettings));
        }
        else
        {
            if(getWidget(i)->isContentVisible())
            {
                getWidget(i)->sentSignalTabStateChanged();
                //mSettings->commit();
                getWidget(i)->setVisibleForContent(false);
            }
        }
    }*/
}

ContentForTab* CustomTabBar::getWidget(int pIndex)
{
    return dynamic_cast<ContentForTab*>(widget(pIndex));
}
