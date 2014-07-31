/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Alex Chmykhalo (alexchmykhalo@users.sourceforge.net)          ***
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

#include "command.h"

#include <QStringList>

const QChar ARGUMENT_SEPARATOR(' ');

Command::Command(QObject *parent) :
    QObject(parent)
{
}

QString Command::name() const
{
    return mName;
}

QIcon Command::icon() const
{
    return mIcon;
}

Command::CommandFlags Command::flags() const
{
    return NoFlags;
}

QString Command::toString() const
{
    return QString("%1 %2")
        .arg(commandString())
        .arg(parametersList().join(ARGUMENT_SEPARATOR));
}

void Command::setName(const QString &pName)
{
    mName = pName;
}

void Command::setIcon(const QIcon &pIcon)
{
    mIcon = pIcon;
}
