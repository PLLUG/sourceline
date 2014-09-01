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

#include "actionmanager.h"
#include "strategies/sortingstrategy.h"
#include "useraction.h"

ActionManager::ActionManager(QObject *parent) :
    QObject(parent)
{
}

void ActionManager::add(MenuGroup pMenuGroups, UserAction *pAction)
{
    mActions[pMenuGroups].push_back(pAction);
}

QMenu *ActionManager::menuByMenuGroup(MenuGroup pMenuGroups) const
{
    return mStrategyByMenuGroup[pMenuGroups]->createMenu(mActions[pMenuGroups]);
}


void ActionManager::setMenuCreationStategy(MenuGroup pMenuGroups, MenuCreationStrategy *pStategy)
{
     mStrategyByMenuGroup[pMenuGroups] = pStategy;
}
