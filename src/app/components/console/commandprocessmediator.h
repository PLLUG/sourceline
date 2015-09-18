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


#ifndef COMMANDPROCESSMEDIATOR_H
#define COMMANDPROCESSMEDIATOR_H

#include <QObject>
#include "commandprocess.h"

class CommandProcessMediator : public QObject
{
    Q_OBJECT
public:
    explicit CommandProcessMediator(QObject *parent = 0);

signals:
    void execute(QString);
    void commandMapped(QString commandId);
    void processStandardOutput(QByteArray out);
    void processErrorOutput(QByteArray out);
    void processStarted();
    void processFinished();

public slots:
    void processConsoleInput(QString input);

    void registerCommand(QString commandId, QString inputPattern);

private:
     CommandProcess *mProcess;
};

#endif // COMMANDPROCESSMEDIATOR_H
