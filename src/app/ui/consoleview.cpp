/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
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

#include "consoleview.h"
#include "ui_consoleview.h"
#include <QProcess>
#include <QDebug>
#include <QDir>

ConsoleView::ConsoleView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConsoleView)
{
    ui->setupUi(this);
    ui->plainTextEdit->setLocalEchoEnabled(true);
    mProcess = new QProcess(this);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
//    env.insert("PATH", env.value("Path") + ";C:\\Program Files (x86)\\Git\\bin\\;");
//    env.insert("PATH", env.value("Path") + ";C:\\Program Files (x86)\\Subversion\\bin\\;");
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

void ConsoleView::execute(QString pCommand)
{
    ui->plainTextEdit->putData("\n");
    mProcess->write(pCommand.toUtf8());
    if(mProcess->atEnd() && !dirPrinted)
    {
        qDebug() << "dir print from exec";
        slotPrintWorkingDir();
    }
}

QString ConsoleView::consolePath()
{
    return mPath;
}

void ConsoleView::slotSetConsolePath(QString pPath)
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
//    if(mProcess->waitForReadyRead(100))
//    {
//        qDebug() << "enable data to read!";
//        slotReadConsoleOutput();
//    }else
//    {
//        qDebug() << "dir print from read";
//    }


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

void ConsoleView::slotPrintWorkingDir(QString dir)
{
    QString lWorkDir = dir;
//    if(lWorkDir.isEmpty())
//    {
//        lWorkDir = QDir::currentPath();
//    }
        ui->plainTextEdit->putData(QByteArray().append(lWorkDir+"~>"));
        dirPrinted = true;
}
