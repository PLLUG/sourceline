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
 * \brief CommandProcess::start is func what start Process with two arguments shell and shell parameters
 */
void CommandProcess::start()
{
    //mProcess
    if(!mProcess->isOpen())
    {
        mProcess->start(mShell,mShellParam);
        mProcess->waitForStarted();
    }
    else{}
}

/*!
 * \brief CommandProcess::shell
 * \return shell name in QString
 */
QString CommandProcess::shell()
{
    return mShell;
}

/*!
 * \brief CommandProcess::setShell
 * \param shell
 */
void CommandProcess::setShell(const QString &shell)
{
    mShell = shell;
}

/*!
 * \brief CommandProcess::shellParam
 * \return
 */
QStringList CommandProcess::shellParam()
{
    return mShellParam;
}


/*!
 * \brief CommandProcess::setShellParam
 * \param shellParam
 */
void CommandProcess::setShellParam(const QStringList &shellParam)
{
    mShellParam = shellParam;
}

/*!
 * \brief CommandProcess::execute
 * \param command
 */
void CommandProcess::execute(const QString &command)
{
    //mProcess->write("echo off");
    mProcess->write(mData.append(command));
    //mProcess->closeWriteChannel();
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

void CommandProcess::shutdown()
{
    if(mProcess->isOpen()){
        mProcess->terminate();
        mProcess->close();
    }
}

CommandProcess::~CommandProcess()
{
    shutdown();
}
