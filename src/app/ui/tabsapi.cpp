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

#include "tabsapi.h"
#include "customtabbar.h"

TabsAPI::TabsAPI(QObject *parent):
    QObject(parent)
{

}

int TabsAPI::getCurrentIndex(CustomTabBar *pTabBar)
{    
    return pTabBar->currentIndex();
}

int TabsAPI::getCountTabs(CustomTabBar *pTabBar)
{
    return pTabBar->count();
}

void TabsAPI::loadSettingsForTabs(CustomTabBar *pTabBar)
{
    pTabBar->loadSettingsForTabs();
}

QString TabsAPI::getNameOfTabById(CustomTabBar *pTabBar, int pId) const
{
    return pTabBar->tabText(pId);
}

QWidget* getCurrentWidget(CustomTabBar *pTabBar)
{
    return pTabBar->currentWidget();
}

QWidget* getWidget(CustomTabBar *pTabBar, int pIndex)
{
    return pTabBar->widget(pIndex);
}

void TabsAPI::slotAddNewWorkplace(CustomTabBar *pTabBar, const QString &pName)
{
    pTabBar->slotAddNewWorkplace(pName);
}

void TabsAPI::slotCloseWorkplace(CustomTabBar *pTabBar, int pIndex)
{
    pTabBar->slotCloseWorkplace(pIndex);
}
