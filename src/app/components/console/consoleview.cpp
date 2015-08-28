/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
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

#include "consoleview.h"
#include "ui_consoleview.h"
#include <QDebug>
#include "commandprocessmediator.h"
// make input work
// remove platform dependent ifs +
// amke Q_PROPERTY for commandprocess +
//    * pommand interpreter
// make methods to commandprocess
//     * start() +
//     * shutdown() +
// all console input send to process stdin


ConsoleView::ConsoleView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleView)
{
    mReadOnlyIndicator = "~>";
    mDirPrinted = true;
    CommandProcessMediator *mediator = new CommandProcessMediator(this);
    mCmdProcess = new CommandProcess(this);
    mCmdProcess->setProperty("shell","C:\\Windows\\System32\\cmd");
    mCmdProcess->setProperty("shellParam",QStringList()<< "/k");
    mCmdProcess->start();

    ui->setupUi(this);
    ui->plainTextEdit->setLocalEchoEnabled(true);
    ui->plainTextEdit->putData(clearAppend(mReadOnlyIndicator));

    connect(ui->plainTextEdit, SIGNAL(signalSendCmd(QString)), this, SLOT(slotExec(QString)));

    connect(mCmdProcess, SIGNAL(started()), this, SLOT(slotLock()));
    connect(mCmdProcess, SIGNAL(finished()), this, SLOT(slotUnlock()));
    connect(this, &ConsoleView::commandEntered, mediator, &CommandProcessMediator::processConsoleInput);
    connect(mCmdProcess, SIGNAL(standardOutput(QByteArray)), this, SLOT(slotOut(QByteArray)));
    connect(mCmdProcess, SIGNAL(errorOutput(QByteArray)), this, SLOT(slotOut(QByteArray)));

    //Debug connections
    connect(ui->plainTextEdit, SIGNAL(blockCountChanged(int)),SLOT(debugBlockCountChanged(int)));
}

void ConsoleView::debugBlockCountChanged(int count)
{
    //Debug func
    qDebug() << "ConsoleView::BlockCountChanged to : " << count;
}

/*!
* \brief ConsoleView::toExecute is function what prepare all to execute the command
* \param pCommand is QString line what entered user for executing
*/
void ConsoleView::toExecute(const QString &pCommand) //as command use @cd C:\Users&ls -R@ or @tree C:\ /A@
{
    ui->plainTextEdit->putData("\n");

    // !!hardcode!! , dont work on linux


        emit commandEntered(pCommand);
}

/*!
 * function System Info.
 * To know what in what OS is running SL.
 */
QString ConsoleView::osInfo() const
{
    return QSysInfo::productType();
}

/*!
 * function what return current PATH for QProcess::setWorkingDirectory
 */
const QString ConsoleView::consolePath()
{
    return mPath;
}

void ConsoleView::slotExec(QString cmd)
{
    cmd +='\n';
    mDirPrinted = false;
    toExecute(cmd);
}

void ConsoleView::slotOut(QByteArray out)
{
    if(!out.isEmpty())
        ui->plainTextEdit->putData(" RESULT : "
                                   + out
                                   + mReadOnlyIndicator);
}

void ConsoleView::slotLock()
{
    ui->plainTextEdit->setReadOnly(true);
}

void ConsoleView::slotUnlock()
{
    ui->plainTextEdit->setReadOnly(false);
}

QByteArray ConsoleView::clearAppend(const QString &pTmp)
{
    mData.clear();
    return mData.append(pTmp);
}

void ConsoleView::slotPrintWorkingDir(const QString &pDir)
{
    ui->plainTextEdit->putData(clearAppend(pDir + mReadOnlyIndicator));
    mDirPrinted = true;
}

ConsoleView::~ConsoleView()
{
    delete ui;
}
