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
public:
    explicit CommandProcess(QObject *parent = 0);

signals:
    void standardOutput(QByteArray out);
    void errorOutput(QByteArray out);
    void started();
    void finished();

public slots:
    void execute(QString shell, QString command, QStringList parameters);

private slots:
    void readStandardOutput();
    void readStandardError();
    void slotAfterFinished(int exitStatus, int exitCode);

private:
    QProcess *mProcess;
    QByteArray mData;
};

#endif // COMMANDPROCESS_H
