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
#include "contentfortabworkplace.h"
#include "settings.h"
#include "settings_dialog/settingstorage.h"

#include <QDebug>
#include <QWidget>

CustomTabBar::CustomTabBar(SettingsManager *pSettingsManager, SettingStorage *pStorage, QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::CustomTabBar)
{
    ui->setupUi(this);
    this->setTabsClosable(true);
    this->setMovable(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(slotCloseWorkplace(int)));
    connect(this, SIGNAL(currentChanged(int)),this,SLOT(setAllTabsInvisibleExceptCurrentTab(int)));    
    mSettings = new Settings(this);
    mSettings->setAutoCommit(true);
    mSettingsManager = pSettingsManager;
    mSettingsManager->addSettings("settingsTabs", "tab", mSettings);
    mStorage = pStorage;
    //mStorage->slotLoadSettings(mSettingsManager->pathBySettings(mSettings));
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
    QTabWidget::addTab(new ContentForTabWorkplace(this, pName), pName);
    setCurrentIndex(this->count()-1);    
    mSettings->add(pName, getWidget(currentIndex()), "tabState");
    mSettings->subscribe(pName, getWidget(currentIndex()), SLOT(setTabState(QVariant)));
}

void CustomTabBar::slotCloseWorkplace(int pIndex)
{
    getWidget(pIndex)->close();
    getWidget(pIndex)->~ContentForTabWorkplace();
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

ContentForTabWorkplace* CustomTabBar::getWidget(int pIndex)
{
    return dynamic_cast<ContentForTabWorkplace*>(widget(pIndex));
}
