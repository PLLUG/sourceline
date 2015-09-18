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

#include "commandcomponentsupplier.h"
#include <command.h>
#include "../../ui/useraction.h"
#include "../../ui/actionmanager.h"
#include "plugininfo.h"

CommandComponentSupplier::CommandComponentSupplier() :
    mActionManager(nullptr)
{
}

QString CommandComponentSupplier::className() const
{
    return Command::staticMetaObject.className();
}

void CommandComponentSupplier::setActionManager(ActionManager *pActionManager)
{
    mActionManager = pActionManager;
}

UserAction *CommandComponentSupplier::actionFromCommand(Command *pComand)
{
    UserAction *rUserAction = new UserAction();
    rUserAction->setIcon(pComand->icon());
    rUserAction->setText(pComand->name());
    rUserAction->setCommandKind(Commands::ImportCommand);
    return rUserAction;
}

void CommandComponentSupplier::supply(QObject *pComponent, const PluginInfo &pPluginInfo)
{
    Q_UNUSED(pPluginInfo);
    if (Command* lCommand = qobject_cast<Command*>(pComponent))
    {
        mActionManager->add(MenuGroup::HelpMenuGroup, actionFromCommand(lCommand));
    }
}
