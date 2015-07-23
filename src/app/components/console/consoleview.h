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

#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <QWidget>

namespace Ui {
class ConsoleView;
}
class QProcess;

class ConsoleView : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleView(QWidget *parent = 0);
    ~ConsoleView();
    void execute(QString pCommand);
    QString consolePath(); 
    QString OsInfo();
public slots:
    void slotSetConsolePath(QString pPath);
    void slotReadConsoleOutput();
    void slotExec(QString cmd);

private:
    void startProcess();
    QWidget *mParent;

private slots:
    void slotPrintWorkingDir(QString dir = QString());


private:
    Ui::ConsoleView *ui;
    QProcess *mProcess;
    QString mPath;
    bool dirPrinted;
};

#endif // CONSOLEVIEW_H
