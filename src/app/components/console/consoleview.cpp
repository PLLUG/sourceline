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
#include <QSysInfo>
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
    CommandProcessMediator *mediator = new CommandProcessMediator(this);

    ui->setupUi(this);
    ui->plainTextEdit->setLocalEchoEnabled(true);
    ui->plainTextEdit->putData(clearAppend("\t<SL-CONSOLE>\n\nINTRO:\n*If you double click console will be cleared,\n"
                                           "*Do not put exit command , it will close console and you will not be able to use that.\n\n"));

    connect(ui->plainTextEdit, SIGNAL(signalSendCmd(QString)), this, SLOT(slotExec(QString)));

    connect(mediator, &CommandProcessMediator::processStarted, this, &ConsoleView::slotLock);
    connect(mediator, &CommandProcessMediator::processFinished, this, &ConsoleView::slotUnlock);
    connect(this, &ConsoleView::commandEntered, mediator, &CommandProcessMediator::processConsoleInput, Qt::UniqueConnection);
    connect(mediator, &CommandProcessMediator::processStandardOutput, this, &ConsoleView::slotOut, Qt::UniqueConnection);
    connect(mediator, &CommandProcessMediator::processErrorOutput, this, &ConsoleView::slotOut, Qt::UniqueConnection);
}

/*!
* \brief ConsoleView::toExecute is function what prepare all to execute the command
* \param pCommand is QString line what entered user for executing
*/
void ConsoleView::toExecute(const QString &pCommand) //as command use @cd C:\Users&ls -R@ or @tree C:\ /A@
{
    ui->plainTextEdit->putData("\n");
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

void ConsoleView::slotExec(QString cmd)
{
    cmd +='\n';
    toExecute(cmd);
}

void ConsoleView::slotOut(QByteArray out)
{
    if(out.at(0) != '\n')
        ui->plainTextEdit->putData(out);
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

ConsoleView::~ConsoleView()
{
    delete ui;
}
