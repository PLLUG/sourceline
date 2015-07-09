#include "texteditforrename.h"
#include <QDebug>

TextEditForRename::TextEditForRename(QWidget *parent) : QTextEdit(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    connect(this->document(), SIGNAL(contentsChanged()), this, SLOT(slotUpdateHeight()));
    this->installEventFilter(parent);
}

void TextEditForRename::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return)
    {
        this->setEnabled(false);
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

bool TextEditForRename::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::Resize)
    {
        slotUpdateHeight();
    }
    if (event->type() == QEvent::PolishRequest)
    {
        slotUpdateHeight();
        QTextCursor cursor = this->textCursor();
        cursor.setPosition(0);
        cursor.setPosition(this->toPlainText().length(), QTextCursor::KeepAnchor);
        this->setTextCursor(cursor);
    }
    return false;
}

void TextEditForRename::slotUpdateHeight()
{
    this->setFixedHeight(this->document()->size().height() + 5);
}


