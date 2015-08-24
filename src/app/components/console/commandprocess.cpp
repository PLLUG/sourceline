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
    //QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    //mProcess->setProcessEnvironment(env);
    //mProcess->setProcessChannelMode(QProcess::MergedChannels);

    connect(mProcess, SIGNAL(started()), this, SIGNAL(started()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(finished(int)), this, SIGNAL(finished()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(readStandardOutput()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(readyReadStandardError()), this, SLOT(readStandardError()), Qt::UniqueConnection);
    connect(mProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(slotAfterFinished(int,int)));
}

/*!
 * \brief CommandProcess::execute
 * \param shell
 * \param command
 * \param parameters
 */
void CommandProcess::execute(const QString &shell, const QString &command,const QStringList &parameters)
{
    //mProcess
    mProcess->start(shell,parameters);
    mProcess->waitForStarted();
    //mProcess->write("echo off");
    mProcess->write(mData.append(command));
    mProcess->closeWriteChannel();
    //mProcess->waitForFinished();
}

void CommandProcess::readStandardOutput()
{
    mData.clear();
    mData = mProcess->readAllStandardOutput();
    if(!mData.isEmpty())
    {
        emit standardOutput(mData);
        mData.clear();
    }
}

void CommandProcess::readStandardError()
{
    mData.clear();
    mData = mProcess->readAllStandardError();
    if(!mData.isEmpty())
    {
        emit errorOutput(mData);
        mData.clear();
    }
}

void CommandProcess::slotAfterFinished(int exitStatus, int exitCode)
{
    Q_UNUSED(exitStatus)
    Q_UNUSED(exitCode)
    mProcess->close();
    readStandardOutput();
    readStandardError();
}

