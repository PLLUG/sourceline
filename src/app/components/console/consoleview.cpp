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
#include <QProcess>
#include <QDebug>
#include <QDir>
#include <QSysInfo>

ConsoleView::ConsoleView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleView)
{
    ui->setupUi(this);
    ui->plainTextEdit->setLocalEchoEnabled(true);
    ui->plainTextEdit->putData(clearAppend("~>"));
    dirPrinted = true;

    mProcess = new QProcess(this);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    mProcess->setProcessEnvironment(env);
    mProcess->setProcessChannelMode(QProcess::MergedChannels);

    connect(ui->plainTextEdit, SIGNAL(signalSendCmd(QString)), this, SLOT(slotExec(QString)));
    connect(mProcess, SIGNAL(readyRead()), this, SLOT(slotReadConsoleOutput()));
    connect(mProcess, SIGNAL(readChannelFinished()), SLOT(slotPrintWorkingDir()));
}

ConsoleView::~ConsoleView()
{
    mProcess->close();
    mProcess->terminate();
    delete ui;
}

void ConsoleView::execute(QString &pCommand)
{
    ui->plainTextEdit->putData("\n");
    mProcess->write(pCommand.toUtf8());
    if(mProcess->atEnd() && !dirPrinted)
    {
        slotPrintWorkingDir();
    }
    QProcess* console;
    if(OsInfo()=="windows")
    {
        console = new QProcess(this);
        QByteArray resultConsole;
        QStringList args;
        //QString cdPathAndCommand = "cd"+consolePath()+"&call "+pCommand;
        args << "/c"  << pCommand; // << "\r" //Two commands in CMD Link : http://stackoverflow.com/questions/9888806/run-two-commands-in-one-windows-cmd-line-one-command-is-set-command
        //need set mPath
        //cmd->setWorkingDirectory(mPath);
        console->start("C:\\Windows\\System32\\cmd", args);
        //cmd->startDetached("C:\\Program Files\\Git\\bin"); //???need arguments for Git
        if (!console->waitForStarted())
        {
            qDebug() << " cmd crashed.";
            return;
        }

        console->waitForFinished();
        console->waitForReadyRead();
        console->waitForBytesWritten();
        resultConsole = console->readAll();
        qDebug() << resultConsole;

        if(!resultConsole.isEmpty())
            ui->plainTextEdit->putData(" RESULT : " + resultConsole + "~>");
        console->waitForFinished();
        qDebug() << console->exitCode();

    }
    else if(OsInfo()=="ubuntu")
    {

        console = new QProcess(this);
        //sh->setWorkingDirectory("//home//lynda//"); set mPath
        console->start("sh");
        qDebug() << QDir::currentPath();
        if (!console->waitForStarted())
        {
            qDebug() << " sh crashed.";
            return;
        }
        console->write(clearAppend(pCommand));
        console->closeWriteChannel();

        console->waitForFinished();
        QByteArray resultSH = console->readAll();
        console->close();
        if(!resultSH.isEmpty())
            ui->plainTextEdit->putData(" RESULT : " + resultSH + "~>");

    }
    else
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->putData("\nProductType: " + clearAppend(QSysInfo::productType())
                                   + "\nPrettyProductName: " + clearAppend(QSysInfo::prettyProductName())
                                   + "\nProductVersion: " + clearAppend(QSysInfo::productVersion())
                                   + "\nKernelType: " + clearAppend(QSysInfo::kernelType())
                                   + "\nKernelVersion: " + clearAppend(QSysInfo::kernelVersion())
                                   + "\n NOW THIS OS IS NOT SUPPORTED.");
        ui->plainTextEdit->setDisabled(true);
    }

    //Command inside СonsoleView
    if(pCommand == "close\n")
    {
        qApp->quit();
    }
}

/*
 * function System Info.
 * To know what in what OS is running SL.
 */
const QString ConsoleView::OsInfo()
{
    return QSysInfo::productType();
}

/*
 * function what return current PATH for QProcess::setWorkingDirectory
 */
const QString ConsoleView::consolePath()
{
    //to get current path , set in pCommand = echo %cd% or write your comand and add "&call (func)"
    return mPath;
}

void ConsoleView::slotSetConsolePath(QString &pPath)
{
    if(!mPath.isEmpty() && (mPath != pPath))
    {
        mProcess->close();
        mProcess->terminate();
        qDebug() << mPath << "close";
    }
    if(!pPath.isEmpty())
    {
        mPath = pPath;
        startProcess();
    }
    else
    {
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText("Please select commad-line interpreter in Setting!");
    }
}

void ConsoleView::slotReadConsoleOutput()
{
    QByteArray output = mProcess->readAll();
    ui->plainTextEdit->putData(output);
    ui->plainTextEdit->putData("\n");

    if (!mProcess->atEnd())
    {
        slotReadConsoleOutput();
    }
    else
    {
        slotPrintWorkingDir();
    }
}

void ConsoleView::slotExec(QString cmd)
{
    cmd +='\n';
    dirPrinted = false;
    this->execute(cmd);
}

void ConsoleView::startProcess()
{
    if(mProcess->state() != QProcess::Running)
    {
        qDebug() << mPath << "start";
        ui->plainTextEdit->clear();
        mProcess->start(mPath, QStringList());
        mProcess->waitForStarted();
        slotPrintWorkingDir();
    }
}

QByteArray ConsoleView::clearAppend(const QString &tmp)
{
    mData.clear();
    return mData.append(tmp);
}

void ConsoleView::slotPrintWorkingDir(QString dir)
{
    QString lWorkDir = dir;

    ui->plainTextEdit->putData(clearAppend(lWorkDir+"~>"));
    dirPrinted = true;
}
