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
    ui->plainTextEdit->putData(clearAppend(mReadOnlyIndicator));
    mDirPrinted = true;
    mReadOnlyIndicator = "~>";

    mProcess = new QProcess(this);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    mProcess->setProcessEnvironment(env);
    mProcess->setProcessChannelMode(QProcess::MergedChannels);

    connect(ui->plainTextEdit, SIGNAL(signalSendCmd(QString)), this, SLOT(slotExec(QString)));
    connect(mProcess, SIGNAL(readyRead()), this, SLOT(slotReadConsoleOutput()));
    connect(mProcess, SIGNAL(readChannelFinished()), SLOT(slotPrintWorkingDir()));
    connect(ui->plainTextEdit, SIGNAL(cursorPositionChanged()), SLOT(debugCursorPositionChanged()));
    connect(ui->plainTextEdit, SIGNAL(textChanged()), SLOT(debugTextChanged()));
    connect(ui->plainTextEdit, SIGNAL(dataChanged(QByteArray)),SLOT(debugdataChanged(QByteArray)));
    connect(ui->plainTextEdit, SIGNAL(blockCountChanged(int)),SLOT(debugBlockCountChanged(int)));
}

void ConsoleView::debugCursorPositionChanged()
{
    qDebug() << " ConsoleView::Cursor position changed;" ;
}

void ConsoleView::debugTextChanged()
{
    qDebug() << " ConsoleView::Text changed;";
}

void ConsoleView::debugdataChanged(QByteArray data)
{
    qDebug() << "ConsoleView:: Data :" << data;
}

void ConsoleView::debugBlockCountChanged(int count)
{
    qDebug() << "ConsoleView::BlockCountChanged to:" << count;
}

ConsoleView::~ConsoleView()
{
    mProcess->close();
    mProcess->terminate();
    delete ui;
}

void ConsoleView::execute(const QString &pCommand)
{
    ui->plainTextEdit->putData("\n");
    mProcess->write(pCommand.toUtf8());
    if(mProcess->atEnd() && !mDirPrinted)
    {
        slotPrintWorkingDir();
    }
    QProcess* console = nullptr;
    if(osInfo()=="windows")
    {
        console = new QProcess(this);
        QByteArray resultConsole;
        QStringList args;
        args << "/c"  << pCommand;
        console->start("C:\\Windows\\System32\\cmd", args);
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
            ui->plainTextEdit->putData(" RESULT : "
                                       + resultConsole
                                       + mReadOnlyIndicator);
        console->waitForFinished();
        if(console->exitCode() == 1)
            ui->plainTextEdit->putData(" ERROR \n" + mReadOnlyIndicator);
        qDebug() << console->exitCode();
    }

    else if(QSysInfo::kernelType()=="linux")
    {
        console = new QProcess(this);
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
            ui->plainTextEdit->putData(" RESULT : "
                                       + resultSH
                                       + mReadOnlyIndicator);
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

void ConsoleView::slotSetConsolePath(const QString &pPath)
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
    mDirPrinted = false;
    execute(cmd);
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

QByteArray ConsoleView::clearAppend(const QString &pTmp)
{
    mData.clear();
    return mData.append(pTmp);
}

void ConsoleView::slotPrintWorkingDir(const QString &pDir)
{
    QString lWorkDir = pDir;

    ui->plainTextEdit->putData(clearAppend(lWorkDir + mReadOnlyIndicator));
    mDirPrinted = true;
}