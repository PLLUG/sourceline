/*******************************************************************************
***                                                                          ***
***    SourceLine - Crossplatform VCS Client.                                ***
***    Copyright (C) 2014  by                                                ***
***            Yura Olenych (yura.olenych@users.sourceforge.net)             ***
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

#ifndef CONSOLEVIEW_H
#define CONSOLEVIEW_H

#include <QWidget>
#include "commandprocess.h"

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
    void toExecute(const QString &pCommand);
    const QString consolePath();
    QString osInfo() const;
public slots:
    void slotExec(QString cmd);
    void slotOut(QByteArray out);
    void slotLock();
    void slotUnlock();

    void debugCursorPositionChanged();
    void debugTextChanged();
    void debugdataChanged(QByteArray data);
    void debugBlockCountChanged(int count);

signals:
    void commandEntered(QString cmd);

private:
    void startProcess();
    QByteArray clearAppend(const QString &pTmp);

private slots:
    void slotPrintWorkingDir(const QString &pDir = QString());


private:

    bool mDirPrinted;
    CommandProcess *mCmdProcess;
    QByteArray mData;
    QByteArray mReadOnlyIndicator;
    QString mPath;
    Ui::ConsoleView *ui;
};

#endif // CONSOLEVIEW_H
