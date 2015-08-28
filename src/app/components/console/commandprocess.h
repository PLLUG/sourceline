/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2015  by                                                ***
***            Olexandr Lynda (sanya.l9519@gmail.com)                        ***
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

#ifndef COMMANDPROCESS_H
#define COMMANDPROCESS_H

#include <QObject>

class QProcess;

/*!
 * \brief The CommandProcess class is responsible for execution of commands as a separate
 * processes.
 */
class CommandProcess : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString shell READ shell WRITE setShell)
    Q_PROPERTY(QStringList shellParam READ shellParam WRITE setShellParam)
public:
    explicit CommandProcess(QObject *parent = 0);
    void start();
    QString shell();
    void setShell(const QString &shell);
    QStringList shellParam();
    void setShellParam(const QStringList &shellParam);
    ~CommandProcess();

signals:
    void standardOutput(QByteArray out);
    void errorOutput(QByteArray out);
    void started();
    void finished();

public slots:
    void execute(const QString &command);

private slots:
    void readStandardOutput();
    void readStandardError();
    void slotAfterFinished();

private:
    void shutdown();

private:
    QProcess *mProcess;
    QByteArray mData;
    QString mShell;
    QStringList mShellParam;
};

#endif // COMMANDPROCESS_H
