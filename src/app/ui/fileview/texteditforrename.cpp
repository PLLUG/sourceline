#include "texteditforrename.h"

TextEditForRename::TextEditForRename(QWidget *parent) : QTextEdit(parent)
{
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

