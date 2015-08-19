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
    , mLocalEchoEnabled(false)
{
    mCursor = textCursor();
    mMaximumBlockCount = 1000;
    mColorBase = Qt::black;
    mColorInputText = Qt::green;
    mReadOnlyLen = 2;

    document()->setMaximumBlockCount(mMaximumBlockCount);
    QPalette p = palette();
    p.setColor(QPalette::Base, mColorBase);
    p.setColor(QPalette::Text, mColorInputText);
    setPalette(p);
}

void Console::putData(const QByteArray &pData)
{
    insertPlainText(QString(pData.constData()));

    QScrollBar *bar = verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Console::setLocalEchoEnabled(bool pSet)
{
    mLocalEchoEnabled = pSet;
}

void Console::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Backspace:
        if(!mCurrentCmd.isEmpty() && mCursor.positionInBlock() > mReadOnlyLen)
        {
            moveCursorToEnd();
            mCurrentCmd.remove(mCurrentCmd.length()-1, 1);
            QPlainTextEdit::keyPressEvent(e);
        }
        break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        emit signalSendCmd(mCurrentCmd);
        mPreviousCmd = mCurrentCmd;
        mCurrentCmd.clear();
        break;
    case Qt::Key_Up:
        if(mCursor.positionInBlock() >= mReadOnlyLen)
        {
            mCurrentCmd = mPreviousCmd;
            insertPlainText(mCurrentCmd);
            mPreviousCmd.clear();
        }
        break;
    case Qt::Key_Left:
        if(mCursor.positionInBlock() > mReadOnlyLen)
            mCursor.movePosition(QTextCursor::Left);
        QPlainTextEdit::keyPressEvent(e);
        break;
    case Qt::Key_Down: break;
    case Qt::Key_Right:
        mCursor.movePosition(QTextCursor::Right);
        QPlainTextEdit::keyPressEvent(e);
        break;
    default:
        moveCursorToEnd();
        setTextCursor(mCursor);
        if (mLocalEchoEnabled)
            QPlainTextEdit::keyPressEvent(e);
        mCurrentCmd.append(e->text());
        emit getData(e->text().toLocal8Bit());
    }
}

void Console::moveCursorToEnd()
{
    if(mCursor.positionInBlock() < mReadOnlyLen)
    {
        mCursor.setPosition(QTextCursor::EndOfLine);
    }
}

/*!
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
