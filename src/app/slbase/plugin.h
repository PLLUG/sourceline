#ifndef PLUGIN_H
#define PLUGIN_H
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
#include "plugin-interface.h"

#include "pluginapi.h"

#define REGISTER_COMMAND(aggregator, CommandClass, kind)\
    aggregator.object<PluginAPI>()->registerCommand(CommandClass::staticMetaObject, kind);

class Plugin :
        public QObject,
        public PluginInterface
{
    Q_OBJECT
    Q_INTERFACES(PluginInterface)
public:
    explicit Plugin(QObject *pParent = 0);

    QList<Command *> commands(Commands::CommandKind kind = Commands::UknownKind) final;

    QObjectList components() const;

protected:
     void addComponent(QObject *pComponent);
     void registerCommand(Command *command);

private:
     QObjectList mComponents;
     QList<Command *> mListCommands;
};

#endif // PLUGIN_H
