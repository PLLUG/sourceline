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

#include "console.h"
#include <QScrollBar>
#include <QDebug>

Console::Console(QWidget *parent)
    : QPlainTextEdit(parent)
    , localEchoEnabled(false)
{
    document()->setMaximumBlockCount(maximumBlockCount);
    QPalette p = palette();
    p.setColor(QPalette::Base, mColorBase);
    p.setColor(QPalette::Text, mColorInputText);
    setPalette(p);
}

void Console::putData(const QByteArray &data)
{
    insertPlainText(QString(data.constData()));

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
        if(!currentCmd.isEmpty())
        {
            currentCmd.remove(currentCmd.length()-1, 1);
            QPlainTextEdit::keyPressEvent(e);
        }
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        emit signalSendCmd(currentCmd);
        currentCmd.clear();
        break;
    case Qt::Key_Left:
    case Qt::Key_Right:
    case Qt::Key_Up:
    case Qt::Key_Down:
        QPlainTextEdit::keyPressEvent(e);
        break;
    default:
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);
        setTextCursor(cursor);
        if (localEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        currentCmd.append(e->text());
        emit getData(e->text().toLocal8Bit());
    }
}


/*
 * function : Clear console with mouse double click(as example)
 */
void Console::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    clear();
    insertPlainText("Console was cleared with double clicking!\n~>");
}

void Console::contextMenuEvent(QContextMenuEvent *e)
{
    Q_UNUSED(e)
}
