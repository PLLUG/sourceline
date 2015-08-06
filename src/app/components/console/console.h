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

#ifndef CONSOLE_H
#define CONSOLE_H

#include <QPlainTextEdit>

class QColor;

class Console : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit Console(QWidget *parent = 0);
    void putData(const QByteArray &data);
    void setLocalEchoEnabled(bool set);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void contextMenuEvent(QContextMenuEvent *e);

signals:
    void getData(const QByteArray &data);
    void signalSendCmd(QString);

private:
    void moveCursorToEnd();
    bool localEchoEnabled;
    QString currentCmd;
    QString mPreviousCmd;
    int maximumBlockCount = 1000;
    QColor mColorBase = Qt::black;
    QColor mColorInputText = Qt::green;
    QTextCursor mCursor;
};

#endif // CONSOLE_H
