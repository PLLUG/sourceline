/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Olexandr Lynda (sanya.l9519@gmail.com)                        ***
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

#include "commandprocessmediator.h"
#include <QProcess>
#include <QVariant>

CommandProcessMediator::CommandProcessMediator(QObject *parent) : QObject(parent)
{
    mProcess = new CommandProcess(this);
    // !!hardcode!! , dont work on linux , set for "shell" property "sh"
    mProcess->setProperty("shell","C:/Windows/System32/cmd");
    mProcess->setProperty("shellParam",QStringList()<< "/k");
    mProcess->start();

    connect(this, SIGNAL(execute(QString)), mProcess, SLOT(execute(QString)));
    connect(mProcess, SIGNAL(started()), this, SIGNAL(processStarted()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(finished()), this, SIGNAL(processFinished()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(standardOutput(QByteArray)), this, SIGNAL(processStandardOutput(QByteArray)), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(errorOutput(QByteArray)), this, SIGNAL(processErrorOutput(QByteArray)), Qt::UniqueConnection);
}

void CommandProcessMediator::processConsoleInput(QString input)
{
    emit execute(input);
}

void CommandProcessMediator::registerCommand(QString commandId, QString inputPattern)
{
    Q_UNUSED(commandId)
    Q_UNUSED(inputPattern)
}

