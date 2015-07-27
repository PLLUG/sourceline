/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Priyma Yuriy (priymayuriy@gmail.com)                          ***
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

#ifndef IPROCESSAPI
#define IPROCESSAPI

#include <QObject>
#include <QDir>
#include <QProcess>

class IProcessAPI
{
public:
    enum ProcessError
    {
        NoError = QProcess::ProcessError::UnknownError + 1
    };

signals:
    virtual void commandFinished(const QString pOutput) = 0;
    virtual void commandNewDataReceived(const QString pOutput) = 0;
    virtual void error(ProcessErrors pErrorKey) = 0;

public:
    virtual void execCommand(const QString pCommand) = 0;
    virtual void setExecutableProcessPath(const QDir pCommand) = 0;
    virtual QDir getExecutableProcessPath() const = 0;

};

Q_DECLARE_INTERFACE(IProcessAPI, "IProcessAPI")

#endif // IPROCESSAPI

