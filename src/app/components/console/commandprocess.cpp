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

#include "commandprocess.h"

#include <QProcess>

CommandProcess::CommandProcess(QObject *parent)
    : QObject(parent),
      mProcess(new QProcess(this))
{
    connect(mProcess, SIGNAL(started()), this, SIGNAL(started()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(finished(int)), this, SIGNAL(finished()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(readyReadStandardError()), this, SLOT(readStandardError()), Qt::UniqueConnection);
}

/*!
 * \brief CommandProcess::execute
 * \param shell
 * \param command
 * \param parameters
 */
void CommandProcess::execute(QString shell, QString command, QStringList parameters)
{
    //mProcess
    mProcess->start(shell);
    mProcess->waitForStarted();
    mProcess->write(command);
    mProcess->closeWriteChannel();
    mProcess->waitForFinished();

    //remove to the 2 next funcs
    QString out = mProcess->readAllStandardOutput();
    if(!out.isEmpty())
    {
        emit standardOutput(out);
    }
    out = mProcess->readAllStandardError();
    else if(!out.isEmpty())
    {
        emit errorOutput(out);
    }
}

void CommandProcess::readStandardOutput()
{

}

void CommandProcess::readStandardError()
{

}

